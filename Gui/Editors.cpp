/// 10 X 10

/**
  * @file Gui/Editors.cpp
 **/

#include "Core/Engine.hpp"
#include "Core/Option.hpp"
#include "Core/OptionsManager.hpp"

#include "Gui/Editors.hpp"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPainter>


namespace Gui {

PlayButton::PlayButton(QWidget* parent) noexcept
    : QWidget(parent)
    , m_isActive(false)
{
    setFixedSize(150, 150);
}

void PlayButton::paintEvent(QPaintEvent*)
{
    QPainter* p = new QPainter(this);
    p->drawImage(0, 0, QImage(m_isActive ? "../Img/PlayLogoActive.png" : "../Img/PlayLogo.png"));
    p->end();
}

void PlayButton::mousePressEvent(QMouseEvent*)
{
    emit gameLaunched();
}

void PlayButton::enterEvent(QEvent*)
{
    m_isActive = true;
    update();
}

void PlayButton::leaveEvent(QEvent*)
{
    m_isActive = false;
    update();
}

BestScoreWidget::BestScoreWidget(QWidget* parent) noexcept
    : QWidget(parent)
{
    createIconLabel();
    createBestScoreLabel();
    setupLayout();
}

void BestScoreWidget::createIconLabel() noexcept
{
    m_iconLabel = new QLabel(this);
    QPixmap pm("../Img/Record.png");
    m_iconLabel->setPixmap(pm);
    m_iconLabel->setFixedSize(60, 60);
    m_iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void BestScoreWidget::createBestScoreLabel() noexcept
{
    QString record = QString::fromStdString(std::to_string(Core::Engine::get()->getRecord()));
    m_bestScoreLabel = new QLabel(record, this);
    m_bestScoreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //m_bestScoreLabel->setFixedWidth(145);
}

void BestScoreWidget::setupLayout() noexcept
{
    QVBoxLayout* vl = new QVBoxLayout(this);
    QHBoxLayout* hl = new QHBoxLayout;
    hl->addStretch();
    hl->addWidget(m_bestScoreLabel);
    hl->addWidget(m_iconLabel);
    hl->addStretch();
    vl->addStretch();
    vl->addLayout(hl);
    vl->addStretch();
}

Editor::Editor(const QString& lbl, QWidget* parent) noexcept
    : QWidget(parent)
    , m_label(new QLabel(lbl, this))
    , m_optionName("")
{
    m_label->setFixedWidth(125);
    m_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void Editor::setOption(const std::string& name) noexcept
{
    if (!name.empty()) {
        m_optionName = name;
    }
}

void Editor::updateOption(std::string&& value) noexcept
{
    if (m_optionName.empty()) {
        return;
    }
    Core::Option* o = Core::OptionsManager::get()->find(m_optionName);
    if (o != nullptr) {
        o->setValue(value);
    }
}

LineEditor::LineEditor(const QString& lbl, QWidget* parent) noexcept
    : Editor(lbl, parent)
{
    m_editor = new QLineEdit(this);
    m_editor->setMinimumWidth(125);
    m_editor->setFont(QFont("Comic Sans MS", 10));
    m_editor->setMaxLength(20);
    setupLayout();
    connect(m_editor, SIGNAL(textChanged(const QString&)), this, SLOT(updateValue(const QString&)));
}

void LineEditor::setupLayout() noexcept
{
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_label);
    layout->addWidget(m_editor);
    setLayout(layout);
}

void LineEditor::updateValue(const QString& value) {
    QPalette p;
    if (value.isEmpty()) {
        p.setColor(QPalette::WindowText, Qt::red);
    }
    m_label->setPalette(p);
    m_editor->setPalette(p);
    if (!value.isEmpty()) {
        emit valueChanged(value);
    }
    updateOption(std::move(value.toStdString()));
}

CheckBoxEditor::CheckBoxEditor(const QString& lbl, QWidget* parent) noexcept
    : Editor(lbl, parent)
{
    m_editor = new QCheckBox(this);
    m_editor->setChecked(true);
    m_editor->setMinimumWidth(125);
    setupLayout();
    connect(m_editor, SIGNAL(stateChanged(int)), this, SIGNAL(valueChanged(int)));
}

void CheckBoxEditor::setupLayout() noexcept
{
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_label);
    layout->addWidget(m_editor);
    setLayout(layout);
}

} /// Gui namespace
