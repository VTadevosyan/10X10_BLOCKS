/// 10 X 10

/**
  * @file Gui/ColorMap.hpp
 **/

#ifndef __10X10_GUI_COLOR_MAP_HPP
#define __10X10_GUI_COLOR_MAP_HPP

#include "Core/Index.hpp"
#include "Core/Object.hpp"

#include <QColor>
#include <QImage>

#include <map>


namespace Gui {

/// @class ColorMap
class ColorMap
{
public:
    /// @brief Create engine
    static void create() noexcept;

    /// @brief Destroy engine
    static void destroy() noexcept;

    /// @brief Gets the engine
    static ColorMap* get() noexcept;

    /// @brief Gets the image for preview items from specified object
    static QImage getPreviewImage(Core::Object* const, bool) noexcept;

public:
    /// @brief Constructor
    ColorMap() noexcept;

    /// @brief Destructor
    virtual ~ColorMap() = default;

public:
    /// @brief update color map data for new object
    void objectCreated(Core::Object* const, const Core::Index&);

    /// @brief Get item color for specified index
    QColor getColor(const Core::Index&) const noexcept;

    /// @brief Get item color for current object
    QColor getColor(Core::Object* const) const noexcept;

    /// @brief Get item image for specified index
    QImage getImage(const Core::Index&) const noexcept;

    /// @brief Get item image for current object
    QImage getImage(Core::Object* const) const noexcept;

private:
    static std::map<std::pair<Core::Object::Type, int>, QColor> s_index2colorMap;
    static std::map<std::pair<Core::Object::Type, int>, QImage> s_index2imageMap;
    static std::map<std::pair<Core::Object::Type, int>, QImage> s_index2previewImageMap;
    static std::map<std::pair<Core::Object::Type, int>, QImage> s_index2previewActiveImageMap;
    static QColor s_defaultColor;
    static ColorMap* s_colorMap;


private:
    std::map<Core::Index, QColor> m_data;
    std::map<Core::Index, QImage> m_img_data;

};

} /// Gui namespace

#endif // __10X10_GUI_COLOR_MAP_HPP
