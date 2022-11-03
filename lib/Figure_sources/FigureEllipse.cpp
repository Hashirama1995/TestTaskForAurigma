#include "Figure.h"

using namespace Object2D;

/*********_Implementation Ellipse*********/

Ellipse::Ellipse(Bitmap& pic, float x_, float y_, float rx_, float ry_, int numSegm, ColorInterface* clr)
    :picture(pic), xCenter(x_), yCenter(y_), rx(rx_), ry(ry_), num_segments(numSegm), color(clr), current_color(clr->getColor())
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();

    if(rx > sizePic.first/2 - 1)
    {
        rx = sizePic.first/2 - 1;
    }
    else if (ry > sizePic.second/2 - 1)
    {
        ry = sizePic.first/2 - 1;
    }

    if(xCenter >= sizePic.first - rx - 1)
    {
        xCenter = sizePic.first - rx - 1;
    }
    else if(xCenter <= 0 + rx + 1)
    {
        xCenter = 0 + rx + 1;
    }

    if(yCenter >= sizePic.second - ry - 1)
    {
        yCenter = sizePic.second - ry - 1;
    }
    else if(yCenter <= 0 + ry + 1)
    {
        yCenter = 0 + ry + 1;
    }

}

Ellipse::~Ellipse()
{
    //delete color;
    std::cout<<"delete Ellipse"<<std::endl;
}

void Ellipse::setColor(ColorInterface* color_)
{
    //color = color_;    
    current_color = color_->getColor() ;
}

void Ellipse::rasterization()
{
    const float step = 2.0 * M_PI/num_segments;

    std::list<Point2D> list;
    
    for (float angle = 0; angle < 2.0 * M_PI; angle += step)
    {
        Point2D temp(rx * cosf(angle), ry * sinf(angle));
        list.push_back(temp);
    }
    if(rotationAngle != 0)
    {
        float sinF = sin(rotationAngle/180 * M_PI);
        float cosF = cos(rotationAngle/180 * M_PI);
        float DX = 0;
        float DY = 0;
        float tempMatrix[3][3] = {{cosF, sinF, 0}, {-sinF, cosF ,0}, {DX, DY, 1}};
        float resX, resY;

        for(std::list<Point2D>::iterator first = list.begin();  first != list.end(); ++first)
        {
            resX = first->x - DX;
            resY = first->y - DY;
            matrixMultiply(resX, resY, tempMatrix);
            first->x = resX;
            first->y = resY;
        }
    }

    std::list<Point2D>::iterator second = list.begin();
    ++second;

    for (std::list<Point2D>::iterator first = list.begin();  second != list.end(); ++first,++second)
    {
        calculateBresenthemCoords(first->x+xCenter, first->y+yCenter, second->x+xCenter, second->y+yCenter);
    }
}

void Ellipse::putPixel(int x, int y)
{
    //picture.putPixel(x,y,color); current_color
    picture.putPixel(x,y,current_color); 
}


void Ellipse::shift(float dx, float dy)
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validateToShift(dx,dy,xCenter,yCenter,sizePic.first,sizePic.second);
    
    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};
    matrixMultiply(xCenter, yCenter, tempMatrix);
}

void Ellipse::zoom(float Sx, float Sy)
{
    const float tempMatrix[3][3] = {{abs(Sx), 0, 0},{0, abs(Sy), 0},{0, 0, 1}};
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    if(rx * Sx > sizePic.first && ry * Sy > sizePic.second)
    {
        std::cout<< "Object Ellipse: was not zoomed. Мultiplier is too high" <<std::endl;
    }

    matrixMultiply(rx, ry, tempMatrix);
}

void Ellipse::rotate(float Fi)
{
    rotationAngle = Fi;
}

void Ellipse::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    x_min = (x_min < xCenter - rx ? x_min : xCenter - rx);
    y_min = (y_min < yCenter - ry ? y_min : yCenter - ry);

    x_max = (x_max > xCenter + rx ? x_max : xCenter + rx);
    y_max = (y_max > yCenter + ry ? y_max : yCenter + ry);
}