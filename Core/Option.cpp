/// 10 X 10 BLOCKS

/**
  * @file Core/Option.cpp
 **/

#include "Option.hpp"

#include <qdebug.h>


namespace Core {

std::function<bool(const Option&, const Option&)> Option::Comparator = [] (const Option& o1, const Option& o2)
{
    return o1.getName() < o2.getName();
};

Option::Option(const std::string& name, const std::string& value) noexcept
    : m_name(name)
    , m_value(value)
{
}

std::string Option::getName() const noexcept
{
    return m_name;
}

std::string Option::getValue() const noexcept
{
    return m_value;
}

void Option::setValue(const std::string& value) noexcept
{
    if (m_value != value) {
        m_value = value;
    }
}

} /// Core namespace
