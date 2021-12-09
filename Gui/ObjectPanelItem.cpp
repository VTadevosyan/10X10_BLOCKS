/// 10 X 10

/**
  * @file Gui/ObjectPanelItem.cpp
 **/

#include "Core/Object.hpp"

#include "Gui/ColorMap.hpp"
#include "Gui/ObjectPanelItem.hpp"

#include <QPainter>
#include <QPen>

#include <QDebug>


namespace Gui {

const int ObjectPanelItem::s_itemSize = 200;
const int ObjectPanelItem::s_squareSize = 35;
const int ObjectPanelItem::s_delta = 2;

ObjectPanelItem::ObjectPanelItem(QWidget* parent)
    : QWidget(parent)
    , m_object(nullptr)
    , m_isActiveItem(false)
{
    setFixedSize(s_itemSize, s_itemSize);
}

void ObjectPanelItem::paintEvent(QPaintEvent*)
{
    if (m_object == nullptr) {
        return;
    }
    QPainter* p = new QPainter(this);
    p->setPen(QPen(Qt::darkMagenta, 2));
    if (m_isActiveItem) {
        p->setPen(QPen(Qt::black, 3));
    }
    p->setBrush(QBrush(Qt::darkGray));

    Core::Object::Type type = m_object->getType();
    switch (type) {
        case Core::Object::Type::angled:
            drawAngledObject(p);
            break;
        case Core::Object::Type::linear:
            drawLinearObject(p);
            break;
        case Core::Object::Type::squared:
            drawSquaredObject(p);
            break;
        default:;
    }
    p->end();
}

void ObjectPanelItem::drawAngledObject(QPainter* p)
{
    Q_ASSERT(p != nullptr);
    Q_ASSERT(m_object != nullptr);
    Core::AngledObject* ao = static_cast<Core::AngledObject*>(m_object);
    Core::AngledObject::HorizontalDirection hdir = ao->getHorizontalDirection();
    Core::AngledObject::VerticalDirection vdir = ao->getVerticalDirection();
    const bool isLeft = hdir == Core::AngledObject::HorizontalDirection::left;
    const bool isTop = vdir == Core::AngledObject::VerticalDirection::top;
    int l = ao->getLength();
    int pos = (s_itemSize - (l * s_squareSize) - s_delta) / 2;
    int posY = isTop ? pos + (l * (s_squareSize) + s_delta) / 2 : pos;
    int posX = isLeft ? pos + (l * (s_squareSize + s_delta)) / 2 : pos;

    const QImage& img = ColorMap::getPreviewImage(ao, m_isActiveItem);
    p->drawImage(posX, posY, img);
    ///p->drawRect(posX, posY, s_squareSize, s_squareSize);
    int px = isLeft ? posX - (s_squareSize + s_delta) : posX + s_squareSize + s_delta;
    for (int i = 0; i < l - 1; ++i) {
        ///p->drawRect(px, posY, s_squareSize, s_squareSize);
        p->drawImage(px, posY, img);
        px = isLeft ? px - (s_squareSize + s_delta) : px + s_squareSize + s_delta;
    }

    int py = isTop ? posY - (s_squareSize + s_delta) : posY + s_squareSize + s_delta;
    px = posX;
    for (int i = 0; i < l - 1; ++i) {
        p->drawImage(px, py, img);
        ///p->drawRect(px, py, s_squareSize, s_squareSize);
        py = isTop ? py - (s_squareSize + s_delta) : py + s_squareSize + s_delta;
    }
}

void ObjectPanelItem::drawLinearObject(QPainter* p)
{
    Q_ASSERT(p != nullptr);
    Q_ASSERT(m_object != nullptr);
    Core::LinearObject* lo = static_cast<Core::LinearObject*>(m_object);
    int l = lo->getLength();
    int pos = (s_itemSize - (l * s_squareSize) - s_delta) / 2;
    Core::LinearObject::Direction dir = lo->getDirection();
    const QImage& img = ColorMap::getPreviewImage(lo, m_isActiveItem);
    for (int i = 0; i < l; ++i) {
        if (dir == Core::LinearObject::Direction::horizontal) {
            p->drawImage(pos, (s_itemSize - s_squareSize - s_delta) / 2, img);
            ///p->drawRect(pos, (s_itemSize - s_squareSize - s_delta) / 2, s_squareSize, s_squareSize);
        } else {
            p->drawImage((s_itemSize - s_squareSize - s_delta) / 2, pos, img);
            ///p->drawRect((s_itemSize - s_squareSize - s_delta) / 2, pos, s_squareSize, s_squareSize);
        }
        pos += s_squareSize + s_delta;
    }
}

void ObjectPanelItem::drawSquaredObject(QPainter* p)
{
    Q_ASSERT(p != nullptr);
    Q_ASSERT(m_object != nullptr);
    Core::SquaredObject* so = static_cast<Core::SquaredObject*>(m_object);
    int l = so->getLength();
    int pos = (s_itemSize - (l * s_squareSize) - s_delta) / 2;
    int posX = pos;
    int posY = pos;
    const QImage& img = ColorMap::getPreviewImage(so, m_isActiveItem);
    for (int row = 0; row < l; ++row) {
        for (int col = 0; col < l; ++col) {
            p->drawImage(posX, posY, img);
            ///p->drawRect(posX, posY, s_squareSize, s_squareSize);
            posX += s_squareSize + s_delta;
        }
        posX = pos;
        posY += s_squareSize + s_delta;
    }
}

void ObjectPanelItem::mouseReleaseEvent(QMouseEvent*)
{
    emit currentChanged(this);
}

void ObjectPanelItem::setActive(bool a) noexcept
{
    m_isActiveItem = a;
}

void ObjectPanelItem::setObject(Core::Object* o) noexcept
{
    m_object = o;
}

Core::Object* ObjectPanelItem::getObject() const noexcept
{
    return m_object;
}

} /// Gui namespace
