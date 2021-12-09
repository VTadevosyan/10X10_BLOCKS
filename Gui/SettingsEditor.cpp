/// 10 X 10 BLOCKS

/**
  * @file Gui/SettingsEditor.cpp
  */

#include <Gui/Editors.hpp>
#include "Gui/SettingsEditor.hpp"

#include <QCheckBox>
#include <QVBoxLayout>


namespace Gui {

SettingsEditor::SettingsEditor(QWidget* parent)
    : QWidget(parent)
{
    m_usernameVisibilityEditor = new CheckBoxEditor("Show Username: ", this);
    m_usernameEditor = new LineEditor("Username: ", this);
    m_usernameEditor->setOption("Option__Username");
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_usernameVisibilityEditor);
    l->addWidget(m_usernameEditor);
    l->addStretch(1);
    setLayout(l);
    connectWidgets();
}

void SettingsEditor::connectWidgets() noexcept
{
    connect(m_usernameVisibilityEditor, SIGNAL(valueChanged(int)), this, SIGNAL(usernameVisibilityChanged(int)));
    connect(m_usernameEditor, SIGNAL(valueChanged(const QString&)), this, SIGNAL(usernameChanged(const QString&)));
}

} /// Gui namespace
