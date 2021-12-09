/// 10 X 10 BLOCKS

/**
  * @file Core/ScoreManager.hpp
 **/

#ifndef __10X10_CORE_SCORE_MANAGER_HPP
#define __10X10_CORE_SCORE_MANAGER_HPP


namespace Core {

/// @class ScoreManager
class ScoreManager
{
public:
    /// @brief Enumeration needs during updating score
    enum class ActionType
    {
        ObjectAdded = 0,
        RowDeleted = 1
    };

public:
    /// @brief Constructor
    ScoreManager() noexcept;

    /// @brief Destructor
    virtual ~ScoreManager() = default;

public:
    /// @brief Update score and record(if needed) based on given action
    void updateScore(ActionType) noexcept;

    /// @brief Gets the score
    unsigned long getScore() const noexcept;

    /// @brief Gets the best score
    unsigned long getRecord() const noexcept;

    /// @brief Load best score from option
    void loadRecordFromOption() noexcept;

private:
    void updateRecord() noexcept;

private:
    unsigned long m_score;
    unsigned long m_record;

};

} /// Core namespace

#endif /// __10X10_CORE_SCORE_MANAGER_HPP
