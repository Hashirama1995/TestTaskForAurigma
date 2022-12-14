#pragma once
namespace Object2D{

    enum class COLORS{
        RGB,
        CMYK
    };

    struct pixel {      //пиксель с тремя составляющими цвета
        unsigned char b = 0;
        unsigned char g = 0;
        unsigned char r = 0;
    };

    
    class ColorInterface
    {
    public:
        //virtual void setColor(float * array, size_t arraySize) = 0;
        virtual void setColor(float r, float g, float b, float a = 0) = 0;
        virtual pixel getColor() = 0;
        virtual ~ColorInterface(){}
    };



    class RGBColor : public ColorInterface
    {
    private:   
        unsigned char R;
        unsigned char G;
        unsigned char B;
    public:
        RGBColor(): R(0), G(0), B(0) {}
        RGBColor(int r, int g, int b): R(r), G(g), B(b) {}

        void setColor(float r, float g, float b, float a = 0);
        //void setColor(float * array, size_t arraySize) override;
        pixel getColor() override;
        ~RGBColor() override;
    };



    class CMYKColor : public ColorInterface
    {
    private:
        double C;
        double M;
        double Y;
        double K;

    public:
        CMYKColor():C(0.0),M(0.0),Y(0.0),K(0.0){}
        CMYKColor(float c, float m, float y, float k):C(c),M(m),Y(y),K(k){}
        
        void setColor(float c, float m, float y, float k);
        //void setColor(float * array, size_t arraySize) override;
        pixel getColor() override;
        ~CMYKColor() override;
    };
}