/// 10 X 10

/**
  * @file Gui/EngineObserver.cpp
 **/

#include "Gui/EngineObserver.hpp"
#include "Gui/MainWindow.hpp"
#include "Gui/View.hpp"

#include <iostream>


namespace Gui {

EngineObserver* EngineObserver::m_engine_observer = nullptr;

void EngineObserver::create(const MainWindow* mw, View* v) noexcept
{
    if (m_engine_observer == nullptr) {
        m_engine_observer = new EngineObserver(mw, v);
    }
}

void EngineObserver::destroy() noexcept
{
    if (m_engine_observer != nullptr) {
        delete m_engine_observer;
        m_engine_observer = nullptr;
    }
}

EngineObserver* EngineObserver::get() noexcept
{
    return m_engine_observer;
}

EngineObserver::EngineObserver(const MainWindow* mw, View* v) noexcept
    : Core::ObserverInterface()
    , m_main_window(mw)
    , m_view(v)
{
    Q_ASSERT(m_view != nullptr);
}

void EngineObserver::processData()
{
    if (m_view != nullptr) {
        m_view->redrawItems();
    }
}

void EngineObserver::notifyGameFinished()
{
    m_main_window->notifyGameFinished();
}

} /// Gui namespace
