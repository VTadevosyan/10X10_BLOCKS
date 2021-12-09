/// 10 X 10

/**
  * @file Gui/HighlightItem.cpp
 **/

#include "Core/Index.hpp"

#include "Gui/HighlightItem.hpp"

#include <QPainter>

#include <QDebug>

namespace Gui {

HighlightItem::HighlightItem(const QPointF& point, bool valid) noexcept
    : BaseItem(point)
    , m_isValid(valid)
{
}

QRectF HighlightItem::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

void HighlightItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    Q_ASSERT(painter != nullptr);
    if (isPosValid()) {
        painter->setPen(QPen(QBrush(m_isValid ? Qt::green : Qt::red), 5));
        painter->drawRect(m_pos.x(), m_pos.y(), 60, 60);
    }
}

} /// Gui namespace
