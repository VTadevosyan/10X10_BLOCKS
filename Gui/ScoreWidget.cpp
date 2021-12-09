/// 10 X 10

/**
  * @file Gui/ScoreWidget.cpp
 **/

#include "Core/Board.hpp"
#include "Core/Engine.hpp"

#include "Gui/Item.hpp"
#include "Gui/ScoreWidget.hpp"

#include <QLabel>
#include <QHBoxLayout>
#include <QPicture>


namespace Gui {

ScoreWidget::ScoreWidget(QWidget* parent)
    : QWidget(parent)
{
    createUsernameWidget();
    createScoreIconWidget();
    createScoreWidget();
    setupLayout();
    setFixedSize(Item::width() * Core::Board::size(), 75);
}

void ScoreWidget::createUsernameWidget()
{
    m_username = new QLabel("USERNAME", this);
    m_username->setFixedWidth(250);
    m_username->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void ScoreWidget::createScoreIconWidget()
{
    m_score_icon = new QLabel(this);
    QPixmap pm("../Img/Score.png");
    m_score_icon->setPixmap(pm);
    m_score_icon->setFixedWidth(60);
    m_score_icon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void ScoreWidget::createScoreWidget()
{
    m_score = new QLabel("0", this);
    m_score->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_score->setFixedWidth(145);
}

void ScoreWidget::setupLayout()
{
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(m_username);
    l->addStretch(1);

    l->addWidget(m_score);
    l->addWidget(m_score_icon);
    setLayout(l);
}

void ScoreWidget::setValue(unsigned long value) noexcept
{
    Q_ASSERT(m_score != nullptr);
    m_score->setText(QString::fromStdString(std::to_string(value)));
    emit scoreChanged(value);
}

void ScoreWidget::setUsernameVisibility(int state) noexcept
{
    Q_ASSERT(m_username != nullptr);
    m_username->setVisible(state != Qt::Unchecked);
}

void ScoreWidget::setUsername(const QString& username) noexcept
{
    Q_ASSERT(m_username != nullptr);
    m_username->setText(username);
}

} /// Gui namespace
