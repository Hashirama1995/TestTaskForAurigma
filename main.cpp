#include "Figure.h"
#include "Bitmap.h"
#include "Figure.h"
#include <iostream>

int main()
{
    Object2D::RGBColor color; 
    Object2D::Bitmap bmp("boba",1024,1024, &color);
    
    Object2D::ContainerFigure2D cont_inner;
    Object2D::ContainerFigure2D cont;


    for(int i = 0; i < 3; i++)
    {
        cont_inner.add(new Object2D::Point());
    }

    for(int i = 0; i < 5; i++)
    {
        cont.add(new Object2D::Point());
    }

    cont.add(&cont_inner);
    
    cont.create();
    
    color.setColor(215,214,215);

    for(int i =0; i<600; i++)
    {
        bmp.putPixel(2+i, 100 + i, &color);
    }


    if(!bmp.draw())
        std::cout<<"BAD";
        
    std::cout<<"ready";
    return 1;
}