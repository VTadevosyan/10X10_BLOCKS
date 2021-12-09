/// 10 X 10

/**
  * @file Gui/ForegroundItem.hpp
 **/

#ifndef __10X10_GUI_FOREGROUND_ITEM_HPP
#define __10X10_GUI_FOREGROUND_ITEM_HPP

#include "Gui/BaseItem.hpp"


namespace Gui {

/// @class ForegroundItem
class ForegroundItem : public BaseItem
{
public:
    /// @brief Constructor
    explicit ForegroundItem(const QPointF&, bool) noexcept;

public:
    QRectF boundingRect() const override;

    /// @brief paint item
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = nullptr) override;

private:
    bool m_isValid;

};

} /// Gui namespace

#endif // __10X10_GUI_FOREGROUND_ITEM_HPP
