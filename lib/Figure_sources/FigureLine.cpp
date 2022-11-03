#include "Figure.h"

using namespace Object2D;

/*********_Implementation Line_*********/

Line::Line(Bitmap& pic, int x1_, int y1_, int x2_, int y2_, ColorInterface* clr)
                            :picture(pic), x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(clr), current_color(clr->getColor())
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(x1, y1, sizePic.first, sizePic.second);
    validatePoint(x2, y2, sizePic.first, sizePic.second);
}

Line::Line(Bitmap& pic, Point2D p0, Point2D p1, ColorInterface* clr)
                            :picture(pic), x1(p0.x), y1(p0.y), x2(p1.x), y2(p1.y), color(clr), current_color(clr->getColor())
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(x1, y1, sizePic.first, sizePic.second);
    validatePoint(x2, y2, sizePic.first, sizePic.second);
}

Line::~Line()
{   
    //delete color;
    std::cout<<"delete Line"<<std::endl;     
} 

void Line::setColor(ColorInterface* color)
{
    current_color = color->getColor();
}



void Line::rasterization()
{
    calculateBresenthemCoords(x1, y1, x2, y2);
}


void Line::putPixel(int x, int y)
{
    //picture.putPixel(x,y,color); 
    picture.putPixel(x,y,current_color);
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
    const float tempMatrix[3][3] = {{abs(Sx), 0, 0},{0, abs(Sy), 0},{0, 0, 1}};

    int tempX1 = x1, tempY1 = y1, tempX2 = x2, tempY2 = y2;

    matrixMultiply(x1,y1,tempMatrix);
    matrixMultiply(x2,y2,tempMatrix);

    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    int x_min = 9999999, y_min = 9999999, x_max = -1, y_max = -1;
    getEdges(x_min, y_min, x_max, y_max);

    if (x_min < 0 || y_min < 0 || x_max > sizePic.first || y_max > sizePic.second)
    {
        x1 = tempX1; y1 = tempY1; x2 = tempX2; y2 = tempY2;
        std::cout<< "Object Line: was not zoomed. Мultiplier is too high" <<std::endl;
    }
}

void Line::rotate(float Fi) 
{   
    float radian = Fi/180.0f * M_PI;         
    float sinF = sin(radian);
    float cosF = cos(radian);
    float DX = abs(x2+x1)/2 ;
    float DY = abs(y2+y1)/2 ;

   std::cout<<"DX = " <<DX <<"  DY = " <<DY << std::endl;

    int resX1 = x1 - DX;
    int resY1 = y1 - DY;
    int resX2 = x2 - DX;
    int resY2 = y2 - DY;

    float tempMatrix[3][3] = {{cosF, sinF, 0}, {-sinF, cosF ,0}, {DX, DY, 1}};

    std::cout<< resX1 << "-" << resY1<< " and "<< resX2 << "-" << resY2;

    matrixMultiply(resX1,resY1,tempMatrix);
    matrixMultiply(resX2,resY2,tempMatrix);

    x1 = resX1; y1 = resY1; x2 = resX2; y2 = resY2;

    std::cout<<" transform to :" << x1<< "-" << y1 << " and "<< x2 << "-" << y2 << std::endl;
    
}