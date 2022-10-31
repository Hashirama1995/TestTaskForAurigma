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

    //map_bitmaps.emplace("boba",bmp);
    
   // Object2D::ContainerFigure2D cont_inner;
    Object2D::ContainerFigure2D cont;



    cont.add(new Object2D::Line(bmp,200,200,400,450,new Object2D::RGBColor(255,255,255)));

    Object2D::Line testObj(bmp,200,200,400,450, new Object2D::RGBColor(255,255,255));

    testObj.rotate(60);
    
    cont.add(&testObj);
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
    cont.create();
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