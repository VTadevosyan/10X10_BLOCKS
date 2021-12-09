/// 10 X 10

/**
  * @file Gui/HighlightItem.hpp
 **/

#ifndef __10X10_GUI_HIGHLIGHT_ITEM_HPP
#define __10X10_GUI_HIGHLIGHT_ITEM_HPP

#include "Gui/BaseItem.hpp"


namespace Gui {

/// @class HighlightItem
class HighlightItem : public BaseItem
{
public:
    /// @brief Constructor
    explicit HighlightItem(const QPointF&, bool) noexcept;

public:
    /// @briefr Gets the bounding rectangle
    QRectF boundingRect() const override;

    /// @brief paint item
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = nullptr) override;

private:
    bool m_isValid;

};

} /// Gui namespace

#endif // __10X10_GUI_HIGHLIGHT_ITEM_HPP
