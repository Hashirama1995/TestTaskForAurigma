#include "Bitmap.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<cstdlib>

using namespace Object2D;

pixel Bitmap::setCurrentColor(ColorInterface* color)
{
    return pixel();
}

int Bitmap::transform_XY_forArrayInx(int x, int y)
{
    return 1;
}



Bitmap::Bitmap(char* p, int w, int h, ColorInterface* color): pixel_color (color)
{
    // WIDTH AND HEIGHT IMAGE
     width=w/4; height=h/4;
        width*=4; height*=4;
    //---------------- почему?

    // PUT THE NAME
    register int i;
    for ( i = 0; p[i]; ++i ) 
    {
        name[i] = p[i];
    }
    name[i]='.'; name[i+1]='b'; name[i+2]='m'; name[i+3]='p';
    //----------------

    // Info Header
    signature[0]='B'; signature[1]='M';
    reserved_1=0;
    reserved_2=0;
    pos_of_start=54;
    size_header=40;
    used_color=0;
    compression=0;
    horizontal_resolution=0;
    bit_per_pixel=24;
    main_color=0;
    num=1;
    size_of_compression=0;
    vertical_resolution=0;
    //------------

    // SIZE's
    bit_img_size=width*height*3;    // image data size in bytes
    size=bit_img_size+54;           // total file size in bytes
    img_size=width*height;          // picture size
    //------------

    pix = new pixel[img_size];      // create array of pixel
    pixel baseColor = pixel_color->getColor();

    for(int j = 0; j < img_size; j++)
    {   
        pix[j]= baseColor;
    }
}

Bitmap::~Bitmap()
{
    //delete [] pix;
    //delete [] pixel_color;
}

void Bitmap::putPixel(int x, int y, ColorInterface* color)
{

}

bool Bitmap::draw()
{
    std::ofstream img(name,std::ios::out | std::ios::binary);
    if (!img) {
        std::cout<<"Can not open the file!!\n";
        return false;
    }

    // First Header
    img.write((char *) &signature, 2);
    img.write((char *) &size, 4);
    img.write((char *) &reserved_1, 2);
    img.write((char *) &reserved_2, 2);
    img.write((char *) &pos_of_start, 4);

    // Second header
    img.write((char *) &size_header, 4);
    img.write((char *) &width, 4);
    img.write((char *) &height, 4);
    img.write((char *) &num, 2);
    img.write((char *) &bit_per_pixel, 2);
    img.write((char *) &compression, 4);
    img.write((char *) &size_of_compression, 4);
    img.write((char *) &horizontal_resolution, 4);
    img.write((char *) &vertical_resolution, 4);
    img.write((char *) &used_color, 4);
    img.write((char *) &main_color, 4);

    // image data
    img.write((char *) pix, bit_img_size);
    img.close();

    return true;
}