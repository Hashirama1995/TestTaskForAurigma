#include "Figure.h"

using namespace Object2D;
/*************_Container_**************/ 

ContainerFigure2D::ContainerFigure2D()
{

}
ContainerFigure2D::~ContainerFigure2D()
{
    std::cout<<"delete container"<<std::endl;
    /*
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->~Figure2D();
    }
    std::cout<<"Delete container"<<std::endl;*/
}

Figure2D* ContainerFigure2D::add(Figure2D* item)
{
    container.push_back(item);
    return item;
}

Figure2D* ContainerFigure2D::add(std::shared_ptr<Figure2D> item)
{
    return add(item.get());
}

void ContainerFigure2D::rasterization()
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->rasterization();
    }
}

void ContainerFigure2D::getEdges(int& x_min, int& y_min, int& x_max, int& y_max)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->getEdges(x_min, y_min, x_max, y_max);
    }
}


void ContainerFigure2D::shift(float dx, float dy)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->shift(dx, dy);
    }
}

void ContainerFigure2D::zoom(float Sx, float Sy)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->zoom(Sx, Sy);
    }
}

void ContainerFigure2D::rotate(float Fi)
{
    for (std::list<Figure2D*>::iterator first = container.begin(); first != container.end(); ++first)
    {
        (*first)->rotate(Fi);
    }
}