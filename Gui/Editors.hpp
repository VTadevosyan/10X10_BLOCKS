/// 10 X 10 BLOCKS

/**
  * @file Gui/Editors.hpp
 **/

#ifndef __10X10_GUI_EDITORS_HPP
#define __10X10_GUI_EDITORS_HPP

#include <QWidget>

class QCheckBox;
class QEvent;
class QLabel;
class QLineEdit;
class QMouseEvent;



namespace Gui {

/// @class PlayButton
class PlayButton : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    PlayButton(QWidget* = nullptr) noexcept;

    /// @brief Draw play logo
    void paintEvent(QPaintEvent*) override;

    /// @brief Emits the signalu about launching game
    void mousePressEvent(QMouseEvent*) override;

    /// @brief Reimplements enter event. Highlights the play logo
    void enterEvent(QEvent*) override;

    /// @brief Reimplements leave event. Clears highlight from play logo
    void leaveEvent(QEvent*) override;

signals:
    /// @brief This signal will be emitted when clicked on play logo
    void gameLaunched();

private:
    bool m_isActive;
};

/// @class BestScoreWidget
class BestScoreWidget : public QWidget
{
    Q_OBJECT

public:
    BestScoreWidget(QWidget* = nullptr) noexcept;

private:
    void createIconLabel() noexcept;
    void createBestScoreLabel() noexcept;
    void setupLayout() noexcept;

private:
    QLabel* m_iconLabel;
    QLabel* m_bestScoreLabel;
};

/// @class Editor
class Editor : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit Editor(const QString&, QWidget* = nullptr) noexcept;

    /// @brief Destructor
    virtual ~Editor() = default;

public:
    /// @brief Sets the option name for editor
    /// If the option name is specified editor will update option value too
    void setOption(const std::string&) noexcept;

    /// @brief Updates the option value
    void updateOption(std::string&&) noexcept;

protected:
    QLabel* m_label;

private:
    std::string m_optionName;

};

/// @class LineEditor
class LineEditor : public Editor
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit LineEditor(const QString&, QWidget* = nullptr) noexcept;

    /// @brief Destructor
    virtual ~LineEditor() = default;

signals:
    void valueChanged(const QString&);

private slots:
    void updateValue(const QString&);

private:
    void setupLayout() noexcept;

private:
    QLineEdit* m_editor;

};


/// @class CheckBoxEditor
class CheckBoxEditor : public Editor
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit CheckBoxEditor(const QString&, QWidget* = nullptr) noexcept;

    /// @brief Destructor
    virtual ~CheckBoxEditor() = default;

signals:
    void valueChanged(int);

private:
    void setupLayout() noexcept;

private:
    QCheckBox* m_editor;

};

} /// Gui namespace

#endif // __10X10_GUI_EDITORS_HPP
