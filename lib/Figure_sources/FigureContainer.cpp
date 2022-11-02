#include "Figure.h"

using namespace Object2D;

void FigureObject2D::validateToShift(float& dx, float& dy ,int x, int y, const unsigned int sizeX, const unsigned int sizeY)
{
     if(x + dx > sizeX)
    {
        dx = sizeX - x;
    }
    else if(x + dx < 0)
    {
        dx = -x;
    }
    
    if(y+dy > sizeY)
    {
        dy = sizeY - y;
    }
    else if(y + dy < 0)
    {
        dy = -y;
    }
    
}

void FigureObject2D::validatePoint(int& x, int& y, const unsigned int sizeX, const unsigned int sizeY)
{
    if(x > sizeX)
    {
        x = sizeX;
    }
    else if (x < 0)
    {   
        x = 0;
    }

    if(y > sizeY)
    {
        y = sizeY;
    }
    else if (y < 0)
    {   
        y = 0;
    }
}

void FigureObject2D::validatePoint(float& x, float& y, const unsigned int sizeX, const unsigned int sizeY)
{
    if(x > sizeX)
    {
        x = static_cast<float>(sizeX);
    }
    else if (x < 0)
    {   
        x = 0.0f;
    }

    if(y > sizeY)
    {
        y = x = static_cast<float>(sizeY);;
    }
    else if (y < 0)
    {   
        y = 0.0f;
    }
}

void FigureObject2D::matrixMultiply(int& x, int& y, const float matrix[3][3])
{
    x = x * matrix[0][0] + y * matrix[1][0] + matrix[2][0];
    y = x * matrix[0][1] + y * matrix[1][1] + matrix[2][1];

   // x2 = x2 * matrix[0][0] + y2 * matrix[1][0] + matrix[2][0];
   // y2 = x2 * matrix[0][1] + y2 * matrix[1][1] + matrix[2][1];
}

void FigureObject2D::matrixMultiply(Point2D& point, const float matrix[3][3])
{
    point.x = point.x * matrix[0][0] + point.y * matrix[1][0] + matrix[2][0];
    point.y = point.x * matrix[0][1] + point.y * matrix[1][1] + matrix[2][1];
}


void FigureObject2D::calculateBresenthemCoords(int x1, int y1, int x2, int y2)
{
    int const deltaX = x2 - x1;
    int const deltaY = y2 - y1;
    int const absDeltaX = std::abs(deltaX);
    int const absDeltaY = std::abs(deltaY);

    int accreation = 0;                     //increment for the second coordinate
    
    if(absDeltaX >=absDeltaY)
    {
        int y = y1;
        const int direction = deltaY !=0 ? (deltaY > 0 ? 1 : -1) : 0;

        int i = 0;
        for(int x = x1;
            deltaX > 0 ? x <= x2 : x >= x2;
            deltaX > 0 ? x++ : x--)
        {
            putPixel(x,y);
            accreation += absDeltaY;

            if(accreation >= absDeltaX)
            {
                accreation -= absDeltaX;
                y += direction;
            }
        }
    }
    else
    {
        int x = x1;
        const int direction = deltaX !=0 ? (deltaX > 0 ? 1 : -1) : 0;

        int i = 0;
        for(int y = y1;
            deltaY > 0 ? y <= y2 : y >= y2;
            deltaY > 0 ? y++ : y--)
        {
            putPixel(x,y);
            accreation += absDeltaX;

            if(accreation >= absDeltaY)
            {
                accreation -= absDeltaY;
                x += direction;
            }
        }
        
    }
}


/*************_Container_**************/ 

ContainerFigure2D::ContainerFigure2D()
{

}
ContainerFigure2D::~ContainerFigure2D()
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->~Figure2D();  // TEST!!!
    }
    std::cout<<"Delete container"<<std::endl;
}

Figure2D* ContainerFigure2D::add(Figure2D* item)
{
    container.push_back(item);
    return item;
}

void ContainerFigure2D::rasterization()
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->rasterization();
    }
}

void ContainerFigure2D::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->getEdges(x_min, y_min, x_max, y_max);
    }
}


void ContainerFigure2D::shift(float dx, float dy)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->shift(dx, dy);
    }
}

void ContainerFigure2D::zoom(float Sx, float Sy)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->zoom(Sx, Sy);
    }
}

void ContainerFigure2D::rotate(float Fi)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->rotate(Fi);
    }
}