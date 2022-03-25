
#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QPen>

#include "../include/DrawField.h"
#include "../include/sup.h"


using namespace std;


DrawField::DrawField(QWidget *parent, size_t width, size_t height) : QWidget(parent), display_W(width), display_H(height)
{
    setMinimumSize(W, H);
    setMaximumSize(W, H);

    display = new unsigned*[display_H];
    for(size_t i = 0; i < display_H; ++i)
        display[i] = new unsigned[display_W];
    refreshDisplay();
        
}

DrawField::~DrawField()
{
    for(size_t i = 0; i < display_H; ++i)
        delete display[i];
    delete display;
}

void DrawField::refreshDisplay()
{
    unsigned white = sup_getColor(255, 255, 255);
    for(size_t i = 0; i < display_H; ++i)
        for(size_t j = 0; j < display_W; ++j)
            display[i][j] = white;
}

void DrawField::putPoint(size_t x, size_t y, unsigned color)
{
    /*
    func:       display:
    ^ y         o--> j
    |           |
    o--> x      v i
    */
    display[display_H-1-y][x] = color;
}

void DrawField::keyPressEventHandle(QKeyEvent *event)
{
    Q_UNUSED(event);
    //int key = event->key();
}

void DrawField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter qp(this);

    for(size_t i = 0; i < display_H; ++i)
        for(size_t j = 0; j < display_W; ++j)
        {
            QColor c(display[i][j]);

            qp.fillRect(j*sizePixel, i*sizePixel, sizePixel, sizePixel, c);
        }
}