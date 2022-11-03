#include <iostream>
#include "UserInterface.h"


using namespace Object2D;

int main()
{
    ColorInterface* color = new RGBColor(100,100,100);

    Builder builder;
    builder.createFile("simba",1024,1024, COLORS::RGB);
    //std::shared_ptr<Point> point =      builder.createPoint(100,100, new RGBColor(100,100,100));
    //std::shared_ptr<Line> line =        builder.createLine(200,200,400,400, new RGBColor(123,255,23));
    //std::shared_ptr<BezierBurve3> burve = builder.createBezierBurve3(Point2D(250,250), Point2D(500,500),Point2D(800,800), Point2D(250,200),3, new RGBColor(255,2,123));
    //std::shared_ptr<Ellipse> ellipse =  builder.createEllipse(300,300,200,300,360,new RGBColor(123,2,11));
    std::shared_ptr<Point> point =      builder.createPoint(100,100, color);
    color->setColor(123,255,23);
    std::shared_ptr<Line> line =        builder.createLine(200,200,400,400, color);
    color->setColor(255,2,123);
    std::shared_ptr<BezierBurve3> burve = builder.createBezierBurve3(Point2D(250,250), Point2D(500,500),Point2D(800,800), Point2D(250,200),3, color);
    color->setColor(123,2,11);
    std::shared_ptr<Ellipse> ellipse =  builder.createEllipse(300,300,200,300,360,color);

    ContainerFigure2D container =       builder.createContainer();

    container.add(point);
    container.add(line);
    container.add(burve);
    container.add(ellipse);

    ContainerFigure2D container2 = builder.createContainer();
    color->setColor(0,0,123);
    std::shared_ptr<BezierBurve3> burve2 = builder.createBezierBurve3(Point2D(40,250), Point2D(500,500),Point2D(800,600), Point2D(800,200),3, color);
    container2.add(burve2);

    container.add(&container2);
    container.rasterization();
    

    if(builder.drawImage())
    {
        std::cout<<"NICE!"<<std::endl;
    }
    return 0;
}