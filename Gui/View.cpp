/// 10 X 10

/**
  * @file Gui/View.cpp
 **/

#include "Core/Board.hpp"
#include "Core/Engine.hpp"
#include "Core/Object.hpp"
#include "Core/ObjectBuilder.hpp"

#include "Gui/ColorMap.hpp"
#include "Gui/Item.hpp"
#include "Gui/HighlightController.hpp"
#include "Gui/HighlightItem.hpp"
#include "Gui/Scene.hpp"
#include "Gui/View.hpp"

#include <qdebug.h>


namespace Gui {

View::View(QWidget* parent)
    : QGraphicsView(parent)
    , m_scene(nullptr)
    , m_object(nullptr)
{
    static const int spacing = 6;
    m_scene = new Scene();
    setScene(m_scene);
    setMouseTracking(true);
    setFixedSize(width() + spacing, height() + spacing);
}

int View::width() const noexcept
{
    return Item::width() * Core::Board::size();
}

int View::height() const noexcept
{
    return Item::height() * Core::Board::size();
}

Scene* View::getScene() const noexcept
{
    return m_scene;
}

void View::mouseMoveEvent(QMouseEvent* event)
{
    QPointF p = mapToScene(event->pos());
    HighlightController::get()->highlight(m_object, p);
}

void View::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if (m_object == nullptr) {
        return;
    }
    QPointF p = mapToScene(event->pos());
    Core::Index index = Core::Index::posToIndex(p, Item::width(), Item::height());
    Core::Engine* e = Core::Engine::get();
    if (e->canCreateObject(m_object, index)) {
        ColorMap* cm = ColorMap::get();
        Q_ASSERT(cm != nullptr);
        cm->objectCreated(m_object, index);
        Q_ASSERT(e != nullptr);
        e->notifyChanged(m_object, index);
    }
}

void View::leaveEvent(QEvent*)
{
    HighlightController::get()->clearHighlight();
}

void View::drawBackground(QPainter* painter, const QRectF&)
{
    painter->drawImage(0, 0, QImage("../Img/vbg.jpg"));
}

void View::drawForeground(QPainter* painter, const QRectF&)
{

    drawBoard(painter);
}

void View::drawBoard(QPainter* painter) noexcept
{
    Q_ASSERT(painter != nullptr);
    painter->setPen(QColor(Qt::gray));
    painter->drawRect(0, 0, width(), height());
    for (auto i = 1; i < 10; ++i) {
        /// Vertical
        painter->drawLine(i * 60, 0, i * 60, height());
        /// Horizontal
        painter->drawLine(0, i * 60, width(), i * 60);
    }
}

void View::redrawItems()
{
    clearItems();
    const std::set<Core::Index>& indexes = Core::Engine::get()->getCheckedCells();
    for (auto it : indexes) {
        Item* i = new Item(it, m_object);
        Q_ASSERT(m_scene != nullptr);
        m_scene->addItem(i);
        m_items.push_back(i);
    }
    m_scene->update();
}

void View::setObject(Core::Object* o) noexcept
{
    m_object = o;
}

void View::clearItems() noexcept
{
    for (auto it : m_items) {
        m_scene->removeItem(it);
        delete it;
    }
    m_items.clear();
}

} /// Gui namespace
