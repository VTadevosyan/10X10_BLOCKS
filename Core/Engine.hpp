/// 10 X 10

/**
  * @file Core/Engine.hpp
 **/

#ifndef __10X10_CORE_ENGINE_HPP
#define __10X10_CORE_ENGINE_HPP

#include "Core/Board.hpp"
#include "Core/Index.hpp"

#include <memory>
#include <set>
#include <vector>


namespace Core {

class Object;
class ScoreManager;

/// @class Engine
class Engine
{
public:
    /// @brief Create engine
    static void create() noexcept;

    /// @brief Destroy engine
    static void destroy() noexcept;

    /// @brief Gets the engine
    static Engine* get() noexcept;

public:
    /// @brief Constructor
    Engine();

    /// @brief Destructor
    virtual ~Engine();

public:
    /// @brief Checks if the specified cell is used or not
    bool isCellChecked(const Index&) const noexcept;

    /// @brief Checks if user able to create new object in current position
    bool canCreateObject(Object* const, const Index&) const noexcept;

    /// @brief Check object bounds: return false if object index is out of board bounds
    bool isOutOfBounds(Core::Object* const, const Index&) const noexcept;

    /// @brief Process data
    void notifyChanged(Object*, const Index&);

    /// @brief Gets the checked cell indexes
    const std::set<Index>& getCheckedCells() const noexcept;

    /// @brief Gets the score
    unsigned long getScore() const noexcept;

    /// @brief Gets the best score (record)
    unsigned long getRecord() const noexcept;

    /// @brief Gets the current objects
    const std::vector<Object*>& getCurrentObjects() const noexcept;

private:
    void setCellChecked(const Index&);
    void createObject(Object* const, const Index&);
    void removeFullRows();
    void updateCurrentObjects(Object*);
    void generateCurrentObjects();
    void deleteCurrentObjects();
    void updateScore();

    bool canCreateAngledObject(Object* const, const Index&) const noexcept;
    bool canCreateLinearObject(Object* const, const Index&) const noexcept;
    bool canCreateSquaredObject(Object* const, const Index&) const noexcept;
    void createAngledObject(Object* const, const Index&);
    void createLinearObject(Object* const, const Index&);
    void createSquaredObject(Object* const, const Index&);

    bool canCreateNextObject() const noexcept;

private:
    static Engine* m_engine;

private:
    std::unique_ptr<Board> m_board;
    std::unique_ptr<ScoreManager> m_scoreManager;
    std::vector<Object*> m_current_objects;
};

} /// Core namespace

#endif // __10X10_CORE_ENGINE_HPP
