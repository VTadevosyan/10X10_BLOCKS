/// 10 X 10

/**
  * @file Gui/ObjectPanel.cpp
 **/

#include "Core/Board.hpp"
#include "Core/Engine.hpp"
#include "Core/Object.hpp"

#include "Gui/Item.hpp"
#include "Gui/ObjectPanel.hpp"
#include "Gui/ObjectPanelItem.hpp"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>


namespace Gui {

ObjectPanel::ObjectPanel(QWidget* parent) noexcept
    : QWidget(parent)
    , m_activeObject(nullptr)
    , m_objects(std::vector<ObjectPanelItem*>(3, nullptr))
{
    setFixedSize(Item::width() * Core::Board::size(), 240);
    for (auto& it : m_objects) {
        it = new ObjectPanelItem(this);
    }
    setupLayout();
    connectObjects();
    loadObjects();
}

ObjectPanel::~ObjectPanel()
{
    disconnectObjects();
}

void ObjectPanel::setupLayout()
{
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(m_objects[0]);
    //l->addStretch(1);
    l->addWidget(m_objects[1]);
    //l->addStretch(1);
    l->addWidget(m_objects[2]);
    setLayout(l);
}

void ObjectPanel::connectObjects()
{
    for (auto it : m_objects) {
        connect(it, SIGNAL(currentChanged(ObjectPanelItem*)), SLOT(setActiveObject(ObjectPanelItem*)));
    }
}

void ObjectPanel::disconnectObjects()
{
    for (auto it : m_objects) {
        disconnect(it, SIGNAL(currentChanged(ObjectPanelItem*)));
    }
}

Core::Object* ObjectPanel::getActiveObject() const noexcept
{
    return m_activeObject != nullptr ? m_activeObject->getObject() : nullptr;
}

void ObjectPanel::update()
{
    loadObjects();
    for (auto it : m_objects) {
        it->setActive(false);
        it->repaint();
    }
    emit objectChanged(nullptr);
}

void ObjectPanel::setActiveObject(ObjectPanelItem* item) noexcept
{
    for (auto it : m_objects) {
        it->setActive(false);
    }
    Q_ASSERT(item != nullptr);
    m_activeObject = item;
    m_activeObject->setActive(true);
    for (auto it : m_objects) {
        it->repaint();
    }
    emit objectChanged(m_activeObject->getObject());
}

void ObjectPanel::loadObjects()
{
    Core::Engine* e = Core::Engine::get();
    const std::vector<Core::Object*>& objs = e->getCurrentObjects();
    std::vector<ObjectPanelItem*>::iterator it = m_objects.begin();
    for (auto o : objs) {
        (*it)->setObject(o);
        (*it)->repaint();
        ++it;
    }
}

} /// Gui namespace
