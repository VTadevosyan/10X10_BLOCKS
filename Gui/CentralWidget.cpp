/// 10 X 10

/**
  * @file Gui/CentralWidget.cpp
 **/

#include "Gui/CentralWidget.hpp"
#include "Gui/ObjectPanel.hpp"
#include "Gui/SettingsWidget.hpp"
#include "Gui/ScoreWidget.hpp"
#include "Gui/View.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>


namespace Gui {

CentralWidget::CentralWidget(QWidget* parent) noexcept
    : QWidget(parent)
{
    m_view = new View(this);
    m_score = new ScoreWidget(this);
    m_objects = new ObjectPanel(this);
    m_settings = new SettingsWidget(this);
    setupLayout();
    connectWidgets();
}

CentralWidget::~CentralWidget()
{
    disconnectWidgets();
    m_view->deleteLater();
    m_score->deleteLater();
    m_objects->deleteLater();
    m_settings->deleteLater();
}

void CentralWidget::connectWidgets() noexcept
{
    connect(m_objects, SIGNAL(objectChanged(Core::Object*)), m_view, SLOT(setObject(Core::Object*)));
    connect(m_score, SIGNAL(scoreChanged(unsigned long)), m_settings, SLOT(updateRecord(unsigned long)));
    connect(m_settings, SIGNAL(settingsButtonClicked()), this, SIGNAL(settingsButtonClicked()));
}

void CentralWidget::disconnectWidgets() noexcept
{
    disconnect(m_objects, SIGNAL(objectChanged(Core::Object*)), m_view, SLOT(setObject(Core::Object*)));
    disconnect(m_score, SIGNAL(scoreChanged(unsigned long)), m_settings, SLOT(updateRecord(unsigned long)));
    disconnect(m_settings, SIGNAL(settingsButtonClicked()), this, SIGNAL(settingsButtonClicked()));
}

void CentralWidget::setupLayout() noexcept
{
    /// score
    QHBoxLayout* sl = new QHBoxLayout;
    sl->addStretch(1);
    sl->addWidget(m_score);
    sl->addStretch(1);
    /// view
    QHBoxLayout* hl = new QHBoxLayout;
    hl->addStretch(1);
    hl->addWidget(m_view);
    hl->addStretch(1);
    /// objects
    QHBoxLayout* ol = new QHBoxLayout;
    ol->addStretch(1);
    ol->addWidget(m_objects);
    ol->addStretch(1);
    /// settings
    QHBoxLayout* settings_l = new QHBoxLayout;
    settings_l->addStretch(1);
    settings_l->addWidget(m_settings);
    settings_l->addStretch(1);
    /// central widget
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addStretch(1);
    vl->addLayout(settings_l);
    vl->addLayout(sl);
    vl->addLayout(hl);
    vl->addLayout(ol);
    vl->addStretch(1);
    setLayout(vl);
}

View* CentralWidget::view() const noexcept
{
    return m_view;
}

ScoreWidget* CentralWidget::scoreWidget() const noexcept
{
    return m_score;
}

ObjectPanel* CentralWidget::objectPanel() const noexcept
{
    return m_objects;
}

Scene* CentralWidget::scene() const noexcept
{
    return m_view->getScene();
}

void CentralWidget::setUsernameVisibility(int state)
{
    Q_ASSERT(m_score != nullptr);
    m_score->setUsernameVisibility(state);
}

void CentralWidget::setUsername(const QString& username)
{
    Q_ASSERT(m_score != nullptr);
    m_score->setUsername(username);
}

} /// Gui namespace
