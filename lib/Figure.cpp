#include "Figure.h"

using namespace Object2D;

/*
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

*/

/*************_Container_**************/ 
/*
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
*/


/*********_Implementation Point_*********/
/*
Point::Point(Bitmap& pic, int x, int y, ColorInterface* clr)
                            :picture(pic), posX(x), posY(y), color(clr)
{
    
    std::cout<<"CHUMBA CREATE !! BIACH!"<<std::endl;
}

Point::~Point()
{
    delete color;
    std::cout<<"delete color"<<std::endl;
}

void Point::setColor(ColorInterface* color)
{

}

void Point::rasterization()
{
    // TODO - for what????
    std::cout<<"create point: "<< posX << "-" << posY <<std::endl;
    
}


void Point::putPixel(int x, int y)
{
    picture.putPixel(posX, posY, color);
}

void Point::shift(float dx, float dy)
{
    // TODO - проверка на корректность dx, dy

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
}*/




/*********_Implementation Line_*********/
/*
Line::Line(Bitmap& pic, int x1_, int y1_, int x2_, int y2_, ColorInterface* clr)
                            :picture(pic), x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(clr)
{
   
}

Line::Line(Bitmap& pic, Point2D p0, Point2D p1, ColorInterface* clr)
                            :picture(pic), x1(p0.x), y1(p0.y), x2(p1.x), y2(p1.y), color(clr)
{
   
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
    // TODO - проверка на корректность dx, dy

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
}*/

//void Line::rotate(float Fi) 
//{   
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
//}





/*********_Implementation BezierBurve*********/
/*
BezierBurve3::BezierBurve3(Bitmap& pic, Point2D p0, Point2D p1, Point2D p2, Point2D p3,int precision_, ColorInterface * clr)
    :picture(pic), P0(p0), P1(p1), P2(p2), P3(p3), precision(precision_), color(clr)
{   }

void BezierBurve3::setColor(ColorInterface* color) 
{

}

Point2D BezierBurve3::calculatePoint(float step)
{
    Point2D result;
    result.x = pow((1.0f - step), 3)*P0.x  +  3.0f *pow((1.0-step),2)*step*P1.x +  3.0f*(1.0-step)*pow(step,2)*P2.x  +  pow(step,3)*P3.x;
    result.y = pow((1.0f -step), 3)*P0.y  +  3.0f *pow((1.0-step),2)*step*P1.y +  3.0f*(1.0-step)*pow(step,2)*P2.y  +  pow(step,3)*P3.y;
    //std::cout <<"coord: " << result.first <<" - "<< result.second<<std::endl ;
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
    picture.putPixel(x,y,color);
}


void BezierBurve3::shift(float dx, float dy) 
{
    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};

    matrixMultiply(P0, tempMatrix);
    matrixMultiply(P1, tempMatrix);
    matrixMultiply(P2, tempMatrix);
    matrixMultiply(P3, tempMatrix);
}

void BezierBurve3::zoom(float Sx, float Sy) 
{
    const float tempMatrix[3][3] = {{Sx,0,0},{0,Sy,0},{0,0,1}};

    matrixMultiply(P0, tempMatrix);
    matrixMultiply(P1, tempMatrix);
    matrixMultiply(P2, tempMatrix);
    matrixMultiply(P3, tempMatrix);
}

void BezierBurve3::rotate(float Fi) 
{
    // Беда
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
    // t^2 * (-3 * P0{x,y} + 5* P1{x,y} - 9 * P2{x,y} + 3 * P3{x,y}) +
                           // + t * (6 * P0{x,y} - 8 * P1{x,y} + 6 * P2{x,y}) + (3 * P0{x,y} - 3 * P1{x,y}) = 0  


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

    x_min = (x_min < listX.front() ? x_min : listX.front());
    y_min = (y_min < listY.front() ? y_min : listY.front());    
    x_max = (x_max > listX.back() ? x_max : listX.back());
    y_max = (y_max > listY.back() ? y_max : listY.back());
}*/



/*********_Implementation Ellipse*********/
/*
Ellipse::Ellipse(Bitmap& pic, float x_, float y_, float rx_, float ry_, int numSegm, ColorInterface* clr)
    :picture(pic), xCenter(x_), yCenter(y_), rx(rx_), ry(ry_), num_segments(numSegm), color(clr)
{}


void Ellipse::setColor(ColorInterface* color)
{
    
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

    std::list<Point2D>::iterator second = list.begin();
    ++second;

    for (std::list<Point2D>::iterator first = list.begin();  second != list.end(); ++first,++second)
    {
        calculateBresenthemCoords(first->x+xCenter, first->y+yCenter, second->x+xCenter, second->y+yCenter);
    }
}

void Ellipse::putPixel(int x, int y)
{
    picture.putPixel(x,y,color);
}


void Ellipse::shift(float dx, float dy)
{
    const float tempMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}};

    matrixMultiply(xCenter, yCenter, tempMatrix);
}

void Ellipse::zoom(float Sx, float Sy)
{
    const float tempMatrix[3][3] = {{Sx,0,0},{0,Sy,0},{0,0,1}};
    
    matrixMultiply(xCenter, yCenter, tempMatrix);
}

void Ellipse::rotate(float Fi)
{
    // dont work
}

void Ellipse::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    x_min = (x_min < xCenter - rx ? x_min : xCenter - rx);
    y_min = (y_min < yCenter - ry ? y_min : yCenter - ry);

    x_max = (x_max > xCenter + rx ? x_max : xCenter + rx);
    y_max = (y_max > yCenter + ry ? y_max : yCenter + ry);
}*/