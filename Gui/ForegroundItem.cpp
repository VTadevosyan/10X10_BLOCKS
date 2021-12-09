/// 10 X 10

/**
  * @file Gui/ForegroundItem.cpp
 **/

#include "Core/Index.hpp"

#include "Gui/ForegroundItem.hpp"

#include <QPainter>

#include <QDebug>

namespace Gui {

ForegroundItem::ForegroundItem(const QPointF& point, bool valid) noexcept
    : BaseItem(point)
    , m_isValid(valid)
{
}

QRectF ForegroundItem::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

void ForegroundItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    Q_ASSERT(painter != nullptr);
    if (isPosValid()) {
        painter->drawImage(QPointF(m_pos.x(), m_pos.y()), QImage("../Img/ForegroundItem.png"));
    }
}

} /// Gui namespace
