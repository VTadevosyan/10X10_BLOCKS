/// 10 X 10

/**
  * @file Core/Board.cpp
 **/

#include "Core/Board.hpp"
#include "Core/Object.hpp"

#define SIZE 10

#include <QDebug>


namespace Core {

int Board::size() noexcept
{
    return SIZE;
}

int Board::maximumCellsCount() noexcept
{
    return size() * size();
}

Board::Board()
{
    m_data = std::vector<bool>(100, false);
}

void Board::setCellChecked(const Index& i) noexcept
{
    Q_ASSERT(i.isValid());
    m_data[getCell(i)] = true;
    m_checked_cell_indexes.insert(i);
}

void Board::setCellUnchecked(const Index& i) noexcept
{
    Q_ASSERT(i.isValid());
    m_data[getCell(i)] = false;
    m_checked_cell_indexes.erase(i);
}

bool Board::isCellChecked(const Index& i) const noexcept
{
    if (!i.isValid()) {
        return false;
    }
    return m_data[getCell(i)];
}

bool Board::isCellChecked(int row, int col) const noexcept
{
    return m_data[getCell(row, col)];
}

bool Board::isOutOfBounds(Core::Object* const o, const Index& i) const noexcept
{
    Q_ASSERT(o != nullptr && i.isValid());
    switch (o->getType()) {
        case Object::Type::angled:
            return isAngledObjectOutOfBounds(o, i);
        case Object::Type::linear:
            return isLinearObjectOutOfBounds(o, i);
        case Object::Type::squared:
            return isSquaredObjectOutOfBounds(o, i);
    default:;
    }
    return true;
}

bool Board::isAngledObjectOutOfBounds(Core::Object* const o, const Index& i) const noexcept
{
    AngledObject* ao = static_cast<AngledObject*>(o);
    int l = ao->getLength();
    const bool isLeft = ao->getHorizontalDirection() == AngledObject::HorizontalDirection::left;
    const bool isTop = ao->getVerticalDirection() == AngledObject::VerticalDirection::top;
    bool outOfBoundsHorizontal = false;
    bool outOfBoundsVertical = false;
    if (isLeft) {
        outOfBoundsHorizontal = i.column() - l + 1 < 0;
    } else {
        outOfBoundsHorizontal = i.column() + l > size();
    }
    if (isTop) {
        outOfBoundsVertical = i.row() - l + 1 < 0;
    } else {
        outOfBoundsVertical = i.row() + l > size();
    }
    return outOfBoundsHorizontal || outOfBoundsVertical;
}

bool Board::isLinearObjectOutOfBounds(Core::Object* const o, const Index& i) const noexcept
{
    LinearObject* lo = static_cast<LinearObject*>(o);
    int l = lo->getLength();
    LinearObject::Direction dir = lo->getDirection();
    if (dir == Core::LinearObject::Direction::vertical && i.row() - l + 1 < 0) {
        return true;
    } else if (dir == Core::LinearObject::Direction::horizontal && i.column() + l > size()) {
        return true;
    }
    return false;
}

bool Board::isSquaredObjectOutOfBounds(Core::Object* const o, const Index& i) const noexcept
{
    SquaredObject* so = static_cast<SquaredObject*>(o);
    int l = so->getLength();
    return i.row() + l > size() || i.column() + l > size();
}

int Board::getCell(const Index& i) const noexcept
{
    Q_ASSERT(i.isValid());
    return getCell(i.row(), i.column());
}

int Board::getCell(int row, int col) const noexcept
{
    return row * size() + col;
}

const std::set<Index>& Board::getCheckedCells() const noexcept
{
    return m_checked_cell_indexes;
}

void Board::getUncheckedCells(std::list<Index>& indexes) const noexcept
{
    for (int r = 0; r < size(); ++r) {
        for (int c = 0; c < size(); ++c) {
            if (!m_data[r * size() + c]) {
                indexes.push_back(Index(r, c));
            }
        }
    }
}

} /// Core namespace
