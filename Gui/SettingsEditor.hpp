/// 10 X 10 BLOCKS

/**
  * @file Gui/SettingsEditor.hpp
 **/

#ifndef __10X10_GUI_SETTINGS_EDITOR_HPP
#define __10X10_GUI_SETTINGS_EDITOR_HPP

#include <QWidget>


class QCheckBox;

namespace Gui {

class CheckBoxEditor;
class LineEditor;

class SettingsEditor : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    SettingsEditor(QWidget *parent = nullptr);

    /// @brief Destructor
    virtual ~SettingsEditor() = default;

signals:
    void usernameVisibilityChanged(int);
    void usernameChanged(const QString&);

private:
    void connectWidgets() noexcept;

private:
    CheckBoxEditor* m_usernameVisibilityEditor;
    LineEditor* m_usernameEditor;
};

} /// Gui namespace

#endif // __10X10_GUI_SETTINGS_EDITOR_HPP
