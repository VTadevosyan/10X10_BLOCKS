QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Core/Board.cpp \
    Core/Engine.cpp \
    Core/Index.cpp \
    Core/Object.cpp \
    Core/ObjectBuilder.cpp \
    Core/Observer.cpp \
    Core/Option.cpp \
    Core/OptionsManager.cpp \
    Core/ScoreManager.cpp \
    Game/Launcher.cpp \
    Game/main.cpp \
    Gui/BaseItem.cpp \
    Gui/CentralWidget.cpp \
    Gui/ColorMap.cpp \
    Gui/Editors.cpp \
    Gui/EngineObserver.cpp \
    Gui/ForegroundItem.cpp \
    Gui/HighlightController.cpp \
    Gui/HighlightItem.cpp \
    Gui/Item.cpp \
    Gui/MainPage.cpp \
    Gui/MainWindow.cpp \
    Gui/ObjectObserver.cpp \
    Gui/ObjectPanel.cpp \
    Gui/ObjectPanelItem.cpp \
    Gui/Scene.cpp \
    Gui/ScoreObserver.cpp \
    Gui/ScoreWidget.cpp \
    Gui/SettingsAssistant.cpp \
    Gui/SettingsEditor.cpp \
    Gui/SettingsWidget.cpp \
    Gui/View.cpp \

HEADERS += \
    Core/Board.hpp \
    Core/Engine.hpp \
    Core/Index.hpp \
    Core/Object.hpp \
    Core/ObjectBuilder.hpp \
    Core/Observer.hpp \
    Core/ObserverInterface.hpp \
    Core/Option.hpp \
    Core/OptionsManager.hpp \
    Core/ScoreManager.hpp \
    Game/Launcher.hpp \
    Gui/BaseItem.hpp \
    Gui/CentralWidget.hpp \
    Gui/ColorMap.hpp \
    Gui/Editors.hpp \
    Gui/EngineObserver.hpp \
    Gui/ForegroundItem.hpp \
    Gui/HighlightController.hpp \
    Gui/HighlightItem.hpp \
    Gui/Item.hpp \
    Gui/MainPage.hpp \
    Gui/MainWindow.hpp \
    Gui/ObjectObserver.hpp \
    Gui/ObjectPanel.hpp \
    Gui/ObjectPanelItem.hpp \
    Gui/Scene.hpp \
    Gui/ScoreObserver.hpp \
    Gui/ScoreWidget.hpp \
    Gui/SettingsAssistant.hpp \
    Gui/SettingsEditor.hpp \
    Gui/SettingsWidget.hpp \
    Gui/View.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Img/Score.png
