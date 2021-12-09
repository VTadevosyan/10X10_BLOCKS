/// 10 X 10

/**
  * @file Core/Object.hpp
 **/

#ifndef __10X10_CORE_OBJECT_HPP
#define __10X10_CORE_OBJECT_HPP


namespace Core {

/// @class Object
class Object
{
public:
    /// @brief Object types enumeration
    enum class Type
    {
        UNKNOWN = -1,
        angled = 0,
        squared = 1,
        linear = 2,
        MAX_SIZE
    };

public:
    /// @brief Constructor
    Object(Type, int);

    /// @brief Destructor
    virtual ~Object() = default;

public:
    /// @brief Get object type
    Type getType() const noexcept;

    /// @brief Gets the object length
    int getLength() const noexcept;

protected:
    Type m_type;
    int m_length;
};


/// @class LinearObject
class LinearObject : public Object
{
public:
    /// @brief Linear object directions enumeration
    enum class Direction
    {
        horizontal = 0,
        vertical,
        MAX_SIZE
    };

public:
    /// @brief Constructor
    LinearObject(int, Direction) noexcept;

    /// @brief Get direction
    Direction getDirection() const noexcept;

private:
    Direction m_direction;

}; /// LinearObject


/// @class SquaredObject
class SquaredObject : public Object
{
public:
    /// @brief Constructor
    SquaredObject(int) noexcept;

};


/// @class AngledObject
class AngledObject : public Object
{
public:
    /// @brief Angled object horizontal directions enumeration
    enum class HorizontalDirection
    {
        left = 0,
        right,
        MAX_SIZE
    };

    /// @brief Angled object vertical directions enumeration
    enum class VerticalDirection
    {
        top = 0,
        bottom,
        MAX_SIZE
    };

public:
    /// @brief Constructor
    AngledObject(int, HorizontalDirection, VerticalDirection) noexcept;

    /// @brief Get horizontal direction
    HorizontalDirection getHorizontalDirection() const noexcept;

    /// @brief Get vertical direction
    VerticalDirection getVerticalDirection() const noexcept;

private:
    HorizontalDirection m_horizontalDirection;
    VerticalDirection m_verticalDirection;

};


} /// Core namespace

#endif // __10X10_CORE_OBJECT_HPP
