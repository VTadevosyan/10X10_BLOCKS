/// 10 X 10 BLOCKS

/**
  * @file Gui/MainPage.hpp
 **/


#ifndef __10X10_GUI_MAIN_PAGE_HPP
#define __10X10_GUI_MAIN_PAGE_HPP

#include <QWidget>


class QPaintEvent;

namespace Gui {

class PlayButton;

/// @class MainPage
class MainPage : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    MainPage(QWidget* = nullptr) noexcept;

    /// @brief Destructor
    ~MainPage();

public:
    /// @brief Draw foreground game board
    void paintEvent(QPaintEvent*) override;

signals:
    /// @brief Notifies when game is being launched
    void gameLaunched();

private:
    void setupLayout() noexcept;

private:
    PlayButton* m_playButton;

};

} /// Gui namespace

#endif // __10X10_GUI_MAIN_PAGE_HPP
