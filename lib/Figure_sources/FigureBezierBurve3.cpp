#include "Figure.h"

using namespace Object2D;


/*********_Implementation BezierBurve*********/
BezierBurve3::BezierBurve3(Bitmap& pic, Point2D p0, Point2D p1, Point2D p2, Point2D p3,int precision_, ColorInterface * clr)
    :picture(pic), P0(p0), P1(p1), P2(p2), P3(p3), precision(precision_), color(clr), current_color(clr->getColor())
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validatePoint(P0.x, P0.y, sizePic.first, sizePic.second);
    validatePoint(P1.x, P1.y, sizePic.first, sizePic.second);
    validatePoint(P2.x, P2.y, sizePic.first, sizePic.second);
    validatePoint(P3.x, P3.y, sizePic.first, sizePic.second);

}
BezierBurve3::~BezierBurve3()
{
    //delete color;
    std::cout<<"delete Burve"<<std::endl;
}

void BezierBurve3::setColor(ColorInterface* color) 
{
    current_color = color->getColor() ;
}

Point2D BezierBurve3::calculatePoint(float step)
{
    Point2D result;
    result.x = pow((1.0f - step), 3)*P0.x  +  3.0f *pow((1.0-step),2)*step*P1.x +  3.0f*(1.0-step)*pow(step,2)*P2.x  +  pow(step,3)*P3.x;
    result.y = pow((1.0f -step), 3)*P0.y  +  3.0f *pow((1.0-step),2)*step*P1.y +  3.0f*(1.0-step)*pow(step,2)*P2.y  +  pow(step,3)*P3.y;
    return result;
}

void BezierBurve3::rasterization() 
{
    float step = 1.0f;
    for (int i =0; i < precision; i++)
    {
        step /= 10.0f;
    }

    std::list<Point2D> list;

    for(float i = 0.0; i < 1; i+=step)
    {
        list.push_back(calculatePoint(i));
    }

    std::list<Point2D>::iterator second = list.begin();
    ++second;

    for (std::list<Point2D>::iterator first = list.begin();  second != list.end(); ++first,++second)
    {
        calculateBresenthemCoords(first->x, first->y, second->x, second->y);
    }
}


void BezierBurve3::putPixel(int x, int y)
{
   // picture.putPixel(x,y,color); current_color
   picture.putPixel(x,y,current_color);
}


void BezierBurve3::shift(float dx, float dy) 
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    validateToShift(dx,dy, P0.x,P0.y, sizePic.first, sizePic.second);
    validateToShift(dx,dy, P1.x,P1.y, sizePic.first, sizePic.second);
    validateToShift(dx,dy, P2.x,P2.y, sizePic.first, sizePic.second);
    validateToShift(dx,dy, P3.x,P3.y, sizePic.first, sizePic.second);

    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};

    matrixMultiply(P0, tempMatrix);
    matrixMultiply(P1, tempMatrix);
    matrixMultiply(P2, tempMatrix);
    matrixMultiply(P3, tempMatrix);
}

void BezierBurve3::zoom(float Sx, float Sy) 
{
    std::pair<unsigned int, unsigned int>sizePic = picture.getPictureSize();
    const float tempMatrix[3][3] = {{abs(Sx), 0, 0},{0, abs(Sy), 0},{0, 0, 1}};

    Point2D temp[4];

    temp[0] = P0; temp[1] = P1; temp[2] = P2; temp[3] = P3;

    matrixMultiply(P0, tempMatrix);
    matrixMultiply(P1, tempMatrix);
    matrixMultiply(P2, tempMatrix);
    matrixMultiply(P3, tempMatrix); 

    int x_min = 9999999, y_min = 9999999, x_max = -1, y_max = -1;
    getEdges(x_min, y_min, x_max, y_max);

    if (x_min < 0 || y_min < 0 || x_max > sizePic.first || y_max > sizePic.second)
    {
        P0 = temp[0]; P1 = temp[1]; P2 = temp[2]; P3 = temp[3];
        std::cout<< "Object BezierBurve3: was not zoomed. Мultiplier is too high" <<std::endl;
    }         
}

void BezierBurve3::rotate(float Fi) 
{
    float radian = Fi/180.0f * M_PI;         
    float sinF = sin(radian);
    float cosF = cos(radian);
    float DX = abs(P0.x + P3.x)/2 ;
    float DY = abs(P0.y + P3.y)/2 ;

    float resX0 = P0.x - DX;
    float resY0 = P0.y - DY;
    float resX1 = P1.x - DX;
    float resY1 = P1.y - DY;
    float resX2 = P2.x - DX;
    float resY2 = P2.y - DY;
    float resX3 = P3.x - DX;
    float resY3 = P3.y - DY;

    float tempMatrix[3][3] = {{cosF, sinF, 0}, {-sinF, cosF ,0}, {DX, DY, 1}};
    
    matrixMultiply(resX0,resY0,tempMatrix);
    matrixMultiply(resX1,resY1,tempMatrix);
    matrixMultiply(resX2,resY2,tempMatrix);   
    matrixMultiply(resX3,resY3,tempMatrix);

    P0.x = resX0;
    P0.y = resY0;
    P1.x = resX1;
    P1.y = resY1;
    P2.x = resX2;
    P2.y = resY2;
    P3.x = resX3;
    P3.y = resY3;
}


void BezierBurve3::getEdges(int& x_min, int& y_min, int& x_max, int& y_max) 
{

   std::vector<float> listX;
   listX.push_back(P0.x);
   listX.push_back(P3.x);

   std::vector<float> listY;
   listY.push_back(P0.y);
   listY.push_back(P3.y);

    // search for extremum points
    // Main idea - we have a polynomic 3rd order function

    //P{x,y} = (1-t)^3 * P0{x,y} + 3 * (1-t)^2 * t * P1{x,y} + 3 * (1-t) * t^2 * P2{x,y} + t^3 * P3{x,y}

    // if if we take the derivative, 
    //      we get a polynomial of the 2nd order and we can find the radicals (for (P{x,y})' = 0)
    //      of this polynomial through the discriminant.
    // Radicals - is 't', at which x and y have the largest and smallest values - extremum points.

    //in end, we have polynomial of the 2nd order
    /* t^2 * (-3 * P0{x,y} + 5* P1{x,y} - 9 * P2{x,y} + 3 * P3{x,y}) +
                            + t * (6 * P0{x,y} - 8 * P1{x,y} + 6 * P2{x,y}) + (3 * P0{x,y} - 3 * P1{x,y}) = 0  */


    float aaX = 3 *(-P0.x + 3 * P1.x - 3 * P2.x + P3.x);
    float bbX = 6 * (P0.x - 2 * P1.x + P2.x);
    float ccX = 3 * (P1.x - P0.x);
    float DiskX = pow(bbX, 2) - 4 * aaX * ccX;
    

    if( DiskX > 0 )
    {
        float t1 = 0, t2 = 0;

        t1 = (-bbX + sqrt(DiskX)) / (2 * aaX);
        t2 = (-bbX - sqrt(DiskX)) / (2 * aaX);
        std::cout<<"t1 max= "<< t1 <<"  t2 max= "<< t2 << std::endl;

        Point2D p1 = calculatePoint(t1);
        Point2D p2 = calculatePoint(t2);
        std::cout<<"X1 max= "<< p1.x <<"  X2 max= "<< p2.x << std::endl;

        if(t1 > 0 && t1 <=1)
        {
            listX.push_back(p1.x);
        }
        if(t2 >0 && t2 <=1)
        {
            listX.push_back(p2.x);
        }

    }
    else if( DiskX == 0 )
    {
        float t = 0, x = 0;

        t = (-1 * bbX) / (2 * aaX);
        std::cout<<" t max= "<< t << std::endl;

        Point2D p = calculatePoint(t);
        std::cout<<" X max= "<< p.x << std::endl;

        if(t > 0 && t <=1)
        {
            listX.push_back(p.x);
        }
    }
    else if( DiskX < 0 )
    {
        std::cout<<" DX < 0 "<< std::endl;
    }



    float aaY = 3 *(-P0.y + 3 * P1.y - 3 * P2.y + P3.y);
    float bbY = 6 * (P0.y - 2 * P1.y + P2.y);
    float ccY = 3 * (P1.y - P0.y);
    float DiskY = pow(bbY, 2) - 4 * aaY * ccY;

    if( DiskY > 0 )
    {
        float t1 = 0, t2 = 0;

        t1 = (-bbY + sqrt(DiskY)) / (2 * aaY);
        t2 = (-bbY - sqrt(DiskY)) / (2 * aaY);
        std::cout<<"t1 Ymax= "<< t1 <<"  t2 Ymax= "<< t2 << std::endl;

        Point2D p1 = calculatePoint(t1);
        Point2D p2 = calculatePoint(t2);
        std::cout<<"Y1 max= "<< p1.y <<"  Y2 max= "<< p2.y << std::endl;

        if(t1 > 0 && t1 <=1)
        {
            listY.push_back(p1.y);
        }
        if(t2 > 0 && t2 <=1)
        {
            listY.push_back(p2.y);
        }
    }
    else if( DiskY == 0 )
    {
        float t = 0, x = 0;

        t = (-1 * bbY) / (2 * aaY);
        std::cout<<" t Ymax= "<< t << std::endl;

        Point2D p = calculatePoint(t);
        std::cout<<"  Y max= "<< p.y << std::endl;

        if(t > 0 && t <=1)
        {
            listY.push_back(p.y);
        }
    }
    else if( DiskY < 0 )
    {
        std::cout<<" DY < 0"<< std::endl;
    }

    //Sort and check

    std::sort(listX.begin(),listX.end());
    std::sort(listY.begin(),listY.end());

        /******TEST BLOCK!**********/
    std::cout<<std::endl;
    for(auto& i : listX)
    {
        std::cout<<i<< " ";
    }

    std::cout<<std::endl;
    for(auto& i : listY)
    {
        std::cout<<i<< " ";
    }
        /******TEST BLOCK!**********/

    x_min = (x_min < listX.front() ? x_min : listX.front());
    y_min = (y_min < listY.front() ? y_min : listY.front());    
    x_max = (x_max > listX.back() ? x_max : listX.back());
    y_max = (y_max > listY.back() ? y_max : listY.back());
}