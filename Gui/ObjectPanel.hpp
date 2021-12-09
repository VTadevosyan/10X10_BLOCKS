/// 10 X 10

/**
  * @file Gui/ObjectPanel.hpp
 **/

#ifndef __10X10_GUI_OBJECT_PANEL_HPP
#define __10X10_GUI_OBJECT_PANEL_HPP

#include <QWidget>

#include <vector>


namespace Core {

class Object;

} /// Core namespace

namespace Gui {

class ObjectPanelItem;

/// @class ObjectPanel
class ObjectPanel : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor
    ObjectPanel(QWidget* = nullptr) noexcept;

    /// @brief Destructor
    virtual ~ObjectPanel();

public:
    /// @brief Gets the active object
    Core::Object* getActiveObject() const noexcept;

    /// @brief update object panel
    void update();

signals:
    /// @brief signal emitted when current object was changed
    void objectChanged(Core::Object*);


private:
    void connectObjects();
    void disconnectObjects();
    void setupLayout();
    void loadObjects();

private slots:
    void setActiveObject(ObjectPanelItem*) noexcept;

private:
    ObjectPanelItem* m_activeObject;
    std::vector<ObjectPanelItem*> m_objects;

};

} /// Gui namespace

#endif // __10X10_GUI_OBJECT_PANEL_HPP
