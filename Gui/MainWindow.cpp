/// 10 X 10

/**
  * @file Gui/MainWindow.cpp
 **/

#include "Core/Engine.hpp"
#include "Core/ObjectBuilder.hpp"
#include "Core/Observer.hpp"

#include "Gui/CentralWidget.hpp"
#include "Gui/ColorMap.hpp"
#include "Gui/EngineObserver.hpp"
#include "Gui/HighlightController.hpp"
#include "Gui/MainWindow.hpp"
#include "Gui/SettingsAssistant.hpp"
#include "Gui/ObjectObserver.hpp"
#include "Gui/ScoreObserver.hpp"

#include <QApplication>
#include <QMessageBox>

#include <qdebug.h>


namespace Gui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_CentralWidget(nullptr)
{
    m_CentralWidget = new CentralWidget(this);
    m_settingsAssistant = new SettingsAssistant("Settings", this);

    setCentralWidget(m_CentralWidget);
    setFont(QFont("Comic Sans MS", 25));
    setWindowIcon(QIcon("../Img/10X10.png"));
    setWindowTitle("10X10 BLOCKS");
    addDockWidget(Qt::RightDockWidgetArea, m_settingsAssistant);
    QPalette p;
    p.setBrush(QPalette::Window, QBrush(QColor(240, 237, 225)/*Qt::white*/));
    setPalette(p);
    connectWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::connectWidgets() noexcept
{
    connect(this, SIGNAL(gameFinished()), this, SLOT(finishGame()));
    connect(m_CentralWidget, SIGNAL(settingsButtonClicked()), this, SLOT(setSettingsAssistantVisible()));
    connect(m_settingsAssistant, SIGNAL(usernameVisibilityChanged(int)), m_CentralWidget, SLOT(setUsernameVisibility(int)));
    connect(m_settingsAssistant, SIGNAL(usernameChanged(const QString&)), m_CentralWidget, SLOT(setUsername(const QString&)));
}

void MainWindow::disconnectWidgets() noexcept
{
    disconnect(this, SIGNAL(gameFinished()), this, SLOT(finishGame()));
    disconnect(m_CentralWidget, SIGNAL(settingsButtonClicked()), this, SLOT(setSettingsAssistantVisible()));
    disconnect(m_settingsAssistant, SIGNAL(usernameVisibilityChanged(int)), m_CentralWidget, SLOT(setUsernameVisibility(int)));
    disconnect(m_settingsAssistant, SIGNAL(usernameChanged(const QString&)), m_CentralWidget, SLOT(setUsername(const QString&)));
}

void MainWindow::paintEvent(QPaintEvent*)
{
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    Q_ASSERT(e != nullptr);
    const QString text = "Your Score Is: " + QString::fromStdString(std::to_string(Core::Engine::get()->getScore()) + "!");
    QMessageBox::StandardButton btn = QMessageBox::warning(this, "Game Finished!", text);
    if (btn == QMessageBox::Ok) {
        e->accept();
        exit(0);
    }
}

void MainWindow::finishGame() noexcept
{
    QCloseEvent event;
    QApplication::sendEvent(this, &event);
}

void MainWindow::notifyGameFinished() const
{
    emit gameFinished();
}

void MainWindow::setSettingsAssistantVisible() noexcept
{
    m_settingsAssistant->setVisible(!m_settingsAssistant->isVisible());
}

} /// Gui namespace
