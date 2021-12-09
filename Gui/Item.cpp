/// 10 X 10

/**
  * @file Gui/Item.cpp
 **/

#include "Gui/ColorMap.hpp"
#include "Gui/Item.hpp"

#include <QPainter>

#include <qdebug.h>


namespace Gui {

int Item::width() noexcept
{
    return 60;
}

int Item::height() noexcept
{
    return 60;
}

QPointF Item::indexToPos(const Core::Index& index) noexcept
{
    Q_ASSERT(index.isValid());
    return QPointF(index.column() * width(), index.row() * height());
}

Item::Item(const Core::Index& index, Core::Object* const o)
    : BaseItem(index)
    , m_object(o)
{
    Q_ASSERT(m_index.isValid());
    m_pos = indexToPos(m_index);
}

QColor Item::retrieveColor() const noexcept
{
    return Qt::darkCyan;
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    Q_ASSERT(painter != nullptr);
    if (isPosValid()) {
        ColorMap* cm = ColorMap::get();
        Q_ASSERT(cm != nullptr);
        painter->setPen(QColor(Qt::green));

        ///painter->setBrush(QBrush(cm->getColor(m_index)));
        ///painter->drawRect(m_pos.x() + 2, m_pos.y() + 2, 56, 56);
        //// QColor clr = cm->getColor(m_index);
        painter->drawImage(m_pos, cm->getImage(m_index));
    }
}

QRectF Item::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

Core::Index Item::getIndex() const noexcept
{
    return m_index;
}

} /// Gui namespace
