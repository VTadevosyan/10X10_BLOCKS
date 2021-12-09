/// 10 X 10

/**
  * @file Gui/EngineObserver.hpp
 **/

#ifndef __10X10_GUI_ENGINE_OBSERVER_HPP
#define __10X10_GUI_ENGINE_OBSERVER_HPP

#include "Core/ObserverInterface.hpp"


namespace Gui {

class MainWindow;
class View;

/// @class EngineObserver
class EngineObserver : public Core::ObserverInterface
{
public:
    /// @brief Create engine observer for Gui
    static void create(const MainWindow*, View*) noexcept;

    /// @brief Destroy engine observer
    static void destroy() noexcept;

    /// @brief Gets the engine observer
    static EngineObserver* get() noexcept;

public:
    /// @brief Constructor
    explicit EngineObserver(const MainWindow*, View*) noexcept;

    /// @brief update gui after modifying data
    void processData() override;

    /// @brief End game
    void notifyGameFinished() override;

private:
    static EngineObserver* m_engine_observer;

private:
    const MainWindow* m_main_window;
    View* m_view;
};

} /// Gui namespace

#endif // __10X10_GUI_ENGINE_OBSERVER_HPP
