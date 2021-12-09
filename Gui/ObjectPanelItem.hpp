/// 10 X 10

/**
  * @file Gui/ObjectPanelItem.hpp
 **/

#ifndef __10X10_GUI_OBJECT_PANEL_ITEM_HPP
#define __10X10_GUI_OBJECT_PANEL_ITEM_HPP

#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>


namespace Core {

class Object;

} /// Core namespace

namespace Gui {

/// @class ObjectPanelItem
class ObjectPanelItem : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    ObjectPanelItem(QWidget* = nullptr);

    /// @brief Destructor
    virtual ~ObjectPanelItem() = default;

public:
    /// @brief draw item
    void paintEvent(QPaintEvent*) override;

    /// @brief handle mouse press event
    /// void mousePressEvent(QMouseEvent*) override;

    /// @brief handle mouse release event
    void mouseReleaseEvent(QMouseEvent*) override;

    /// @brief mark as active object
    void setActive(bool) noexcept;

    /// @brief Sets the object for item
    void setObject(Core::Object*) noexcept;

    /// @brief Gets the object
    Core::Object* getObject() const noexcept;

signals:
    void currentChanged(ObjectPanelItem*);

private:
    void drawAngledObject(QPainter*);
    void drawLinearObject(QPainter*);
    void drawSquaredObject(QPainter*);

private:
    static const int s_itemSize;
    static const int s_squareSize;
    static const int s_delta;

private:
    Core::Object* m_object;
    bool m_isActiveItem;
};

} /// Gui namespace

#endif /// __10X10_GUI_OBJECT_PANEL_ITEM_HPP
