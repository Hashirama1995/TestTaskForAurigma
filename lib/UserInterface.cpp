#include "UserInterface.h"

Builder::Builder()
{   
}
Builder::~Builder()
{
    if(bitmap != nullptr){
        delete bitmap;
    }
    
    std::cout<<"Builder delete"<<std::endl;   
}
bool Builder::createFile(char* name, int width, int height, COLORS clr)
{
    switch(clr)
    {
        case COLORS::RGB:{
            bitmap = new Bitmap(name,width,height,new RGBColor(0,0,0));
            return true;
        }

        case COLORS::CMYK:{
            bitmap = new Bitmap(name,width,height,new CMYKColor(75,68,67,90));
            return true;
        }
    }

    return false;
}

std::shared_ptr<Point> Builder::createPoint(int x_coord, int y_coord, ColorInterface* clr)
{
    std::shared_ptr<Point> temp (reinterpret_cast<Point*>(new Point(*bitmap, x_coord, y_coord, clr)));
    return temp;
}

std::shared_ptr<Line> Builder::createLine(int x1, int y1, int x2, int y2, ColorInterface* clr)
{
    std::shared_ptr<Line> temp ( reinterpret_cast<Line*>(new Line(*bitmap, x1, y1, x2, y2, clr)));
    return temp;
}


std::shared_ptr<BezierBurve3> Builder::createBezierBurve3(Point2D p0, Point2D p1, Point2D p2, Point2D p3, int precision, ColorInterface * clr)
{
    std::shared_ptr<BezierBurve3> temp (reinterpret_cast<BezierBurve3*>(new BezierBurve3(*bitmap, p0, p1, p2, p3, precision, clr)));
    return temp;
}


std::shared_ptr<Ellipse> Builder::createEllipse(float x_, float y_, float rx_, float ry_, int numSegm, ColorInterface * clr)
{
    std::shared_ptr<Ellipse> temp (reinterpret_cast<Ellipse*>(new Ellipse(*bitmap, x_, y_, rx_, ry_, numSegm, clr)));
    return temp;
}

ContainerFigure2D Builder::createContainer()
{
    return ContainerFigure2D();
}

bool Builder::drawImage()
{
    return bitmap->draw();
}