/// 10 X 10 BLOCKS

/**
  * @file Core/Option.hpp
 **/

#ifndef __10X10_CORE_OPTION_HPP
#define __10X10_CORE_OPTION_HPP

#include "Core/ScoreManager.hpp"

#include <functional>


namespace Core {

/// @class Option
class Option final
{
public:
    /// @brief For comparing objects of type 'Option'
    static std::function<bool(const Option&, const Option&)> Comparator;
    using ComparatorType = decltype(Comparator);

public:
    /// @brief Constructor
    Option(const std::string&, const std::string& = "") noexcept;

    /// @brief Destructor
    virtual ~Option() = default;

    /// @brief Copy Constructor
    //Option(const Option&) = delete;

    /// @brief Copy Constructor
    //Option(Option&&) = delete;

    /// @brief Copy Assignement
    //Option& operator= (const Option&) = delete;

    /// @brief Move Assignement
    //Option&& operator= (Option&&) = delete;

public:
    /// @brief Gets the option value
    std::string getName() const noexcept;

    /// @brief Gets the option value
    std::string getValue() const noexcept;

    /// @brief Sets the option value
    void setValue(const std::string&) noexcept;

private:
    std::string m_name;
    std::string m_value;

};

} /// Core namespace

#endif // __10X10_CORE_OPTION_HPP
