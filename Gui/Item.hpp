/// 10 X 10

/**
  * @file Gui/Item.hpp
 **/

#ifndef __10X10_GUI_ITEM_HPP
#define __10X10_GUI_ITEM_HPP

#include "Core/Index.hpp"
#include "Core/Object.hpp"

#include "Gui/BaseItem.hpp"

#include <QGraphicsItem>

#include <map>


namespace Gui {

/// @class Item
class Item : public BaseItem
{
public:
    /// @brief Item fixed width with pixels
    static int width() noexcept;

    /// @brief Item fixed height with pixels
    static int height() noexcept;

    /// @brief Gets the item position from index
    static QPointF indexToPos(const Core::Index&) noexcept;

public:
    /// @brief Constructor
    Item(const Core::Index&, Core::Object* const);

    /// @brief Destructor
    virtual ~Item() = default;

public:
    /// @brief bounding rectangle
    QRectF boundingRect() const override;

    /// @brief paint item
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = nullptr) override;

    /// @brief Gets the item index
    Core::Index getIndex() const noexcept;

private:
    QColor retrieveColor() const noexcept;

private:
    Core::Object* const m_object;
};

} /// Gui namespace

#endif // __10X10_GUI_ITEM_HPP
