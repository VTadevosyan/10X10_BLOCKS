/// 10 X 10 BLOCKS

/**
  * @file Gui/Launcher.hpp
 **/

#ifndef __10X10_GUI_LAUNCHER_HPP
#define __10X10_GUI_LAUNCHER_HPP

#include <QApplication>
#include <QObject>


namespace Gui {

class MainPage;
class MainWindow;

} /// Gui namespace

namespace Game {

/// @class Launcher
class Launcher : public QObject
{
    Q_OBJECT

public:
    /// @brief Run game launcher
    static void run(QApplication&);

public:
    /// @brief Constructor
    Launcher(QApplication&);

    /// @brief Destructor
    ~Launcher();

private:
    void activateCore() const noexcept;
    void activateGui() const noexcept;
    void deactivateGui() const noexcept;
    void deactivateCore() const noexcept;
    void createWindows();
    void destroyWindows();
    void exec();
    void makeConnections() noexcept;
    void destroyConnections() noexcept;

private slots:
    void launchGame();

private:
    QApplication& m_application;
    Gui::MainPage* m_mainPage;
    Gui::MainWindow* m_mainWindow;
};

} /// Game namespace

#endif /// __10X10_GUI_LAUNCHER_HPP
