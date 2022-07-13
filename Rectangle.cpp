#include "Rectangle.h" 

Rectangle::Rectangle(QPainterDevice* device, int id)
    : Shape(device, id, ShapeType::Rectangle), x{x}, y{y}, width {width}, length {length}
    {

    }
Rectangle::~Rectangle()
{
    
}
void Rectangle::draw(QPainterDevice * device)
{

    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawRect(x, y, width, length);
    painter->end();
}
void Rectangle::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Rectangle::area()
{
    return length * width;
}

void Rectangle::perimeter()
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

int Rectangle::getX()
{
    return x;
}
int Rectangle::getY()
{
    return y;
}
int Rectangle::getWidth()
{
    return width;
}
int Rectangle::getLength()
{
    return length;
}
