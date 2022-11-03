#include "Figure.h"
#include "Bitmap.h"
#include <memory.h>

using namespace Object2D;



class Builder
{
private:
    Object2D::Bitmap* bitmap = nullptr;

public:
    Builder();
    ~Builder();
    //
    bool createFile(char* name, int width, int height, COLORS clr); 

    std::shared_ptr<Point> createPoint(int x_coord, int y_coord, ColorInterface* clr);
    std::shared_ptr<Line> createLine(int x1, int y1, int x2, int y2, ColorInterface* clr);
    std::shared_ptr<BezierBurve3> createBezierBurve3(Point2D p0, Point2D p1, Point2D p2, Point2D p3, int precision, ColorInterface * clr);
    std::shared_ptr<Ellipse> createEllipse(float x_, float y_, float rx_, float ry_, int numSegm, ColorInterface * clr);

    ContainerFigure2D createContainer();

    bool drawImage();
};