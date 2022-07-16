
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include "Rectangle.h"

class Ellipse : public Shape
{
public:
    Ellipse(QPaintDevice* device = nullptr, int id = -1);
    Ellipse(QPaintDevice* device, int id, int width, int length, QPen pen, QBrush brush, int x = 0, int y = 0);
    ~Ellipse() override;

    void draw(QPaintDevice* device) override;
    void move(const int x, const int y) override;
    double area() override;
    double perimeter() override;

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setLength(int length);

    int getX() const;
    int getY() const;

    int getWidth() const;
    int getLength() const;

private:
    int width, length, x , y;
    QRectF rectangle;
};
