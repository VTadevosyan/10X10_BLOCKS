/// 10 X 10 BLOCKS

/**
  * @file Gui/SettingsWidget.cpp
  */

#include "Core/Board.hpp"
#include "Core/Engine.hpp"

#include "Gui/Editors.hpp"
#include "Gui/Item.hpp"
#include "Gui/SettingsWidget.hpp"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>


namespace Gui {

SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent)
{
    createSettingsButton();

    /*createRecordScoreWidget();
    createRecordScoreIconWidget();*/
    setupLayout();
    setFixedSize(Item::width() * Core::Board::size(), 80);
}

void SettingsWidget::setupLayout()
{
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(m_settings);
    l->addStretch(1);
    l->addWidget(new BestScoreWidget(this));
    /*l->addWidget(m_record_score);
    l->addWidget(m_record_icon);*/
    setLayout(l);
}

void SettingsWidget::createSettingsButton()
{
    m_settings = new QPushButton(QIcon("../Img/Settings.png"), "", this);
    m_settings->setFixedSize(60, 60);
    m_settings->setIconSize(QSize(50, 50));
    connect(m_settings, SIGNAL(clicked()), this, SIGNAL(settingsButtonClicked()));
}

void SettingsWidget::createRecordScoreIconWidget()
{
    m_record_icon = new QLabel(this);
    QPixmap pm("../Img/Record.png");
    m_record_icon->setPixmap(pm);
    m_record_icon->setFixedWidth(60);
    m_record_icon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void SettingsWidget::createRecordScoreWidget()
{
    QString record = QString::fromStdString(std::to_string(Core::Engine::get()->getRecord()));
    m_record_score = new QLabel(record, this);
    m_record_score->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_record_score->setFixedWidth(145);
}

void SettingsWidget::updateRecord(unsigned long record) noexcept
{
    /*Core::Engine* e = Core::Engine::get();
    Q_ASSERT(e != nullptr);
    if (record < e->getRecord()) {
        return;
    }
    QString s = QString::fromStdString(std::to_string(record));
    m_record_score->setText(s);*/
}


} /// Gui namespace
