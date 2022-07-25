#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "vector.h"
#include <cmath>

using namespace MC_Vec;

class Line : public Shape
{
private:
    QPoint point1;
    QPoint point2;

public:
    Line(int id = -1);
    Line(int id, QPen pen, QBrush brush, int x1,int x2,int y1,int y2);
    Line(int id, Vector<QPoint> points);
    ~Line();

    void draw(QPaintDevice* device, QPainter* painter) override;
    void move(const int x, const int y) override;
    double perimeter() override;
    double area() override;

    // Gets
    double getX1();
    double getY1();
    double getX2();
    double getY2();

    // Sets
    void setX(int value, int point);
    void setY(int value, int point);
};

#endif
