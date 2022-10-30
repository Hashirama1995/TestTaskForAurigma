#include "engine.h"
#include "Bitmap.h"

int main()
{
    Object2D::RGBColor color; 
    
    Object2D::Bitmap bmp("boba",1024,1024, &color);

    if(!bmp.draw())
        std::cout<<"BAD";
        
    std::cout<<"ready";
    return 1;
}