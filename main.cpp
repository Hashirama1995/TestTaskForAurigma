#include "Figure.h"
#include "Bitmap.h"
#include "Figure.h"
#include <iostream>
#include <unordered_map>

int main()
{
    //std::unordered_map<std::string, Object2D::Bitmap> map_bitmaps;

    Object2D::RGBColor color; 
    Object2D::Bitmap bmp("boba",1024,1024, &color);

    Object2D::Point2D point (100,150);
    Object2D::Point2D point2 (200,800);
    Object2D::Point2D point3 (300,500);
    Object2D::Point2D point4 (200,100);


    
    //map_bitmaps.emplace("boba",bmp);
    
   // Object2D::ContainerFigure2D cont_inner;
    Object2D::ContainerFigure2D cont;

    Object2D::Ellipse ellips(bmp, 500.0, 200.0, 100, 200, 360+180, new Object2D::RGBColor(255,255,255));

    cont.add(&ellips);

    Object2D::BezierBurve3 burve (bmp,point,point2,point3, point4, 3, new Object2D::RGBColor(255,255,255));

    cont.add(new Object2D::Line(bmp,200,200,400,450,new Object2D::RGBColor(255,255,255)));
    cont.add(new Object2D::BezierBurve3(bmp,point,point2,point3, point4, 3, new Object2D::RGBColor(255,255,255)));

    int xmin = 9999;
    int ymin = 9999;
    int xmax = -1;
    int ymax = -1;

    cont.getEdges(xmin, ymin, xmax, ymax);

    std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
    std::cout<<"x_min: "<< xmin<<" y_min: "<< ymin<<std::endl;
    std::cout<<"x_max: "<< xmax<<" y_max: "<< ymax<<std::endl;
    //Object2D::Line testObj(bmp,200,200,400,450, new Object2D::RGBColor(255,255,255));

    //testObj.rotate(60);
    
    //cont.add(&testObj);
    /*
    for(int i = 0; i < 50; i++)
    {
        cont_inner.add(new Object2D::Point(bmp, 255 ,500+i ,new Object2D::RGBColor(215, 200, 114)   ) );
    }

    for(int i = 0; i < 35; i++)
    {
        cont.add(new Object2D::Point(bmp ,255+i ,500 ,new Object2D::RGBColor(112,0,22)  ) );
    }

    cont.add(&cont_inner);*/
    
    cont.rasterization();
    //cont.create();
    /*
    color.setColor(215,214,215);

    for(int i =0; i<600; i++)
    {
        bmp.putPixel(2+i, 100 + i, &color);
    }
    */


    if(!bmp.draw())
        std::cout<<"BAD";
        
    std::cout<<"ready";
    return 1;
}