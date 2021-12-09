/// 10 X 10

/**
  * @file Gui/ScoreObserver.hpp
 **/

#ifndef __10X10_GUI_SCORE_OBSERVER_HPP
#define __10X10_GUI_SCORE_OBSERVER_HPP

#include "Core/ObserverInterface.hpp"


namespace Gui {

class ScoreWidget;

/// @class ScoreObserver
class ScoreObserver : public Core::ObserverInterface
{
public:
    /// @brief Create score observer for Gui
    static void create(ScoreWidget*) noexcept;

    /// @brief Destroy score observer
    static void destroy() noexcept;

    /// @brief Gets the score observer
    static ScoreObserver* get() noexcept;

public:
    /// @brief Constructor
    explicit ScoreObserver(ScoreWidget*) noexcept;

    /// @brief update gui after modifying data
    void processData() override;

    /// @brief finishing game
    void notifyGameFinished() override {}

private:
    static ScoreObserver* m_score_observer;

private:
    ScoreWidget* m_score_widget;

};

} // Gui namespace

#endif /// __10X10_GUI_SCORE_OBSERVER_HPP
