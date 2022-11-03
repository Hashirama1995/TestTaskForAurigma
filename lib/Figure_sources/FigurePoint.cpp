#include "Figure.h"
using namespace Object2D;

/*********_Implementation Point_*********/

Point::Point(Bitmap& pic, int x, int y, ColorInterface* clr)
                            :picture(pic), posX(x), posY(y), color(clr),current_color(clr->getColor())
{
    //delete color;
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(posX, posY, sizePic.first, sizePic.second);
}

Point::~Point()
{
    
    //delete color;
    std::cout<<"delete Point"<<std::endl;
}

void Point::setColor(ColorInterface* color)
{
    current_color = color->getColor();
}

void Point::rasterization()
{
    putPixel(posX, posY);    
}


void Point::putPixel(int x, int y)
{
    //picture.putPixel(posX, posY, color);
    picture.putPixel(posX, posY, current_color);
}

void Point::shift(float dx, float dy)
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validateToShift(dx, dy, posX, posY, sizePic.first, sizePic.second);

    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};
    matrixMultiply(posX, posY ,tempMatrix);
}

void Point::zoom(float Sx, float Sy)
{
    std::cout<< "Point::zoom - Thix method not implemented"<<std::endl;
}

void Point::rotate(float Fi) 
{
    std::cout<< "Point::rotate - Thix method not implemented"<<std::endl;
}

void Point::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    if(x_min < posX)
        x_min = posX;

    if(y_min < posY)
        x_min = posX;

    if(x_max < posX)
        x_max = posX;

    if(y_max < posY)
        y_max = posX;    
}