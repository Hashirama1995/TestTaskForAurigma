#pragma once
#include "Colors.h"
#include <map>

namespace Object2D{
    
    class Image{
        virtual pixel setCurrentColor(ColorInterface* color) = 0;
        virtual int transform_XY_forArrayInx(int x, int y) = 0;
        virtual bool draw() = 0;
        virtual void putPixel(int x, int y, ColorInterface* color) = 0;
        virtual void putPixels(std::pair<int,int>* coords, int size, ColorInterface* color) = 0;
    };


    class Bitmap : public Image
    {
    
    private:
        char signature[2];                  //file type 'B''M' for .bmp
        unsigned int size;                  // size in baits
        unsigned short reserved_1;          // reserved for what?
        unsigned short reserved_2;          // reserved for what?
        unsigned int pos_of_start;          // offset
        char name[100]{0};                  // name
        unsigned int size_header = 40;           // default size for .bmp= 40
        unsigned int width;                 
        unsigned int height;
        unsigned short num;                     // number of planes
        unsigned short bit_per_pixel;           // color deep
        unsigned int compression = 0;           // compression type
        unsigned int size_of_compression= 0;    // default = 0
        unsigned int horizontal_resolution= 0;  // default = 0
        unsigned int vertical_resolution= 0;    // default = 0
        unsigned int used_color;                //кол-во используемых цветов
        unsigned int main_color;                //кол-во важных цветов

        pixel *pix;
        ColorInterface* pixel_color = nullptr;

        unsigned int img_size;                  //image size
        unsigned int bit_img_size;              //bit_image_size

    private:
        pixel setCurrentColor(ColorInterface* color) override;
        int transform_XY_forArrayInx(int x, int y) override;


    public:
        Bitmap(char* p, int width, int height, ColorInterface* color) ;  
        ~Bitmap();
        
        bool draw() override;                                            // create picture
        void putPixel(int x, int y, ColorInterface* color) override;     // set pixel color 
        void putPixels(std::pair<int,int>* coords, int size, ColorInterface* color) override;
        std::pair<unsigned int,unsigned int> getPictureSize();
    };
}
