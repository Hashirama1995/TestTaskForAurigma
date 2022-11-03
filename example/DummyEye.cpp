#include <iostream>
#include "UserInterface.h"


int main()
{
    RGBColor color(0,0,0);
    Builder builder;
    builder.createFile("example_eye",1060,1060, COLORS::RGB);
    std::shared_ptr<Ellipse> ellipse =  builder.createEllipse(500.0,500.0,100.0,200,360,&color);
    
    color.setColor(211,3,252);
    
    
    int i = 0;
    for(i; i <= 60; i+=15)
    {
        ellipse->rasterization();
        ellipse->rotate(i);
        color.setColor(211+i/2,3+i,252);
        ellipse->setColor(&color);
    }

    for(i; i <= 120; i+=15)
    {
        ellipse->rasterization();
        ellipse->rotate(i);
        color.setColor(252,65+i,3);
        ellipse->setColor(&color);
    }

    for(i; i <= 180; i+=15)
    {
        ellipse->rasterization();
        ellipse->rotate(i);
        color.setColor(252,252,3+i);
        ellipse->setColor(&color);
    }

    Object2D::Point2D point (110,350);
    Object2D::Point2D point2 (300,1050);
    Object2D::Point2D point3 (800,550);
    Object2D::Point2D point4 (1050,750);
    color.setColor(252,3,65);

    std::shared_ptr<BezierBurve3> burve = builder.createBezierBurve3(point,point2,point3, point4, 3, &color);
   
    burve->rasterization();
    color.setColor(252,3,211);
    burve->shift(0,-10);
    burve->rasterization();
    color.setColor(3,252,232);
    burve->shift(0,20);
    burve->rasterization();
    color.setColor(3,252,232);
    burve->shift(0,20);
    burve->rasterization();


    point.x = 150; point.y =320;
    point2.x = 700; point2.y =150;
    point3.x = 800; point3.y = 500;
    point4.x = 1000; point4.y =550;
    std::shared_ptr<BezierBurve3> burve2 = builder.createBezierBurve3(point,point2,point3, point4, 3, &color);
    color.setColor(3,252,232);
    burve2->rasterization();
    color.setColor(45,252,232);
    burve2->shift(0,-10);
    burve2->rasterization();


    if(builder.drawImage())
    {
        std::cout<<"NICE!"<<std::endl;
    }
    
    return 0;
}