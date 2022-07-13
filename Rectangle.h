#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(QPaintDevice* device = nullptr, int id = -1);
    ~Rectangle();

    void draw(QPaintDevice* device) override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setLength(int length);

    int getX();
    int getY();

    int getWidth();
    int getLength();

private:
    int width, length, x , y, id;

};