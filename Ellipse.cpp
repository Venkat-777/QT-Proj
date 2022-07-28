
#include "Ellipse.h"
#include <cmath>


Ellipse::Ellipse(int id)
    : Shape(id), x { 0 }, y { 0 }, width { 0 }, length { 0 }
{ }

Ellipse::Ellipse(int id, Vector<QPoint> points, int width, int length)
    : Shape(id), x { points[0].x() }, y { points[0].y() }, width { width }, length { length }
{ }

Ellipse::Ellipse(int id, int x, int y, int width, int length, QPen pen, QBrush brush)
    : Shape(id, Shape::ShapeType::Ellipse, pen, brush), x {x}, y {y}, width {width}, length {length} {}


Ellipse::~Ellipse() {}


void Ellipse::draw(QPaintDevice* device, QPainter* painter)
{
    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawEllipse(x, y, width, length);
    painter->end();
}

void Ellipse::move(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

double Ellipse::area()
{

   return 3.142 * width * length;
}

double Ellipse::perimeter()
{
    return 2 * 3.142 * sqrt(((width * width) + (length * length) / 2));
}

void Ellipse::setX(int x)
{
    this->x = x;
}

void Ellipse::setY(int y)
{
    this->y = y;
}

void Ellipse::setWidth(int width)
{
    this->width = width;
}

void Ellipse::setLength(int length)
{
    this->length = length;
}

int Ellipse::getX() const
{
    return x;
}

int Ellipse::getY() const
{
    return y;
}

int Ellipse::getWidth() const
{
    return width;
}

int Ellipse::getLength() const
{
    return length;
}
