/// 10 X 10

/**
  * @file Core/Observer.cpp
 **/

#include "Core/Observer.hpp"
#include "Core/ObserverInterface.hpp"

#include <algorithm>


namespace Core {

Observer* Observer::m_observer = nullptr;

void Observer::create() noexcept
{
    if (m_observer == nullptr) {
        m_observer = new Observer;
    }
}

void Observer::destroy() noexcept
{
    if (m_observer != nullptr) {
        delete m_observer;
        m_observer = nullptr;
    }
}

Observer* Observer::get() noexcept
{
    return m_observer;
}

Observer::Observer() noexcept
{
}

void Observer::registerObserver(ObserverInterface* i) noexcept
{
    if (i == nullptr) {
        return;
    }
    auto it = std::find(m_interfaces.begin(), m_interfaces.end(), i);
    if (it == m_interfaces.end()) {
        m_interfaces.push_back(i);
    }
}

void Observer::deregisterObserver(ObserverInterface* i) noexcept
{
    if (i == nullptr) {
        return;
    }
    auto it = std::find(m_interfaces.begin(), m_interfaces.end(), i);
    if (it != m_interfaces.end()) {
        m_interfaces.remove(i);
    }
}

void Observer::processData()
{
    for (auto it : m_interfaces) {
        if (it != nullptr) {
            it->processData();
        }
    }
}

void Observer::notifyGameFinished()
{
    for (auto it : m_interfaces) {
        if (it != nullptr) {
            it->notifyGameFinished();
        }
    }
}

} /// Core namespace
