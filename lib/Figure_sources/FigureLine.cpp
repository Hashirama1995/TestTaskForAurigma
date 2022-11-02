#include "Figure.h"

using namespace Object2D;

/*********_Implementation Line_*********/

Line::Line(Bitmap& pic, int x1_, int y1_, int x2_, int y2_, ColorInterface* clr)
                            :picture(pic), x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(clr)
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(x1, y1, sizePic.first, sizePic.second);
    validatePoint(x2, y2, sizePic.first, sizePic.second);
}

Line::Line(Bitmap& pic, Point2D p0, Point2D p1, ColorInterface* clr)
                            :picture(pic), x1(p0.x), y1(p0.y), x2(p1.x), y2(p1.y), color(clr)
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(x1, y1, sizePic.first, sizePic.second);
    validatePoint(x2, y2, sizePic.first, sizePic.second);
}

Line::~Line()
{   
    if(color)
        delete color;   // ЕСТЬ ПРОБЛЕМА!
} 

void Line::setColor(ColorInterface* color)
{

}



void Line::rasterization()
{
    calculateBresenthemCoords(x1, y1, x2, y2);
}


void Line::putPixel(int x, int y)
{
    picture.putPixel(x,y,color);
}

void Line::affineMatrixMultiply(float matrix_[3][3])
{
    x1 = x1 * matrix_[0][0] + y1 * matrix_[1][0] + matrix_[2][0];
    y1 = x1 * matrix_[0][1] + y1 * matrix_[1][1] + matrix_[2][1];

    x2 = x2 * matrix_[0][0] + y2 * matrix_[1][0] + matrix_[2][0];
    y2 = x2 * matrix_[0][1] + y2 * matrix_[1][1] + matrix_[2][1];
}

void Line::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    if(x_min < (x1 < x2 ? x1 : x2))
        x_min = (x1 < x2 ? x1 : x2);

    if(y_min < (y1 < y2 ? y1 : y2))
        x_min = (y1 < y2 ? y1 : y2);

    if(x_max < (x1 < x2 ? x2 : x1))
        x_max = (x1 < x2 ? x2 : x1);

    if(y_max < (y1 < y2 ? y2 : y1))
        y_max = (y1 < y2 ? y2 : y1);
}


void Line::shift(float dx, float dy)
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    
    validateToShift(dx,dy,x1,y1,sizePic.first,sizePic.second);
    validateToShift(dx,dy,x2,x2,sizePic.first,sizePic.second);

    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};

    matrixMultiply(x1,y1,tempMatrix);
    matrixMultiply(x2,y2,tempMatrix);
}



void Line::zoom(float Sx, float Sy)
{
    // TODO - проверка на корректность Sx, Sy

    float tempMatrix[3][3] = {{Sx,0,0},{0,Sy,0},{0,0,1}};

    std::cout<< x1 << "-" << y1<< " and "<< x2 << "-" << y2;
    matrixMultiply(x1,y1,tempMatrix);
    matrixMultiply(x2,y2,tempMatrix);
    std::cout<<" transform to :" << x1<< "-" << y1 << " and "<< x2 << "-" << y2 << std::endl;
}

void Line::rotate(float Fi) 
{   
    // Беда
    // НЕ РАБОТАЕТ!!!

    /*
    Fi = Fi * M_PI/180;         
    float sinF = sin(Fi);
    float cosF = cos(Fi);

    float tempMatrix[3][3] = {{cosF, sinF, 0}, {-sinF, cosF ,0}, {0, 0, 1}};

    std::cout<< x1 << "-" << y1<< " and "<< x2 << "-" << y2;
    affineMatrixMultiply(tempMatrix);
    std::cout<<" transform to :" << x1<< "-" << y1 << " and "<< x2 << "-" << y2 << std::endl;
    */
}