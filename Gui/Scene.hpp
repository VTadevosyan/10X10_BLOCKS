/// 10 X 10

/**
  * @file Gui/Scene.hpp
 **/

#ifndef __10X10_GUI_SCENE_HPP
#define __10X10_GUI_SCENE_HPP

#include <QGraphicsScene>


namespace Gui {

/// @class Scene
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit Scene();

    /// @brief Destructor
    virtual ~Scene() = default;
};

} /// Gui namespace

#endif // __10X10_GUI_SCENE_HPP
