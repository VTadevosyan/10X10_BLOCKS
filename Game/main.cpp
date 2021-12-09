/// 10 X 10

/**
  * @file main.cpp
 **/

#include "Game/Launcher.hpp"

#include <QApplication>


int main(int argc, char* argv[])
{
    try {
        QApplication a(argc, argv);
        Game::Launcher::run(a);
        return a.exec();
    } catch(...) {
    }
    return 0;
}
