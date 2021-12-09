/// 10 X 10

/**
  * @file Core/Object.cpp
 **/

#include "Core/Object.hpp"

#include <qDebug.h>

namespace Core {

Object::Object(Type t, int l)
    : m_type(t)
    , m_length(l)
{

}

Core::Object::Type Object::getType() const noexcept
{
    return m_type;
}

int Object::getLength() const noexcept
{
    return m_length;
}

LinearObject::LinearObject(int l, Direction d) noexcept
    : Object(Object::Type::linear, l)
    , m_direction(d)
{
}

LinearObject::Direction LinearObject::getDirection() const noexcept
{
    return m_direction;
}

SquaredObject::SquaredObject(int l) noexcept
    : Object(Type::squared, l)
{

}

AngledObject::AngledObject(int l, HorizontalDirection hd, VerticalDirection vd) noexcept
    : Object(Type::angled, l)
    , m_horizontalDirection(hd)
    , m_verticalDirection(vd)
{

}

AngledObject::HorizontalDirection AngledObject::getHorizontalDirection() const noexcept
{
    return m_horizontalDirection;
}

AngledObject::VerticalDirection AngledObject::getVerticalDirection() const noexcept
{
    return m_verticalDirection;
}


} /// Core namespace
