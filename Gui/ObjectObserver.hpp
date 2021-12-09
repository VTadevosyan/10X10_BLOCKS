/// 10 X 10

/**
  * @file Gui/EngineObserver.hpp
 **/

#ifndef __10X10_GUI_OBJECT_OBSERVER_HPP
#define __10X10_GUI_OBJECT_OBSERVER_HPP

#include "Core/ObserverInterface.hpp"


namespace Gui {

class ObjectPanel;

//// @class ObjectObserver
class ObjectObserver : public Core::ObserverInterface
{
public:
    /// @brief Create engine observer for Gui
    static void create(ObjectPanel*) noexcept;

    /// @brief Destroy engine observer
    static void destroy() noexcept;

    /// @brief Gets the engine observer
    static ObjectObserver* get() noexcept;

public:
    /// @brief Constructor
    explicit ObjectObserver(ObjectPanel*) noexcept;

    /// @brief update gui after modifying data
    void processData() override;

    /// @brief finishing game
    void notifyGameFinished() override {}

private:
    static ObjectObserver* m_object_observer;

private:
    ObjectPanel* m_objectPanel;
};

}/// Gui namespace

#endif // __10X10_GUI_OBJECT_OBSERVER_HPP
