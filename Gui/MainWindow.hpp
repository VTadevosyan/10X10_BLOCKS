/// 10 X 10

/**
  * @file Gui/MainWindow.hpp
 **/

#ifndef __10X10_GUI_MAIN_WINDOW_HPP
#define __10X10_GUI_MAIN_WINDOW_HPP

#include <QCloseEvent>
#include <QMainWindow>


namespace Gui {

class CentralWidget;
class SettingsAssistant;

/// @class MainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Constructor
    MainWindow(QWidget *parent = nullptr);

    /// @brief Destructor
    ~MainWindow();

public:
    /// @brief Handle application close event
    void closeEvent(QCloseEvent*) override;

    void paintEvent(QPaintEvent*) override;

    /// @brief Notify to finish game
    void notifyGameFinished() const;

signals:
    void gameFinished() const;

private slots:
    void finishGame() noexcept;
    void setSettingsAssistantVisible() noexcept;

private:
    void connectWidgets() noexcept;
    void disconnectWidgets() noexcept;

private:
    CentralWidget* m_CentralWidget;
    SettingsAssistant* m_settingsAssistant;
};

} /// Gui namespace

#endif // __10X10_GUI_MAIN_WINDOW_HPP
