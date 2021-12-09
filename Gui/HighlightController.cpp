/// 10 X 10

/**
  * @file Gui/HighlightController.cpp
 **/

#include "Core/Board.hpp"
#include "Core/Engine.hpp"
#include "Core/Index.hpp"
#include "Core/Object.hpp"

#include "Gui/HighlightController.hpp"
#include "Gui/HighlightItem.hpp"
#include "Gui/Item.hpp"
#include "Gui/Scene.hpp"

#include <qdebug.h>


namespace Gui {

HighlightController* HighlightController::m_highlightController = nullptr;

void HighlightController::create(Scene* s) noexcept
{
    if (m_highlightController == nullptr) {
        m_highlightController = new HighlightController(s);
    }
}

void HighlightController::destroy() noexcept
{
    if (m_highlightController != nullptr) {
        delete m_highlightController;
        m_highlightController = nullptr;
    }
}

HighlightController* HighlightController::get() noexcept
{
    Q_ASSERT(m_highlightController != nullptr);
    return m_highlightController;
}

HighlightController::HighlightController(Scene* s) noexcept
    : m_scene(s)
{
    Q_ASSERT(m_scene != nullptr);
}

void HighlightController::highlight(Core::Object* const o, const QPointF& p)
{
    clearHighlight();
    if (o == nullptr) {
        return;
    }
    switch (o->getType()) {
        case Core::Object::Type::angled:
            higlightAngledObject(o, p);
            break;
        case Core::Object::Type::linear:
            higlightLinearObject(o, p);
            break;
        case Core::Object::Type::squared:
            higlightSquaredObject(o, p);
            break;
        default:;
    }
}

void HighlightController::higlightAngledObject(Core::Object* const o, const QPointF& p)
{
    Core::AngledObject* ao = static_cast<Core::AngledObject*>(o);
    int l = ao->getLength();
    Core::AngledObject::HorizontalDirection hdir = ao->getHorizontalDirection();
    Core::AngledObject::VerticalDirection vdir = ao->getVerticalDirection();
    Core::Index index = Core::Index::posToIndex(p, Item::width(), Item::height());
    const bool isLeft = hdir == Core::AngledObject::HorizontalDirection::left;
    const bool isTop = vdir == Core::AngledObject::VerticalDirection::top;
    const bool outOfBounds = Core::Engine::get()->isOutOfBounds(o, index);
    QPointF currentPos = p;
    int yHolder = currentPos.y();
    addItem(currentPos, outOfBounds);
    for (int i = 0; i < l - 1; ++i) {
        currentPos.setY(isTop ? currentPos.y() - Item::height() : currentPos.y() + Item::height());
        addItem(currentPos, outOfBounds);
    }
    currentPos.setY(yHolder);
    for (int i = 0; i < l - 1; ++i) {
        currentPos.setX(isLeft ? currentPos.x() - Item::height() : currentPos.x() + Item::height());
        addItem(currentPos, outOfBounds);
    }
}

void HighlightController::higlightLinearObject(Core::Object* const o, const QPointF& p)
{
    Core::LinearObject* lo = static_cast<Core::LinearObject*>(o);
    int l = lo->Object::getLength();
    Core::LinearObject::Direction dir = lo->getDirection();
    Core::Index index = Core::Index::posToIndex(p, Item::width(), Item::height());
    const bool outOfBounds = Core::Engine::get()->isOutOfBounds(o, index);
    QPointF currentPos = p;
    for (int i = 0; i < l; ++i) {
        addItem(currentPos, outOfBounds);
        if (dir == Core::LinearObject::Direction::horizontal) {
            currentPos.setX(currentPos.x() + Item::width());
        } else {
            currentPos.setY(currentPos.y() - Item::height());
        }
    }
}

void HighlightController::higlightSquaredObject(Core::Object* const o, const QPointF& p)
{
    Core::SquaredObject* so = static_cast<Core::SquaredObject*>(o);
    int l = so->Object::getLength();
    Core::Index index = Core::Index::posToIndex(p, Item::width(), Item::height());
    const bool outOfBounds = Core::Engine::get()->isOutOfBounds(o, index);
    QPointF currentPos = p;
    for (int i = 0; i < l; ++i) {
        for (int row = 0; row < l; ++row) {
            addItem(currentPos, outOfBounds);
            currentPos.setX(currentPos.x() + Item::width());
        }
        currentPos.setY(currentPos.y() + Item::height());
        currentPos.setX(p.x());
    }
}

void HighlightController::addItem(const QPointF& p, bool outOfBounds)
{
    Core::Engine* e = Core::Engine::get();
    Core::Index index = Core::Index::posToIndex(p, Item::width(), Item::height());
    HighlightItem* item = new HighlightItem(p, !e->isCellChecked(index) && !outOfBounds);
    m_highlightItems.push_back(item);
    m_scene->addItem(item);
    m_scene->update(item->boundingRect());

}

void HighlightController::clearHighlight()
{
    Q_ASSERT(m_scene != nullptr);
    for (auto it : m_highlightItems) {
        m_scene->removeItem(it);
        delete it;
    }
    m_highlightItems.clear();
    m_scene->update();
}

} /// Gui namespace
