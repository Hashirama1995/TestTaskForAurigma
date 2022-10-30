#include "engine.h"

bool Engine2D::createBMPFile(int width, int height)
{
    static uint8_t counter = 0;
    counter++;

     std::ofstream file1;
     std::string filename = "newImage"+std::to_string(counter);
    
    file1.open(filename + ".bmp"); //,std::ios::out | std::ios::binary  
    if(!file1.is_open())
    {
        std::cout<<"File is not created"<<std::endl;
        file1.close();
        return false;
    }


    return true;
}