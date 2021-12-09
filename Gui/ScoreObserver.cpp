/// 10 X 10

/**
  * @file Gui/ScoreObserver.cpp
 **/

#include "Core/Engine.hpp"

#include "Gui/ScoreObserver.hpp"
#include "Gui/ScoreWidget.hpp"
#include "Gui/View.hpp"


namespace Gui {

ScoreObserver* ScoreObserver::m_score_observer = nullptr;

void ScoreObserver::create(ScoreWidget* v) noexcept
{
    if (m_score_observer == nullptr) {
        m_score_observer = new ScoreObserver(v);
    }
}

void ScoreObserver::destroy() noexcept
{
    if (m_score_observer != nullptr) {
        delete m_score_observer;
        m_score_observer = nullptr;
    }
}

ScoreObserver* ScoreObserver::get() noexcept
{
    return m_score_observer;
}

ScoreObserver::ScoreObserver(ScoreWidget* s) noexcept
    : m_score_widget(s)
{
    Q_ASSERT(m_score_widget != nullptr);
}

void ScoreObserver::processData()
{
    if (m_score_widget != nullptr) {
        Core::Engine* e = Core::Engine::get();
        Q_ASSERT(e != nullptr);
        m_score_widget->setValue(e->getScore());
    }
}

} /// Gui namespace
