/// 10 X 10

/**
  * @file Core/OptionsManager.cpp
 **/

#include "Core/Option.hpp"
#include "Core/OptionsManager.hpp"

#include <QSettings>

#include <qdebug.h>

namespace Core {

OptionsManager* OptionsManager::m_optionsManager = nullptr;

void OptionsManager::create() noexcept
{
    if (m_optionsManager == nullptr) {
        m_optionsManager = new OptionsManager;
    }
}

void OptionsManager::destroy() noexcept
{
    if (m_optionsManager != nullptr) {
        delete m_optionsManager;
        m_optionsManager = nullptr;
    }
}

OptionsManager* OptionsManager::get() noexcept
{
    Q_ASSERT(m_optionsManager != nullptr);
    return m_optionsManager;
}

OptionsManager::OptionsManager() noexcept
    : m_options(options_t(Option::Comparator))
{
    QSettings s("Settings", QSettings::IniFormat);
    registerOptions();
    load();
}

Option* OptionsManager::find(const std::string& name) const noexcept
{
    auto it = m_options.find(name);
    return it != m_options.end() ? &const_cast<Option&>(*it) : nullptr;
}

void OptionsManager::load() noexcept
{
    QSettings s("Settings", QSettings::IniFormat);
    const QStringList& ls = s.allKeys();
    for (const auto& it : ls) {
        if (s.contains(it)) {
            options_t::iterator oi = m_options.find(it.toStdString());
            if (oi != m_options.end()) {
                Option& o = const_cast<Option&>(*oi);
                o.setValue(s.value(it).toString().toStdString());
            }
        }
    }
}

void OptionsManager::save() noexcept
{
    QSettings s("Settings", QSettings::IniFormat);
    for (const auto& it : m_options) {
        s.setValue(it.getName().c_str(), it.getValue().c_str());
    }
}

void OptionsManager::registerOptions() noexcept
{
    m_options.insert(Option("Option__UsernameVisibility", "true"));
    m_options.insert(Option("Option__Username", ""));
    m_options.insert(Option("Option__Record", "0"));
    m_options.insert(Option("Option__ObjectStyle", "Icons"));
}

} /// Core namespace
