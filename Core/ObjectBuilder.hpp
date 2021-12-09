/// 10 X 10

/**
  * @file Core/ObjectBuilder.hpp
 **/

#ifndef __10X10_CORE_OBJECT_BUILDER_HPP
#define __10X10_CORE_OBJECT_BUILDER_HPP

#include "Core/Object.hpp"

namespace Core {

/// @class ObjectBuilder
class ObjectBuilder
{
public:
    /// @brief Create object builder
    static void create() noexcept;

    /// @brief Destroy object builder
    static void destroy() noexcept;

    /// @brief Gets the object builer
    static ObjectBuilder* get() noexcept;

public:
    /// @brief Gets the maximum length for angled objects
    static int angledMaxLength() noexcept;

    /// @brief Gets the maximum length for linear objects
    static int linearMaxLength() noexcept;

    /// @brief Gets the maximum length for squared objects
    static int squaredMaxLength() noexcept;

public:
    /// @brief Constructor
    ObjectBuilder();

    /// @brief Constructor
    virtual ~ObjectBuilder() = default;

public:
    /// @brief Create a new object
    Object* generateObject() const;

private:
    Object::Type generateObjectType() const noexcept;
    int generateAngledObjectSize() const noexcept;
    int generateLinearObjectSize() const noexcept;
    int generateSquaredObjectSize() const noexcept;
    LinearObject::Direction generateLinearObjectDirection() const noexcept;
    AngledObject::HorizontalDirection generateAngledObjectHorizontalDirection() const noexcept;
    AngledObject::VerticalDirection generateAngledObjectVerticalDirection() const noexcept;

private:
    static ObjectBuilder* m_builder;

};

} /// Core namespace

#endif // __10X10_CORE_OBJECT_BUILDER_HPP
