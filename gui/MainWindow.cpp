
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimerEvent>

#include <string>

#include "../include/MainWindow.h"
#include "../include/DrawField.h"
#include "../include/GameHandler.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), GAME_W(50), GAME_H(50)
{
    lastKey = 0;
    tickTime_mili = 100;

    QGridLayout *grid = new QGridLayout(this);

    drawField = new DrawField(this, GAME_W, GAME_H);
    
    scoreLabel = new QLabel("0");

    grid->addWidget(scoreLabel, 0, 0);
    grid->addWidget(drawField, 1, 0);

    setLayout(grid);

    gh = new GameHandler(GAME_W, GAME_H, drawField);
    gh->getSnake()->setRndBrain();

    this->startTimer(tickTime_mili);
}

MainWindow::~MainWindow()
{
    delete gh;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    drawField->keyPressEventHandle(event);

    int key = event->key();

    // https://doc.qt.io/qt-5/qt.html#Key-enum
    if(key == Qt::Key_Up)
    {
        //gh->tick(2);
        lastKey = 2;
    }
    else if(key == Qt::Key_Down)
    {
        //gh->tick(4);
        lastKey = 4;
    }
    else if(key == Qt::Key_Left)
    {
        //gh->tick(1);
        lastKey = 1;
    }
    else if(key == Qt::Key_Right)
    {
        //gh->tick(3);
        lastKey = 3;
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    drawField->refreshDisplay();

    //bool isOK = gh->tick(lastKey);
    bool isOK = gh->tick(gh->whatSnakeThink());
    if(!isOK)
        lastKey = 3;
    else
        lastKey = 0;

    scoreLabel->setText( (std::to_string((int)(gh->getScore()+0.5))).c_str() );

    drawField->update();
}