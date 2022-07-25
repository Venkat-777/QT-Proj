#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"
#include "vector.h"
#include <QPoint>

using namespace MC_Vec;

class Polyline : public Shape
{
public:
    Polyline(int id = -1);
    Polyline(int id, Vector<QPoint> points);
    ~Polyline() override;

    void draw(QPaintDevice* device, QPainter* painter) override;
    void move(const int newX, const int newY) override;
    double perimeter() override;
    double area() override;

    int getX(int pointNum) const;
    int getY(int pointNum) const;
    Vector<QPoint> getPointVector();

    void setX(int value, int point);
    void setY(int value, int point);

private:
    int pointCount;
    Vector<QPoint> points;
};

#endif
