/// 10 X 10

/**
  * @file Core/Index.hpp
 **/

#ifndef __10X10_CORE_INDEX_HPP
#define __10X10_CORE_INDEX_HPP

#include <QPointF>


namespace Core {

/// @class Index
class Index
{
public:
    /// @brief Creates a new index from mouse position
    static Index posToIndex(const QPointF&, int, int) noexcept;

public:
    bool operator< (const Index&) const noexcept;

public:
    /// @brief Constructor
    Index(int, int);

    /// @brief Default Constructor
    Index();

    /// @brief Destructor
    virtual ~Index() = default;

public:
    /// @brief Gets the row
    int row() const noexcept;

    /// @brief Gets the column
    int column() const noexcept;

    /// @brief Checks the index validity
    bool isValid() const noexcept;


private:
    int m_row;
    int m_col;
};

} /// Core namespace

#endif // __10X10_CORE_INDEX_HPP
