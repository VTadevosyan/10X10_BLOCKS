/// 10 X 10

/**
  * @file Core/Observer.hpp
 **/

#ifndef __10X10_CORE_OBSERVER_INTERFACE_HPP
#define __10X10_CORE_OBSERVER_INTERFACE_HPP


namespace Core {

/// @class ObserverInterface
class ObserverInterface
{
public:
    /// @brief Constructor
    ObserverInterface() noexcept = default;

    /// @brief Destructor
    virtual ~ObserverInterface() = default;

public:
    /// @brief pure virtual function for processing data after change notification
    virtual void processData() = 0;

    /// @brief pure virtual function for processing finishing game
    virtual void notifyGameFinished() = 0;

};

} /// Core namespace

#endif /// __10X10_CORE_OBSERVER_INTERFACE_HPP
