/// 10 X 10 BLOCKS

/**
  * @file Core/OptionsManager.hpp
 **/

#ifndef __10X10_CORE_OPTIONS_MANAGER_HPP
#define __10X10_CORE_OPTIONS_MANAGER_HPP

#include "Option.hpp"

#include <set>


namespace Core {

/// @class OptionsManager
class OptionsManager
{
    using options_t = std::set<Option, Option::ComparatorType>;

public:
    /// @brief Create object builder
    static void create() noexcept;

    /// @brief Destroy object builder
    static void destroy() noexcept;

    /// @brief Gets the object builer
    static OptionsManager* get() noexcept;

public:
    /// @brief Constructor
    OptionsManager() noexcept;

    /// @brief Load options from file
    void load() noexcept;

    /// @brief Save options into file
    void save() noexcept;

public:
    /// @brief Find option with given name
    Option* find(const std::string&) const noexcept;

private:
    /// @brief Register game options
    void registerOptions() noexcept;

private:
    static OptionsManager* m_optionsManager;

private:
    options_t m_options;

};

} /// Core namespace

#endif /// __10X10_CORE_OPTIONS_MANAGER_HPP
