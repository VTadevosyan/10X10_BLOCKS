/// 10 X 10

/**
  * @file Gui/CentralWidget.hpp
 **/

#ifndef __10X10_GUI_CENTRAL_WIDGET_HPP
#define __10X10_GUI_CENTRAL_WIDGET_HPP

#include <QWidget>


namespace Gui {

class ObjectPanel;
class Scene;
class SettingsWidget;
class ScoreWidget;
class View;

/// @class CentralWidget
class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit CentralWidget(QWidget* = nullptr) noexcept;

    /// @brief Destructor
    virtual ~CentralWidget();

public:
    /// @brief Gets the view
    View* view() const noexcept;

    /// @brief Gets the score widget
    ScoreWidget* scoreWidget() const noexcept;

    /// @brief Gets the object panel
    ObjectPanel* objectPanel() const noexcept;

    /// @brief Gets the scene
    Scene* scene() const noexcept;

public slots:
    void setUsernameVisibility(int);
    void setUsername(const QString&);

signals:
    void settingsButtonClicked();

private:
    void setupLayout() noexcept;
    void connectWidgets() noexcept;
    void disconnectWidgets() noexcept;

private:
    View* m_view;
    SettingsWidget* m_settings;
    ScoreWidget* m_score;
    ObjectPanel* m_objects;
};

} /// Gui namespace

#endif // __10X10_GUI_CENTRAL_WIDGET_HPP
