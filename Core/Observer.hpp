/// 10 X 10

/**
  * @file Core/Observer.hpp
 **/

#ifndef __10X10_CORE_OBSERVER_HPP
#define __10X10_CORE_OBSERVER_HPP

#include <list>


namespace Core {

class ObserverInterface;

/// @class Observer
class Observer
{
public:
    /// @brief Create observer
    static void create() noexcept;

    /// @brief Destroy observer
    static void destroy() noexcept;

    /// @brief Gets the observer
    static Observer* get() noexcept;

public:
    /// @brief Constructor
    Observer() noexcept;

    /// @brief Destructor
    virtual ~Observer() = default;

public:
    /// @brief register observer
    void registerObserver(ObserverInterface*) noexcept;

    /// @brief deregister observer
    void deregisterObserver(ObserverInterface*) noexcept;

    /// @brief pure virtual function for processing data after change notification
    virtual void processData();

    /// @brief end game notification
    virtual void notifyGameFinished();

private:
    static Observer* m_observer;

private:
    std::list<ObserverInterface*> m_interfaces;
};

} /// Core namespace


#endif // __10X10_CORE_OBSERVER_HPP
