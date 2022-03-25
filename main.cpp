#include <QApplication>
#include <QIcon>

#include <iostream>
#include <cstdlib>

#include "./include/MainWindow.h"

#include "./include/sup.h"
 
/*
./aisnak - just game
./aisnak num - learning
./aisnake numbers - demonstrating
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    window.setWindowTitle("DeepLearning snak");
    window.resize(1280, 720);
    window.setWindowIcon(QIcon("./imgsrc/ico.png"));

    /*if(argc == 1)
    {
        
    }*/



    window.show();

    return app.exec();
}