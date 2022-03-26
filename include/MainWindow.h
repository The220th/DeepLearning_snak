#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimerEvent>

#include <cstdlib>

#include "../include/DrawField.h"
#include "../include/GameHandler.h"

class MainWindow : public QWidget
{

    Q_OBJECT

    private:
    DrawField *drawField;
    QLabel *scoreLabel;

    const std::size_t GAME_W;
    const std::size_t GAME_H;

    GameHandler *gh;
    double *gh_scores;
    std::size_t gh_N;

    int tickTime_mili;

    /*
    0 - nothing
    1 - left
    2 - up
    3 - right
    4 - down
    */
    int lastKey;

    public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DrawField* getDrawField();

    protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H