#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include "vector.h"
#include <QPoint>

using namespace MC_Vec;


class Ellipse : public Shape
{
public:

    Ellipse(int id = -1);
    Ellipse(int id, Vector<QPoint> points, int width, int length);
    Ellipse(int id, int x, int y, int width, int length, QPen pen, QBrush brush);
    ~Ellipse() override;

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
    int x;
    int y;
    int width;
    int length;
};


#endif
