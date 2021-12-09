/// 10 X 10

/**
  * @file Gui/ColorMap.cpp
 **/

#include "Gui/ColorMap.hpp"

#include <qdebug.h>


namespace Gui {

ColorMap* ColorMap::s_colorMap = nullptr;
QColor ColorMap::s_defaultColor = Qt::white;

std::map<std::pair<Core::Object::Type, int>, QColor> ColorMap::s_index2colorMap = {
    { std::make_pair(Core::Object::Type::angled, 2),  Qt::blue },
    { std::make_pair(Core::Object::Type::angled, 3),  Qt::darkGray },
    { std::make_pair(Core::Object::Type::linear, 2),  Qt::darkBlue },
    { std::make_pair(Core::Object::Type::linear, 3),  Qt::darkYellow },
    { std::make_pair(Core::Object::Type::linear, 4),  Qt::darkMagenta },
    { std::make_pair(Core::Object::Type::linear, 5),  Qt::darkRed },
    { std::make_pair(Core::Object::Type::squared, 1), Qt::magenta },
    { std::make_pair(Core::Object::Type::squared, 2), Qt::darkCyan },
    { std::make_pair(Core::Object::Type::squared, 3), Qt::darkGreen }
};

std::map<std::pair<Core::Object::Type, int>, QImage> ColorMap::s_index2imageMap
{
    { std::make_pair(Core::Object::Type::angled, 2),  QImage("../Img/YellowItem.png") },
    { std::make_pair(Core::Object::Type::angled, 3),  QImage("../Img/BlueItem.png") },
    { std::make_pair(Core::Object::Type::linear, 2),  QImage("../Img/RedItem.png") },
    { std::make_pair(Core::Object::Type::linear, 3),  QImage("../Img/RedItem.png") },
    { std::make_pair(Core::Object::Type::linear, 4),  QImage("../Img/GreenItem.png") },
    { std::make_pair(Core::Object::Type::linear, 5),  QImage("../Img/GreenItem.png") },
    { std::make_pair(Core::Object::Type::squared, 1), QImage("../Img/GrayItem.png") },
    { std::make_pair(Core::Object::Type::squared, 2), QImage("../Img/YellowItem.png") },
    { std::make_pair(Core::Object::Type::squared, 3), QImage("../Img/OrangeItem.png") }
};

std::map<std::pair<Core::Object::Type, int>, QImage> ColorMap::s_index2previewImageMap
{
    { std::make_pair(Core::Object::Type::angled, 2),  QImage("../Img/YellowPreviewItem.png") },
    { std::make_pair(Core::Object::Type::angled, 3),  QImage("../Img/BluePreviewItem.png") },
    { std::make_pair(Core::Object::Type::linear, 2),  QImage("../Img/RedPreviewItem.png") },
    { std::make_pair(Core::Object::Type::linear, 3),  QImage("../Img/RedPreviewItem.png") },
    { std::make_pair(Core::Object::Type::linear, 4),  QImage("../Img/GreenPreviewItem.png") },
    { std::make_pair(Core::Object::Type::linear, 5),  QImage("../Img/GreenPreviewItem.png") },
    { std::make_pair(Core::Object::Type::squared, 1), QImage("../Img/GrayPreviewItem.png") },
    { std::make_pair(Core::Object::Type::squared, 2), QImage("../Img/YellowPreviewItem.png") },
    { std::make_pair(Core::Object::Type::squared, 3), QImage("../Img/OrangePreviewItem.png") }
};

std::map<std::pair<Core::Object::Type, int>, QImage> ColorMap::s_index2previewActiveImageMap
{
    { std::make_pair(Core::Object::Type::angled, 2),  QImage("../Img/YellowPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::angled, 3),  QImage("../Img/BluePreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::linear, 2),  QImage("../Img/RedPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::linear, 3),  QImage("../Img/RedPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::linear, 4),  QImage("../Img/GreenPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::linear, 5),  QImage("../Img/GreenPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::squared, 1), QImage("../Img/GrayPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::squared, 2), QImage("../Img/YellowPreviewActiveItem.png") },
    { std::make_pair(Core::Object::Type::squared, 3), QImage("../Img/OrangePreviewActiveItem.png") }
};

void ColorMap::create() noexcept
{
    if (s_colorMap == nullptr) {
        s_colorMap = new ColorMap;
    }
}

void ColorMap::destroy() noexcept
{
    if (s_colorMap != nullptr) {
        delete s_colorMap;
        s_colorMap = nullptr;
    }
}

ColorMap* ColorMap::get() noexcept
{
    Q_ASSERT(s_colorMap != nullptr);
    return s_colorMap;
}

QImage ColorMap::getPreviewImage(Core::Object* const o, bool isActive) noexcept
{
    if (o == nullptr) {
        return QImage();
    }
    const Core::Object::Type type = o->getType();
    const int length = o->getLength();
    if (isActive) {
        auto it = s_index2previewActiveImageMap.find(std::make_pair(type, length));
        return it != s_index2previewActiveImageMap.end() ? it->second : QImage();
    }
    auto it = s_index2previewImageMap.find(std::make_pair(type, length));
    return it != s_index2previewImageMap.end() ? it->second : QImage();
}

ColorMap::ColorMap() noexcept
{
    m_data = {};
}

QColor ColorMap::getColor(const Core::Index& i) const noexcept
{
    if (!i.isValid()) {
        return s_defaultColor;
    }
    auto it = m_data.find(i);
    return it != m_data.end() ? it->second : s_defaultColor;
}

QColor ColorMap::getColor(Core::Object* const o) const noexcept
{
    if (o == nullptr) {
        return s_defaultColor;
    }
    const Core::Object::Type type = o->getType();
    const int length = o->getLength();
    auto it = s_index2colorMap.find(std::make_pair(type, length));
    return it != s_index2colorMap.end() ? it->second : s_defaultColor;
}

QImage ColorMap::getImage(const Core::Index& i) const noexcept
{
    if (!i.isValid()) {
        return QImage();
    }
    auto it = m_img_data.find(i);
    return it != m_img_data.end() ? it->second : QImage();
}

QImage ColorMap::getImage(Core::Object* const o) const noexcept
{
    if (o == nullptr) {
        return QImage();
    }
    const Core::Object::Type type = o->getType();
    const int length = o->getLength();
    auto it = s_index2imageMap.find(std::make_pair(type, length));
    return it != s_index2imageMap.end() ? it->second : QImage();
}

void ColorMap::objectCreated(Core::Object* const o, const Core::Index& i)
{
    if (o == nullptr || !i.isValid()) {
        return;
    }
    int row = i.row();
    int col = i.column();
    const int length = o->getLength();
    QColor color = getColor(o);
    QImage image = getImage(o);
    Core::Object::Type type = o->getType();
    if (type == Core::Object::Type::angled) {
        Core::AngledObject* ao = static_cast<Core::AngledObject*>(o);
        const bool isLeft = ao->getHorizontalDirection() == Core::AngledObject::HorizontalDirection::left;
        const bool isTop = ao->getVerticalDirection() == Core::AngledObject::VerticalDirection::top;
        m_data[Core::Index(row, col)] = color;
        m_img_data[Core::Index(row, col)] = image;
        if (isLeft) {
            for (int i = 1; i < length; ++i) {
                m_data[Core::Index(row, col - i)] = color;
                m_img_data[Core::Index(row, col - i)] = image;
            }
        } else {
            for (int i = 1; i < length; ++i) {
                m_data[Core::Index(row, col + i)] = color;
                m_img_data[Core::Index(row, col + i)] = image;
            }
        }
        if (isTop) {
            for (int i = 1; i < length; ++i) {
                m_data[Core::Index(row - i, col)] = color;
                m_img_data[Core::Index(row - i, col)] = image;
            }
        } else {
            for (int i = 1; i < length; ++i) {
                m_data[Core::Index(row + i, col)] = color;
                m_img_data[Core::Index(row + i, col)] = image;
            }
        }

    } else if (type == Core::Object::Type::linear) {
        Core::LinearObject* lo = static_cast<Core::LinearObject*>(o);
        Core::LinearObject::Direction direction = lo->getDirection();
        if (direction == Core::LinearObject::Direction::horizontal) {
            for (int i = 0; i < length; ++i) {
                m_data[Core::Index(row, col)] = color;
                m_img_data[Core::Index(row, col)] = image;
                ++col;
            }
        } else {
            Q_ASSERT(direction == Core::LinearObject::Direction::vertical);
            for (int i = 0; i < length; ++i) {
                m_data[Core::Index(row, col)] = color;
                m_img_data[Core::Index(row, col)] = image;
                --row;
            }
        }
    } else if (type == Core::Object::Type::squared) {
        for (int ri = 0; ri < length; ++ri) {
            for (int ci = 0; ci < length; ++ci) {
                m_data[Core::Index(row, col + ci)] = color;
                m_img_data[Core::Index(row, col + ci)] = image;
            }
            ++row;
            col = i.column();
        }
    }

}


} /// Gui namespace
