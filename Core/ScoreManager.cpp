/// 10 X 10 BLOCKS

/**
  * @file Core/ScoreManager.cpp
 **/

#include "Core/Option.hpp"
#include "Core/OptionsManager.hpp"
#include "Core/ScoreManager.hpp"

#include <QSettings>

#include <qdebug.h>

namespace Core {

ScoreManager::ScoreManager() noexcept
    : m_score(0)
    , m_record(0)
{
}

void ScoreManager::updateScore(ActionType a) noexcept
{
    switch (a) {
        case ActionType::ObjectAdded:
            ++m_score;
            break;
        case ActionType::RowDeleted:
            m_score += 10;
            break;
        default:
            Q_ASSERT("INVALID ACTION TYPE IS SPECIFIED" != nullptr);
    }
    updateRecord();
}

void ScoreManager::updateRecord() noexcept
{
    if (m_score > m_record) {
        m_record = m_score;
    }
    Option* o = Core::OptionsManager::get()->find("Option__Record");
    if (o != nullptr) {
        o->setValue(std::to_string(m_record));
    }
}

void ScoreManager::loadRecordFromOption() noexcept
{
    const Option* o = OptionsManager::get()->find("Option__Record");
    if (o != nullptr) {
        try {
            m_record = std::stoi(o->getValue());
        }  catch (const std::exception&) {
            m_record = 0;
        }
    }
}

unsigned long ScoreManager::getScore() const noexcept
{
    return m_score;
}

unsigned long ScoreManager::getRecord() const noexcept
{
    return m_record;
}

} /// Core namespace
