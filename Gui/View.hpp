/// 10 X 10

/**
  * @file Gui/View.hpp
 **/

#ifndef __10X10_GUI_VIEW_HPP
#define __10X10_GUI_VIEW_HPP

#include <QGraphicsView>
#include <QFocusEvent>
#include <QMouseEvent>

#include <map>


namespace Core {

class Index;
class Object;

} /// Core namespace

namespace Gui {

class Item;
class Scene;

/// @class View
class View : public QGraphicsView
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit View(QWidget* = nullptr);

    /// @brief Destructor
    virtual ~View() = default;

public:
    /// @brief Draw foreground game board
    void drawBackground(QPainter*, const QRectF&) override;

    /// @brief Draw foreground game board
    void drawForeground(QPainter*, const QRectF&) override;

    /// @brief mouse move event
    void mouseMoveEvent(QMouseEvent*) override;

    /// @brief mouse press event
    void mousePressEvent(QMouseEvent*) override;

    /// @brief focus out event
    void leaveEvent(QEvent*) override;

public:
    /// @brief Gets the width of View
    int width() const noexcept;

    /// @brief Gets the height of View
    int height() const noexcept;

    /// @brief Gets the scene
    Scene* getScene() const noexcept;

public:
    /// @brief Redraw board items
    void redrawItems();

public slots:
    /// @brief Set current object
    void setObject(Core::Object*) noexcept;

private:
    void drawBoard(QPainter*) noexcept;
    void clearItems() noexcept;

private:
    std::list<Item*> m_items;
    std::map<Core::Index*, QColor> m_colorMap;
    Scene* m_scene;
    Core::Object* m_object;
};

} /// Gui namespace

#endif // __10X10_GUI_VIEW_HPP
