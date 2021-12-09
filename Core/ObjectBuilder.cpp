/// 10 X 10

/**
  * @file Core/ObjectBuilder.cpp
 **/

#include "Core/ObjectBuilder.hpp"

#include <ctime>

#include <qdebug.h>


namespace Core {

ObjectBuilder* ObjectBuilder::m_builder = nullptr;

void ObjectBuilder::create() noexcept
{
    if (m_builder == nullptr) {
        m_builder = new ObjectBuilder;
    }
}

void ObjectBuilder::destroy() noexcept
{
    if (m_builder != nullptr) {
        delete m_builder;
        m_builder = nullptr;
    }
}

ObjectBuilder* ObjectBuilder::get() noexcept
{
    Q_ASSERT(m_builder != nullptr);
    return m_builder;
}

int ObjectBuilder::angledMaxLength() noexcept
{
    return 2;
}

int ObjectBuilder::linearMaxLength() noexcept
{
    return 4;
}

int ObjectBuilder::squaredMaxLength() noexcept
{
    return 3;
}

ObjectBuilder::ObjectBuilder()
{
    std::srand(time(0));
}

Object::Type ObjectBuilder::generateObjectType() const noexcept
{
    return static_cast<Object::Type>(qrand() % static_cast<int>(Object::Type::MAX_SIZE));
}

int ObjectBuilder::generateAngledObjectSize() const noexcept
{
    return qrand() % angledMaxLength() + 2;
}

int ObjectBuilder::generateLinearObjectSize() const noexcept
{
    return qrand() % linearMaxLength() + 2;
}

int ObjectBuilder::generateSquaredObjectSize() const noexcept
{
    return qrand() % squaredMaxLength() + 1;
}

LinearObject::Direction ObjectBuilder::generateLinearObjectDirection() const noexcept
{
    return static_cast<LinearObject::Direction>(qrand() % static_cast<int>(LinearObject::Direction::MAX_SIZE));
}

AngledObject::HorizontalDirection ObjectBuilder::generateAngledObjectHorizontalDirection() const noexcept
{
    return static_cast<AngledObject::HorizontalDirection>(qrand() % static_cast<int>(AngledObject::HorizontalDirection::MAX_SIZE));
}

AngledObject::VerticalDirection ObjectBuilder::generateAngledObjectVerticalDirection() const noexcept
{
    return static_cast<AngledObject::VerticalDirection>(qrand() % static_cast<int>(AngledObject::VerticalDirection::MAX_SIZE));
}

Object* ObjectBuilder::generateObject() const
{
    Object::Type type = generateObjectType();
    switch (type) {
        case Object::Type::angled:
        {
            int size = generateAngledObjectSize();
            AngledObject::HorizontalDirection hdir = generateAngledObjectHorizontalDirection();
            AngledObject::VerticalDirection vdir = generateAngledObjectVerticalDirection();
            return new AngledObject(size, hdir, vdir);
        }
        case Object::Type::linear:
        {
            int size = generateLinearObjectSize();
            LinearObject::Direction dir = generateLinearObjectDirection();
            return new LinearObject(size, dir);
        }
        case Object::Type::squared:
        {
            int size = generateSquaredObjectSize();
            return new SquaredObject(size);
        }
        default:
            Q_ASSERT(type > Object::Type::UNKNOWN && type < Object::Type::MAX_SIZE);
    };
    return nullptr;
}

} /// Core namespace
