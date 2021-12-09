/// 10 X 10

/**
  * @file Core/Board.hpp
 **/

#ifndef __10X10_CORE_BOARD_HPP
#define __10X10_CORE_BOARD_HPP

#include "Core/Index.hpp"

#include <list>
#include <set>
#include <vector>


namespace Core {

class Object;

/// @class Board
class Board
{
public:
    /// @brief Gets the horizontal/vertical items count
    static int size() noexcept;

    /// @brief Gets the maximum count of cells
    static int maximumCellsCount() noexcept;

public:
    /// @brief Constructor
    Board();

    /// @brief Destructor
    virtual ~Board() = default;

public:
    /// @brief Checks if the specified cell is used or not
    bool isCellChecked(const Index&) const noexcept;

    /// @brief Checks if the specified cell is used or not
    bool isCellChecked(int, int) const noexcept;

    /// @brief Check object bounds
    bool isOutOfBounds(Core::Object* const, const Index&) const noexcept;

    /// @brief Sets the specified cell checked
    void setCellChecked(const Index&) noexcept;

    /// @brief Sets the specified cell unchecked
    void setCellUnchecked(const Index&) noexcept;

    /// @brief Get cell from index
    int getCell(const Index&) const noexcept;

    /// @brief Get cell from specified row and column
    int getCell(int, int) const noexcept;

    /// @brief Gets the checked cell indexes
    const std::set<Index>& getCheckedCells() const noexcept;

    /// @brief Gets the empty cell indexes
    void getUncheckedCells(std::list<Index>&) const noexcept;

private:
    bool isAngledObjectOutOfBounds(Core::Object* const, const Index&) const noexcept;
    bool isLinearObjectOutOfBounds(Core::Object* const, const Index&) const noexcept;
    bool isSquaredObjectOutOfBounds(Core::Object* const, const Index&) const noexcept;

private:
    std::vector<bool> m_data;
    std::set<Index> m_checked_cell_indexes;

};

} /// Core namespace


#endif // __10X10_CORE_BOARD_HPP
