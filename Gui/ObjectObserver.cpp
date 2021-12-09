/// 10 X 10

/**
  * @file Gui/ObjectObserver.cpp
 **/

#include "Gui/ObjectObserver.hpp"
#include "Gui/ObjectPanel.hpp"


namespace Gui {

ObjectObserver* ObjectObserver::m_object_observer = nullptr;

void ObjectObserver::create(ObjectPanel* p) noexcept
{
    if (m_object_observer == nullptr) {
        m_object_observer = new ObjectObserver(p);
    }
}

void ObjectObserver::destroy() noexcept
{
    if (m_object_observer != nullptr) {
        delete m_object_observer;
        m_object_observer = nullptr;
    }
}

ObjectObserver* ObjectObserver::get() noexcept
{
    return m_object_observer;
}

ObjectObserver::ObjectObserver(ObjectPanel* p) noexcept
    : Core::ObserverInterface()
    , m_objectPanel(p)
{
    Q_ASSERT(m_objectPanel != nullptr);
}

void ObjectObserver::processData()
{
    if (m_objectPanel != nullptr) {
        m_objectPanel->update();
    }
}

} /// Gui namespace
