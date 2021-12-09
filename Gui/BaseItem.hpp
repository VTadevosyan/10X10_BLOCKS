/// 10 X 10

/**
  * @file Gui/BaseItem.hpp
 **/

#ifndef __10X10_GUI_BASE_ITEM_HPP
#define __10X10_GUI_BASE_ITEM_HPP

#include "Core/Index.hpp"
#include "Core/Object.hpp"

#include <QGraphicsItem>

#include <map>


namespace Gui {

/// @class Item
class BaseItem : public QGraphicsItem
{
public:
    /// @brief Item fixed width with pixels
    static int width() noexcept;

    /// @brief Item fixed height with pixels
    static int height() noexcept;

    /// @brief Gets the item position from index
    static QPointF indexToPos(const Core::Index& index) noexcept;

public:
    /// @brief Constructor
    BaseItem(const Core::Index&);

    /// @brief Constructor
    BaseItem(const QPointF& p);

    /// @brief bounding rectangle: need to override
    virtual QRectF boundingRect() const = 0;

    /// @brief paint item: need to override
    virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = nullptr) = 0;

protected:
    /// @brief Check pos validity
    bool isPosValid() const noexcept;

protected:
    Core::Index m_index;
    QPointF m_pos;

};

} /// Gui namespace

#endif // __10X10_GUI_BASE_ITEM_HPP
