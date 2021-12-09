/// 10 X 10

/**
  * @file Gui/SettingsAssistant.hpp
 **/

#ifndef __10X10_GUI_SETTINGS_ASSISTANT_HPP
#define __10X10_GUI_SETTINGS_ASSISTANT_HPP

#include <QDockWidget>


namespace Gui {

class SettingsEditor;

/// @class SettingsAssistant
class SettingsAssistant : public QDockWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    SettingsAssistant(const QString&, QWidget *parent = nullptr);

    /// @brief Destructor
    virtual ~SettingsAssistant() = default;

signals:
    void usernameVisibilityChanged(int);
    void usernameChanged(const QString&);

private:
    SettingsEditor* m_editor;

};

} /// Gui namespace

#endif // __10X10_GUI_SETTINGS_ASSISTANT_HPP
