/// 10 X 10

/**
  * @file Gui/SettingsAssistant.cpp
 **/

#include "Gui/SettingsAssistant.hpp"
#include "Gui/SettingsEditor.hpp"


namespace Gui {

SettingsAssistant::SettingsAssistant(const QString& title, QWidget* parent)
    : QDockWidget(title, parent)
{
    m_editor = new SettingsEditor(this);
    setWidget(m_editor);
    setMinimumWidth(250);
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFont(QFont("Comic Sans MS", 12));
    setAutoFillBackground(true);

    connect(m_editor, SIGNAL(usernameVisibilityChanged(int)), this, SIGNAL(usernameVisibilityChanged(int)));
    connect(m_editor, SIGNAL(usernameChanged(const QString&)), this, SIGNAL(usernameChanged(const QString&)));

}

} /// Gui namespace
