#include "Rectangle.h"

Rectangle::Rectangle(int id)
    : Shape(id), width { 0 }, length { 0 }, x { 0 }, y { 0 }
{ }

Rectangle::Rectangle(int id, int width, int length, QPen pen, QBrush brush, int x, int y)
    : Shape(id, ShapeType::Rectangle, pen, brush), width { width }, length { length }, x { x }, y { y }
{ }


Rectangle::Rectangle(int id, Vector<QPoint> points, int length, int width)
    : Shape(id), width { width }, length { length }, x { points[0].x() }, y { points[0].y() }
{  }


Rectangle::~Rectangle()
{
}

void Rectangle::draw(QPaintDevice* device, QPainter* painter)
{
    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawRect(x, y, width, length);
    painter->end();
}

void Rectangle::move(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

double Rectangle::area()
{
    return length * width;
}

double Rectangle::perimeter()
{
    return length + length + width + width;
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
