/// 10 X 10

/**
  * @file Core/Engine.cpp
 **/

#include "Core/Engine.hpp"
#include "Core/Object.hpp"
#include "Core/ObjectBuilder.hpp"
#include "Core/Observer.hpp"
#include "Core/OptionsManager.hpp"
#include "Core/ScoreManager.hpp"

#include <QDebug>

#define BOARD_SIZE 10


namespace Core {

Engine* Engine::m_engine = nullptr;

void Engine::create() noexcept
{
    if (m_engine == nullptr) {
        m_engine = new Engine;
    }
}

void Engine::destroy() noexcept
{
    OptionsManager::get()->save();
    if (m_engine != nullptr) {
        delete m_engine;
        m_engine = nullptr;
    }
}

Engine* Engine::get() noexcept
{
    Q_ASSERT(m_engine != nullptr);
    return m_engine;
}

Engine::Engine()
    : m_board(new Board)
    , m_scoreManager(new ScoreManager)
    , m_current_objects(std::vector<Object*>(3, nullptr))
{
    Observer::create();
    ObjectBuilder::create();
    OptionsManager::create();
    generateCurrentObjects();
    /// record
    m_scoreManager->loadRecordFromOption();
}

Engine::~Engine()
{
    Observer::destroy();
    ObjectBuilder::destroy();
    OptionsManager::get()->save();
    OptionsManager::destroy();
    m_board.release();
    m_scoreManager.release();
}

bool Engine::isCellChecked(const Index& i) const noexcept
{
    return m_board->isCellChecked(i);
}

bool Engine::isOutOfBounds(Core::Object* const o, const Index& i) const noexcept
{
    if (o == nullptr || !i.isValid()) {
        return true;
    }
    return m_board->isOutOfBounds(o, i);
}

bool Engine::canCreateObject(Object* const o, const Index& i) const noexcept
{
    if (o == nullptr || !i.isValid()) {
        return false;
    }

    switch (o->getType()) {
        case Object::Type::angled:
            return canCreateAngledObject(o, i);
        case Object::Type::linear:
            return canCreateLinearObject(o, i);
        case Object::Type::squared:
            return canCreateSquaredObject(o, i);
        default:;
    }
    return false;
}

bool Engine::canCreateAngledObject(Object* const obj, const Index& i) const noexcept
{
    AngledObject* ao = static_cast<AngledObject*>(obj);
    int length = ao->getLength();
    int row = i.row();
    int column = i.column();
    AngledObject::HorizontalDirection hdir = ao->getHorizontalDirection();
    AngledObject::VerticalDirection vdir = ao->getVerticalDirection();
    const bool isLeft = hdir == AngledObject::HorizontalDirection::left;
    const bool isTop = vdir == AngledObject::VerticalDirection::top;
    if (isLeft) {
        if (column - length + 1 < 0) {
            return false;
        }
    } else {
        if (column + length > Board::size()) {
            return false;
        }
    }
    if (isTop) {
        if (row - length + 1 < 0) {
            return false;
        }
    } else {
        if (row + length > Board::size()) {
            return false;
        }
    }

    if (isLeft) {
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row, column - i)) {
                return false;
            }
        }
    } else {
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row, column + i)) {
                return false;
            }
        }
    }

    if (isTop) {
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row - i, column)) {
                return false;
            }
        }
    } else {
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row + i, column)) {
                return false;
            }
        }
    }
    return true;
}

bool Engine::canCreateLinearObject(Object* const obj, const Index& i) const noexcept
{
    LinearObject* lo = static_cast<LinearObject*>(obj);
    int length = lo->getLength();
    int row = i.row();
    int column = i.column();
    LinearObject::Direction dir = lo->getDirection();
    if (dir == LinearObject::Direction::horizontal) {
        if (column + length > Board::size()) {
            return false;
        }
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row, column + i)) {
                return false;
            }
        }
    } else if (dir == LinearObject::Direction::vertical) {
        if (row + 1 - length < 0) {
            return false;
        }
        for (int i = 0; i < length; ++i) {
            if (m_board->isCellChecked(row - i, column)) {
                return false;
            }
        }
    }
    return true;
}

bool Engine::canCreateSquaredObject(Object* const obj, const Index& i) const noexcept
{
    SquaredObject* lo = static_cast<SquaredObject*>(obj);
    int length = lo->getLength();
    int row = i.row();
    int column = i.column();
    if (row + length > Board::size() || column + length > Board::size()) {
        return false;
    }
    for (int ri = 0; ri < length; ++ri) {
        for (int ci = 0; ci < length; ++ci) {
            if (m_board->isCellChecked(i.row() + ri, i.column() + ci)) {
                return false;
            }
        }
    }
    return true;
}

const std::set<Index>& Engine::getCheckedCells() const noexcept
{
    return m_board->getCheckedCells();
}

const std::vector<Object*>& Engine::getCurrentObjects() const noexcept
{
    return m_current_objects;
}

void Engine::notifyChanged(Object* o, const Index& i)
{
    if (o == nullptr) {
        return;
    }
    if (!i.isValid()) {
        return;
    }
    if (m_board->isCellChecked(i)) {
        return;
    }
    if (canCreateObject(o, i)) {
        createObject(o, i);
        updateCurrentObjects(o);
        removeFullRows();
        Observer::get()->processData();
        if (!canCreateNextObject()) {
            Observer::get()->notifyGameFinished();
        }
    }
}

void Engine::createObject(Object* const o, const Index& i)
{
    Q_ASSERT(o != nullptr && i.isValid());
    Q_ASSERT(canCreateObject(o, i));
    switch (o->getType()) {
        case Object::Type::angled:
            createAngledObject(o, i);
            break;
        case Object::Type::linear:
            createLinearObject(o, i);
            break;
        case Object::Type::squared:
            createSquaredObject(o, i);
            break;
        default:;
    }
}

void Engine::createAngledObject(Object* const obj, const Index& i)
{
    AngledObject* ao = static_cast<AngledObject*>(obj);
    const int length = ao->getLength();
    AngledObject::HorizontalDirection hdir = ao->getHorizontalDirection();
    AngledObject::VerticalDirection vdir = ao->getVerticalDirection();
    const bool isLeft = hdir == AngledObject::HorizontalDirection::left;
    const bool isTop = vdir == AngledObject::VerticalDirection::top;
    setCellChecked(i);
    for (int it = 1; it < length; ++it) {
        if (isLeft) {
            setCellChecked(Index(i.row(), i.column() - it));
        } else {
            setCellChecked(Index(i.row(), i.column() + it));
        }
    }
    for (int it = 1; it < length; ++it) {
        if (isTop) {
            setCellChecked(Index(i.row() - it, i.column()));
        } else {
            setCellChecked(Index(i.row() + it, i.column()));
        }
    }
}

void Engine::createLinearObject(Object* const o, const Index& i)
{
    LinearObject* lo = static_cast<LinearObject*>(o);
    const int length = lo->getLength();
    const bool isHorizontal = lo->getDirection() == LinearObject::Direction::horizontal;
    for (int it = 0; it < length; ++it) {
        if (isHorizontal) {
            setCellChecked(Index(i.row(), i.column() + it));
        } else {
            setCellChecked(Index(i.row() - it, i.column()));
        }
    }
}

void Engine::createSquaredObject(Object* const o, const Index& i)
{
    SquaredObject* lo = static_cast<SquaredObject*>(o);
    const int length = lo->getLength();
    for (int ri = 0; ri < length; ++ri) {
        for (int ci = 0; ci < length; ++ci) {
            setCellChecked(Index(i.row() + ri, i.column() + ci));
        }
    }
}

unsigned long Engine::getScore() const noexcept
{
    return m_scoreManager->getScore();
}

unsigned long Engine::getRecord() const noexcept
{
    return m_scoreManager->getRecord();
}

void Engine::setCellChecked(const Index& i)
{
    if (!i.isValid()) {
        return;
    }
    m_board->setCellChecked(i);
    m_scoreManager->updateScore(ScoreManager::ActionType::ObjectAdded);
}

void Engine::removeFullRows()
{
    std::list<int> rows;
    std::list<int> columns;
    for (auto r = 0; r < BOARD_SIZE; ++r) {
        /// Rows
        int i = 0;
        for (; i < BOARD_SIZE; ++i) {
            if (!m_board->isCellChecked(i, r)) {
                break;
            }
        }
        if (i == BOARD_SIZE) {
            rows.push_back(r);
        }
        /// Columns
        i = 0;
        for (; i < BOARD_SIZE; ++i) {
            if (!m_board->isCellChecked(r, i)) {
                break;
            }
        }
        if (i == BOARD_SIZE) {
            columns.push_back(r);
        }
    }
    /// Vertical lines
    for (auto it : rows) {
        for (auto i = 0; i < BOARD_SIZE; ++i) {
            m_board->setCellUnchecked(Index(i, it));
        }
        m_scoreManager->updateScore(ScoreManager::ActionType::RowDeleted);
    }
    /// Horizontal lines
    for (auto it : columns) {
        for (auto i = 0; i < BOARD_SIZE; ++i) {
            m_board->setCellUnchecked(Index(it, i));
        }
        m_scoreManager->updateScore(ScoreManager::ActionType::RowDeleted);
    }
}

void Engine::generateCurrentObjects()
{
    deleteCurrentObjects();
    for (auto& it : m_current_objects) {
        ObjectBuilder* builder = ObjectBuilder::get();
        it = builder->generateObject();
    }
    for (size_t i = 0; i < m_current_objects.size(); ++i) {
        if (canCreateNextObject()) {
            return;
        }
    }
    generateCurrentObjects();
}

void Engine::updateCurrentObjects(Object* o)
{
    for (auto& it : m_current_objects) {
        if (it == o) {
            delete it;
            it = nullptr;
        }
    }

    auto needGenerate = [](Object* o) {
        return o != nullptr;
    };
    auto it = std::find_if(m_current_objects.begin(), m_current_objects.end(), needGenerate);

    if (it == m_current_objects.end()) {
        generateCurrentObjects();
    }
}

void Engine::deleteCurrentObjects()
{
    if (m_current_objects.empty()) {
        return;
    }
    for (auto it : m_current_objects) {
        if (it != nullptr) {
            delete it;
            it = nullptr;
        }
    }
}

bool Engine::canCreateNextObject() const noexcept
{
    std::list<Index> indexes;
    m_board->getUncheckedCells(indexes);
    for (const auto& o : m_current_objects) {
        for (auto i : indexes) {
            if (canCreateObject(o, i)) {
                return true;
            }
        }
    }
    return false;
}

} /// Core namespace
