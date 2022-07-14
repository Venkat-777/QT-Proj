#include "text.h"

Text::Text(QPaintDevice * device, int id)
    : Shape(device, id, ShapeType::Text), width {0}, height{0}, x {0}, y{0}
{

}

Text::~Text()
{

}

void Text::draw(QPaintDevice * device)
{
    QPainter & painter = getQPainter();

    painter.begin(device);
    painter.setFont(font);
    painter.setPen(getPen());
    painter.setBrush(getBrush());
    painter.drawText(x, y, width, height, flag, text);
    painter.end();

}

void Text::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

double Text::area()
{
    return height;
}

double Text::perimeter()
{
    return width + width + height + height;
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
void Text::setHeight(int height)
{
    this->height = height;
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

QString Text::getText()
{
    return text;
}
QFont Text::getFont()
{
    return font;
}
int Text::getWidth()
{
    return width;
}
int Text::getHeight()
{
    return height;
}
int Text::getX()
{
    return x;
}

int Text::getY()
{
    return y;
}
