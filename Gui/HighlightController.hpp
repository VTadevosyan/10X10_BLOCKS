/// 10 X 10

/**
  * @file Gui/HighlightController.hpp
 **/

#ifndef __10X10_GUI_HIGHLIGHT_CONTROLLER_HPP
#define __10X10_GUI_HIGHLIGHT_CONTROLLER_HPP

#include <QPointF>

#include <list>


namespace Core {

class Object;

} /// Core namespace

namespace Gui {

class HighlightItem;
class Scene;

/// @class HighlightController
class HighlightController
{
public:
    /// @brief Create engine
    static void create(Scene*) noexcept;

    /// @brief Destroy engine
    static void destroy() noexcept;

    /// @brief Gets the engine
    static HighlightController* get() noexcept;

public:
    /// @brief Constructor
    HighlightController(Scene*) noexcept;

public:
    /// @brief highlight object
    void highlight(Core::Object* const, const QPointF&);

    /// @brief clears the current highlight
    void clearHighlight();

private:
    void higlightAngledObject(Core::Object* const, const QPointF&);
    void higlightLinearObject(Core::Object* const, const QPointF&);
    void higlightSquaredObject(Core::Object* const, const QPointF&);
    void addItem(const QPointF&, bool = false);

private:
    static HighlightController* m_highlightController;

private:
    std::list<HighlightItem*> m_highlightItems;
    Scene* m_scene;
};

} /// Gui namespace

#endif // __10X10_GUI_HIGHLIGHT_CONTROLLER_HPP
