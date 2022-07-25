#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPoint>

#include "shape.h"
#include "vector.h"

using namespace MC_Vec;


class Rectangle : public Shape
{
public:
    Rectangle(int id = -1);

    Rectangle(int id,   int width,    int length,
              QPen pen, QBrush brush, int x = 0, int y = 0 );

    Rectangle(int id, Vector<QPoint> points, int length, int width);


    ~Rectangle() override;

    void draw(QPaintDevice* device, QPainter* painter) override;
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
};

#endif
