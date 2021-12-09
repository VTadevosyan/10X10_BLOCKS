/// 10 X 10 BLOCKS

/**
  * @file Gui/Launcher.cpp
 **/

#include "Game/Launcher.hpp"

#include "Core/Engine.hpp"
#include "Core/Observer.hpp"

#include "Gui/CentralWidget.hpp"
#include "Gui/ColorMap.hpp"
#include "Gui/EngineObserver.hpp"
#include "Gui/HighlightController.hpp"
#include "Gui/MainPage.hpp"
#include "Gui/MainWindow.hpp"
#include "Gui/ObjectObserver.hpp"
#include "Gui/ScoreObserver.hpp"


namespace Game {

Launcher::Launcher(QApplication& app)
    : m_application(app)
    , m_mainPage(nullptr)
    , m_mainWindow(nullptr)
{
    activateCore();
    createWindows();
    activateGui();
    makeConnections();
}

Launcher::~Launcher()
{
    deactivateGui();
    deactivateCore();
    destroyConnections();
    destroyWindows();
}

void Launcher::run(QApplication& a)
{
    static Launcher l(a);
    l.exec();
}

void Launcher::launchGame()
{
    m_mainWindow->show();
    m_mainPage->hide();
    m_application.setActiveWindow(m_mainWindow);
}

void Launcher::exec()
{
    m_mainPage->show();
    m_application.setActiveWindow(m_mainPage);
}

void Launcher::createWindows()
{
    Q_ASSERT(m_mainPage == nullptr);
    Q_ASSERT(m_mainWindow == nullptr);
    m_mainPage = new Gui::MainPage;
    m_mainWindow = new Gui::MainWindow;
}

void Launcher::destroyWindows()
{
    Q_ASSERT(m_mainPage != nullptr);
    Q_ASSERT(m_mainWindow != nullptr);
    delete m_mainPage;
    delete m_mainWindow;
}

void Launcher::activateCore() const noexcept
{
    Core::Engine::create();
}

void Launcher::activateGui() const noexcept
{
    Gui::CentralWidget* cw = static_cast<Gui::CentralWidget*>(m_mainWindow->centralWidget());
    Gui::View* view = cw->view();
    Gui::ScoreWidget* score = cw->scoreWidget();
    Gui::ObjectPanel* objects = cw->objectPanel();
    Gui::EngineObserver::create(m_mainWindow, view);
    Gui::ScoreObserver::create(score);
    Gui::ObjectObserver::create(objects);
    Core::Observer::get()->registerObserver(Gui::EngineObserver::get());
    Core::Observer::get()->registerObserver(Gui::ScoreObserver::get());
    Core::Observer::get()->registerObserver(Gui::ObjectObserver::get());
    Gui::HighlightController::create(cw->scene());
    Gui::ColorMap::create();
}

void Launcher::deactivateGui() const noexcept
{
    Core::Observer::get()->deregisterObserver(Gui::EngineObserver::get());
    Core::Observer::get()->deregisterObserver(Gui::ScoreObserver::get());
    Core::Observer::get()->deregisterObserver(Gui::ObjectObserver::get());
    Gui::EngineObserver::destroy();
    Gui::ScoreObserver::destroy();
    Gui::ObjectObserver::destroy();
    Gui::HighlightController::destroy();
    Gui::ColorMap::destroy();
}

void Launcher::deactivateCore() const noexcept
{
    Core::Engine::destroy();
}

void Launcher::makeConnections() noexcept
{
    connect(m_mainPage, SIGNAL(gameLaunched()), this, SLOT(launchGame()));
}

void Launcher::destroyConnections() noexcept
{
    disconnect(m_mainPage, SIGNAL(gameLaunched()), this, SLOT(launchGame()));
}

} /// Game namespace
