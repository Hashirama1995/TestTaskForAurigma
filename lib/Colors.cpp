#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include "Colors.h"

using namespace Object2D;

// RGB COLORS
void RGBColor::setColor(float r, float g, float b)
{
    float array[] = {r, g, b};
    setColor(array,3);
}

void RGBColor::setColor(float * array, size_t arraySize) 
{
    if(arraySize == 3)
    {
        R = static_cast<unsigned char>(array[0]);
        B = static_cast<unsigned char>(array[1]);
        G = static_cast<unsigned char>(array[2]);
    }
}

pixel RGBColor::getColor()
{
    pixel res;
    res.r = R;
    res.b = B;
    res.g = G;

    return res;    
}
RGBColor::~RGBColor() {}



// CMYK COLORS
void CMYKColor::setColor(float c, float m, float y, float k)
{
    float array[] = {c, m, y,k};
    setColor(array, 4);
}

void CMYKColor::setColor(float * array, size_t arraySize)
{
    if(arraySize == 4)
    {
       C = static_cast<double>(array[0]);
       M = static_cast<double>(array[1]);
       Y = static_cast<double>(array[2]);
       K = static_cast<double>(array[3]);
    }
}


pixel CMYKColor::getColor()
{
    pixel res;
    res.r = (unsigned char)(255 * (1 - C) * (1 - K));
	res.g = (unsigned char)(255 * (1 - M) * (1 - K));
	res.b = (unsigned char)(255 * (1 - Y) * (1 - K));

    return res;    
}

CMYKColor::~CMYKColor() {}