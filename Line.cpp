#include "Line.h"


Line::Line(QPaintDevice* device, int id): Shape(device,id,ShapeType::Line)
{
    point1.setX(0);
    point1.setY(0);

    point2.setX(0);
    point2.setY(0);
}
Line::Line(QPaintDevice* device,int id,QPen pen, QBrush brush, int x1,int x2,int y1,int y2): 
      Shape(device, id, ShapeType::Line, pen, brush)
{
    point1.setX(x1);
    point1.setY(y1);

    point2.setX(x2);
    point2.setY(y2);
}
Line::~Line()
{

}
void Line::draw(QPaintDevice* device)
{
    QPainter& painter = getQPainter();
    painter.begin(device);
    painter.setPen(getPen());
    painter.setBrush(getBrush());

    painter.drawLine(point1.x(),point1.y(),point2.x(),point2.y());
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
double Line::getX1()
{
    return (point1.x());
}
double Line::getY1()
{
    return (point1.y());
}
double Line::getX2()
{
    return (point2.x());
}
double Line::getY2()
{
    return (point2.y());
}

//Sets
void Line::setX1(double x1)
{
    point1.setX(x1);
}
void Line::setY1(double y1)
{
    point1.setY(y1);    
}
void Line::setX2(double x2)
{
    point2.setX(x2);
}
void Line::setY2(double y2)
{
    point2.setY(y2);
}
