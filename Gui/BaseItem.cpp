/// 10 X 10

/**
  * @file Gui/BaseItem.hpp
 **/

#include "Gui/BaseItem.hpp"


namespace Gui {

int BaseItem::width() noexcept
{
    return 60;
}

int BaseItem::height() noexcept
{
    return 60;
}

QPointF BaseItem::indexToPos(const Core::Index& index) noexcept
{
    Q_ASSERT(index.isValid());
    return QPointF(index.row() * width(), index.column() * height());
}

BaseItem::BaseItem(const Core::Index& i)
    : m_index(i)
    , m_pos(indexToPos(m_index))
{

}

BaseItem::BaseItem(const QPointF& p)
{
    m_index = Core::Index::posToIndex(p, width(), height());
    m_pos = QPointF(m_index.column() * width(), m_index.row() * height());
}

bool BaseItem::isPosValid() const noexcept
{
    return m_pos != QPointF(-1, -1);
}

} /// Gui namespace
