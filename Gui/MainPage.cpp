/// 10 X 10 BLOCKS

/**
  * @file Gui/MainPage.cpp
 **/

#include "Gui/Editors.hpp"
#include "Gui/MainPage.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


namespace Gui {

MainPage::MainPage(QWidget* parent) noexcept
    : QWidget(parent)
    , m_playButton(new PlayButton(this))
{
    setFixedSize(406, 626);
    setWindowIcon(QIcon("../Img/10X10.png"));
    setWindowTitle("10X10 BLOCKS");
    setupLayout();
    setFont(QFont("Comic Sans MS", 25));
    connect(m_playButton, SIGNAL(gameLaunched()), this, SIGNAL(gameLaunched()));
}

MainPage::~MainPage()
{
    disconnect(m_playButton, SIGNAL(gameLaunched()), this, SIGNAL(gameLaunched()));
}


void MainPage::setupLayout() noexcept
{
    QHBoxLayout* hl1 = new QHBoxLayout;
    QHBoxLayout* hl2 = new QHBoxLayout;
    QVBoxLayout* vl = new QVBoxLayout(this);
    hl1->addStretch();
    hl1->addWidget(new BestScoreWidget(this));
    hl1->addStretch();
    hl2->addStretch();
    hl2->addWidget(m_playButton);
    hl2->addStretch();
    vl->addLayout(hl1);
    vl->addStretch();
    vl->addLayout(hl2);
    vl->addStretch();
}

void MainPage::paintEvent(QPaintEvent*)
{
    QPainter* p = new QPainter(this);
    p->drawImage(0, 0, QImage("../Img/MainPageBG.png"));
    p->end();
}


} /// Gui namespace
