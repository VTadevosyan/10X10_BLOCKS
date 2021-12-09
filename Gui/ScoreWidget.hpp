/// 10 X 10

/**
  * @file Gui/ScoreWidget.hpp
 **/

#ifndef __10X10_GUI_SCORE_WIDGET_HPP
#define __10X10_GUI_SCORE_WIDGET_HPP

#include <QWidget>


class QLabel;

namespace Gui {

/// @class ScoreWidget
class ScoreWidget : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    ScoreWidget(QWidget *parent = nullptr);

    /// @brief Destructor
    virtual ~ScoreWidget() = default;

public:
    /// @brief Sets the new score value
    void setValue(unsigned long) noexcept;

    void setUsernameVisibility(int) noexcept;
    void setUsername(const QString&) noexcept;

signals:
    /// @brief This signal emitted when score value is changed
    /// called from setValue function
    void scoreChanged(unsigned long);

private:
    void setupLayout();
    void createUsernameWidget();
    void createScoreIconWidget();
    void createScoreWidget();

private:
    QLabel* m_username;
    QLabel* m_score_icon;
    QLabel* m_score;
};

} /// Gui namespace

#endif // __10X10_GUI_SCORE_WIDGET_HPP
