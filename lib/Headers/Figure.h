#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include <utility>
#include <algorithm>

#include "Colors.h"
#include "Bitmap.h"

#define M_PI 3.14159265358979323846  /* pi */

namespace Object2D{


    struct Point2D{
        float x;
        float y;

        Point2D():x(0), y(0) {}
        Point2D(int xx, int yy):x(xx), y(yy) {}
    };

    /***********_Main interface_************/ 
    class Figure2D
    {
    public:
        virtual void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) = 0;
        virtual void rasterization() = 0;

        virtual ~Figure2D() {}

        virtual void shift(float dx, float dy) = 0;
        virtual void zoom(float Sx, float Sy) = 0;
        virtual void rotate(float Fi) = 0;
    };


    /*************_Container_**************/ 
    class ContainerFigure2D: public Figure2D
    { 
    private:
        int posX = 0;
        int posY = 0;
        std::list<Figure2D*> container;
        
    public:
        ContainerFigure2D();
        ~ContainerFigure2D() override;

        void rasterization() override;
        Figure2D* add(Figure2D* item);
        
        void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) override;

        void shift(float dx, float dy);
        void zoom(float Sx, float Sy);
        void rotate(float Fi);
    };





    /*********_2D Figure interface_*********/ 
    class FigureObject2D: public Figure2D
    {
    public: // pure virtual
        virtual void setColor(ColorInterface* color) = 0;
        virtual void rasterization() = 0;
        virtual void putPixel(int x, int y) = 0;

        virtual void shift(float dx, float dy) = 0;
        virtual void zoom(float Sx, float Sy) = 0;
        virtual void rotate(float Fi) = 0;

        virtual void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) = 0;
    
    public: // implemented
        FigureObject2D() {};
        virtual ~FigureObject2D() {}
        virtual void matrixMultiply(int& x, int& y, const float matrix[3][3]);
        virtual void matrixMultiply(Point2D& point, const float matrix[3][3]);
        virtual void calculateBresenthemCoords(int x1, int y1, int x2, int y2);

        virtual void validatePoint(float& x, float& y, const unsigned int sizeX, const unsigned int sizeY);
        virtual void validatePoint(int& x, int& y, const unsigned int sizeX, const unsigned int sizeY);
        virtual void validateToShift(float& dx, float& dy ,int x, int y, const unsigned int sizeX, const unsigned int sizeY);
    };



    /*********_Implementation Point_*********/
    class Point: public FigureObject2D
    {
    private:
        Bitmap& picture;
        ColorInterface* color = nullptr;
        int posX = 0;
        int posY = 0;
    
    private:
        void putPixel(int x, int y) override;
        
    public:
        Point(Bitmap& pic, int x, int y, ColorInterface* clr);
        ~Point() override;

        void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) override;
        void setColor(ColorInterface* color) override;
        void rasterization() override;
        
        void shift(float dx, float dy) override;

        void zoom(float Sx, float Sy) override; // not implemented
        void rotate(float Fi) override;         // not implemented
    };


    /*********_Implementation Line_*********/
    class Line: public FigureObject2D
    {
    private:
        Bitmap& picture;
        ColorInterface* color = nullptr;
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;

    private:
        void affineMatrixMultiply(float matrix_[3][3]);
        void putPixel(int x, int y) override;

    public:
        Line(Bitmap& pic, int x1, int y1, int x2, int y2, ColorInterface* clr);
        Line(Bitmap& pic, Point2D p0, Point2D p1, ColorInterface* clr);
        ~Line() override;

        void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) override;
        void setColor(ColorInterface* color) override;
        void rasterization() override;

        void shift(float dx, float dy) override;
        void zoom(float Sx, float Sy) override;
        void rotate(float Fi) override; // НЕ РАБОТАЕТ
    };

    

    

    class BezierBurve3: public FigureObject2D
    {
    private:
        Bitmap& picture;
        ColorInterface* color = nullptr;
        Point2D P0;
        Point2D P1;
        Point2D P2;
        Point2D P3;
        int precision = 1;
        
        int PointCoordsSize = 0;
        std::pair<int,int>* PointCoords = nullptr;

    private:
        void putPixel(int x, int y) override;
        Point2D calculatePoint(float step);
        //float findExtrmum();

    public:
        BezierBurve3(Bitmap& pic, Point2D p0, Point2D p1, Point2D p2, Point2D p3, int precision, ColorInterface * clr);
        void setColor(ColorInterface* color) override;
        void rasterization() override;
        
        void shift(float dx, float dy) override;
        void zoom(float Sx, float Sy) override;
        void rotate(float Fi) override;

        void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) override;
    };


    class Ellipse: public FigureObject2D
    {
    private:
        Bitmap& picture;
        ColorInterface* color = nullptr;
        int xCenter;
        int yCenter;
        float rx;
        float ry;
        int num_segments;
    
    private:
        void putPixel(int x, int y) override;

    public:
        Ellipse(Bitmap& pic, float x_, float y_, float rx_, float ry_, int numSegm, ColorInterface * clr);

        void setColor(ColorInterface* color) override;
        void rasterization() override;

        void shift(float dx, float dy) override;
        void zoom(float Sx, float Sy) override;
        void rotate(float Fi) override;

        void getEdges(int& x_min, int& y_min, int& x_max, int& y_max) override;
    };
}