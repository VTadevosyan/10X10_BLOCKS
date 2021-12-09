/// 10 X 10

/**
  * @file Gui/SettingsWidget.hpp
 **/

#ifndef __10X10_GUI_SETTINGS_WIDGET_HPP
#define __10X10_GUI_SETTINGS_WIDGET_HPP

#include <QWidget>


class QLabel;
class QPushButton;

namespace Gui {

/// @class SettingsWidget
class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    SettingsWidget(QWidget *parent = nullptr);

    /// @brief Destructor
    virtual ~SettingsWidget() = default;

signals:
    void settingsButtonClicked();

public slots:
    /// @brief Sets the new score value
    void updateRecord(unsigned long) noexcept;

private:
    void setupLayout();
    void createSettingsButton();
    void createRecordScoreIconWidget();
    void createRecordScoreWidget();

private:
    QPushButton* m_settings;
    QLabel* m_record_icon;
    QLabel* m_record_score;
};

} /// Gui namespace

#endif // __10X10_GUI_SETTINGS_WIDGET_HPP
