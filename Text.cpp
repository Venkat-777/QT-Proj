#include "text.h"

Text::Text(int id)
    : Shape(id), width {0}, length{0}, x {0}, y{0}
{ }


Text::Text(int id, Vector<QPoint> points, int length, int width,
           QString text, QFont font, Qt::AlignmentFlag flag,QPen pen, QBrush brush) //(int id, ShapeType shape, QPen pen, QBrush brush)
    : Shape(id,Shape::ShapeType::Text,pen,brush),   width {width}, length {length}, x {points[0].x()}, y {points[0].y()},
      font {font}, text {text}, flag {flag}
{ }


Text::~Text()
{ }

void Text::draw(QPaintDevice * device, QPainter* painter)
{
    painter->begin(device);
    painter->setFont(font);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawText(x, y, width, length, flag, text);
    painter->end();
}

void Text::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

double Text::area()
{
    return -1;
}

double Text::perimeter()
{
    return -1;
}

void Text::setText(QString text)
{
    this->text = text;
}

void Text::setFont(QFont font)
{
    this->font = font;
}
void Text::setFlag(Qt::AlignmentFlag flag)
{
    this->flag = flag;
}
void Text::setLength(int length)
{
    this->length = length;
}
void Text::setWidth(int width)
{
    this->width = width;
}

void Text::setX(int x)
{
    this->x = x;
}

void Text::setY(int y)
{
    this->y = y;
}

QString& Text::getText()
{
    return text;
}
QFont& Text::getFont()
{
    return font;
}
int Text::getWidth()
{
    return width;
}
int Text::getLength()
{
    return length;
}
int Text::getX()
{
    return x;
}
int Text::getY()
{
    return y;
}

Qt::AlignmentFlag Text::getAlignment()
{
    return flag;
}
