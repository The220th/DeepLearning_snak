#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>

#include <cstdlib>
#include <cmath>

#include "../include/matrix.h"

class DrawField : public QWidget
{

  //Q_OBJECT

  private:
    const std::size_t sizePixel = 15;

    const std::size_t display_W;
    const std::size_t display_H;
    
    const std::size_t W = display_W*sizePixel;
    const std::size_t H = display_H*sizePixel;

    /*
    o--> j
    |
    v i
    */
    unsigned **display;


  public:
    DrawField(QWidget *parent, size_t width, size_t height);
    ~DrawField();

    void refreshDisplay();

    void keyPressEventHandle(QKeyEvent *event);
    

    /*
    ^ y
    |
    o--> x
    */
    void putPoint(std::size_t x, std::size_t y, unsigned color);
 
  private:
    void paintEvent(QPaintEvent *event);
};

#endif // DRAWFIELD_H