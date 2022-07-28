#include "line.h"


Line::Line(int id): Shape(id)
{
    point1.setX(0);
    point1.setY(0);

    point2.setX(0);
    point2.setY(0);
}

Line::Line(int id, QPen pen, QBrush brush, int x1, int x2, int y1, int y2):
    Shape(id, Shape::ShapeType::Line, pen, brush), point1(x1, y1), point2(x2, y2)
{ }

Line::Line(int id, Vector<QPoint> points)
    : Shape(id), point1 (points[0].x(), points[0].y()), point2 (points[1].x(), points[1].y())
{ }

Line::~Line()
{ }

void Line::draw(QPaintDevice* device, QPainter* painter)
{
    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawLine(point1.x(),point1.y(),point2.x(),point2.y());
    painter->end();
}

void Line::move(const int translateX, const int translateY)
{
    point1.setX(point1.x() + translateX);
    point1.setY(point1.y() + translateY);
    point2.setX(point2.x() + translateX);
    point2.setY(point2.y() + translateY);
}

double Line::perimeter()
{
    //Declaring variables
    int perimeter = 0;

    //perimeter root of ->( (x2-x1)^2 + (y2-y1)^2 )
    perimeter = (pow(point2.x()-point1.x(),2) + pow(point2.y()-point1.y(),2));
    perimeter = sqrt(perimeter);

    return perimeter;
}

double Line::area()
{
    return 0;
}


//Gets
int Line::getX1()
{
    return (point1.x());
}
int Line::getY1()
{
    return (point1.y());
}
int Line::getX2()
{
    return (point2.x());
}
int Line::getY2()
{
    return (point2.y());
}


// Sets
void Line::setX(int value, int point)
{
    if (point == 1)
        point1.setX(value);
    else
        point2.setX(value);
}

void Line::setY(int value, int point)
{
    if (point == 1)
        point1.setY(value);
    else
        point2.setY(value);
}
