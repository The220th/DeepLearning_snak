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
#include <QTimer>

#include <cstdlib>

#include "../include/DrawField.h"
#include "../include/GameHandler.h"

class MainWindow : public QWidget
{

    Q_OBJECT

    private:
    DrawField *drawField;
    QLabel *scoreLabel;
    QLabel *genLabel;

    const std::size_t GAME_W;
    const std::size_t GAME_H;

    GameHandler **gh;
    double *gh_scores;
    std::size_t gh_N;

    int tickTime_mili;

    size_t curGeneration;

    /*
    0 - nothing
    1 - left
    2 - up
    3 - right
    4 - down
    */
    int lastKey;

    QTimer *timer;

    private Q_SLOTS:
        void _timerEvent();

    public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DrawField* getDrawField();

    protected:
    void keyPressEvent(QKeyEvent *event);
    //void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H