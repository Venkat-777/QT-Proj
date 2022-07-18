#include "Rectangle.h" 
#include "Ellipse.h"

Ellipse::Ellipse(QPaintDevice* device, int id)
    : Shape(device, id, ShapeType::Ellipse), width { 0 }, length { 0 }, x { 0 }, y { 0 }
{
}

Ellipse::Ellipse(QPaintDevice* device, int id, int width, int length, QPen pen, QBrush brush, int x = 0, int y = 0)
    : Shape(device, id, ShapeType::Ellipse, pen, brush), width { width }, length { length }, x { x }, y { y }
{
}

Ellipse::~Ellipse() 
{
}

void Ellipse::draw(QPaintDevice* device)
{
    QPainter& painter = getQPainter();
    
    painter.begin(device);
    painter.setPen(getPen());
    painter.setBrush(getBrush());
    painter.drawEllipse(x, y, width, length);
    painter.end();
}

void Ellipse::move(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

double Ellipse::area(float a, float b)
{
   float Area;
   Area = 3.142 * a * b ;
    
   return Area;
}

double Ellipse::perimeter(double radius)
{
    return 2 * 3.14 * radius;
}

void Rectangle::setX(int x)
{
    this->x = x;
}

void Rectangle::setY(int y)
{
    this->y = y;
}

void Rectangle::setWidth(int width)
{
    this->width = width;
}

void Rectangle::setLength(int length)
{
    this->length = length;
}

int Rectangle::getX() const
{
    return x;
}
int Rectangle::getY() const
{
    return y;
}
int Rectangle::getWidth() const
{
    return width;
}
int Rectangle::getLength() const
{
    return length;
}
