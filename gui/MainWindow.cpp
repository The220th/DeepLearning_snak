
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QTimer>

#include <string>
#include <iostream>

#include "../include/MainWindow.h"
#include "../include/DrawField.h"
#include "../include/GameHandler.h"
#include "../include/sup.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), GAME_W(50), GAME_H(50), gh_N(100)
{
    lastKey = 0;
    tickTime_mili = 100;
    curGeneration = 1;

    QGridLayout *grid = new QGridLayout(this);

    drawField = new DrawField(this, GAME_W, GAME_H);
    
    scoreLabel = new QLabel("0", this);
    genLabel = new QLabel(std::to_string(curGeneration).c_str(), this);

    grid->addWidget(scoreLabel, 0, 0);
    grid->addWidget(genLabel, 0, 1);
    grid->addWidget(drawField, 1, 0, 1, 2);

    setLayout(grid);

    gh = new GameHandler*[gh_N];
    for(size_t i = 0; i < gh_N; ++i)
    {
        gh[i] = new GameHandler(GAME_W, GAME_H, drawField);
        (gh[i])->getSnake()->setRndBrain();
    }

    gh_scores = new double[gh_N];
    sup_reset_array(gh_scores, gh_N, -1.0);

    //this->startTimer(tickTime_mili);
    timer = new QTimer(this);
    timer->setInterval(tickTime_mili);
    //m_firstTimerId = timer->timerId();
    connect(timer, SIGNAL(timeout()), this, SLOT(_timerEvent()));
    timer->start();
}

MainWindow::~MainWindow()
{   
    for(size_t i = 0; i < gh_N; ++i)
    {
        delete gh[i];
    }
    delete gh;

    delete gh_scores;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    drawField->keyPressEventHandle(event);

    int key = event->key();

    // https://doc.qt.io/qt-5/qt.html#Key-enum
    if(key == Qt::Key_Up)
    {
        tickTime_mili += 10;
        timer->setInterval(tickTime_mili);
    }
    else if(key == Qt::Key_Down)
    {
        tickTime_mili -= 10;
        if(tickTime_mili < 1)
            tickTime_mili = 1;
        timer->setInterval(tickTime_mili);
    }
}

//void MainWindow::timerEvent(QTimerEvent *event)
void MainWindow::_timerEvent()
{
    //Q_UNUSED(event);

    drawField->refreshDisplay();

    for(size_t gi = 0; gi < gh_N; ++gi)
    {
        if(gh_scores[gi] == -1.0)
        {
            bool isOK = (gh[gi])->tick((gh[gi])->whatSnakeThink());
            if(!isOK)
            {
                gh_scores[gi] = (gh[gi])->getScore();
            }
        }
    }

    double curscores[gh_N];
    for(size_t i = 0; i < gh_N; ++i)
        curscores[i] = (gh[i])->getScore();

    double maxScore = sup_calc_max(curscores, gh_N);
    scoreLabel->setText(("Score: " + (std::to_string((size_t)(maxScore+0.5)))).c_str() );


    if(!sup_check_inclusion(gh_scores, gh_N, -1.0)) // all games left
    {
        double sumOfScores = sup_calc_sum(gh_scores, gh_N);
        Matrix<double> **oldGenoms = new Matrix<double>*[gh_N];
        for(size_t i = 0; i < gh_N; ++i)
            oldGenoms[i] = new Matrix<double>( (gh[i])->getSnake()->getBrain()->getGenom() );

        for(size_t i = 0; i < gh_N; ++i)
        {
            (gh[i])->reset();

            size_t parent1 = sup_chooseProbablyBest(gh_scores, gh_N, sumOfScores);
            size_t parent2 = sup_chooseProbablyBest(gh_scores, gh_N, sumOfScores);

            Matrix<double> newGenom = SnakeBrain::offspring(*oldGenoms[parent1], *oldGenoms[parent2]);

            (gh[i])->getSnake()->setBrain(newGenom);
        }

        for(size_t i = 0; i < gh_N; ++i)
            delete oldGenoms[i];
        delete oldGenoms;

        sup_reset_array(gh_scores, gh_N, -1.0);

        ++curGeneration;
        genLabel->setText(("Generation: " + std::to_string(curGeneration)).c_str());
    }

    drawField->update();
}