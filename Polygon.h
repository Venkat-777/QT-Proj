#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "vector.h"
#include <QPoint>

using namespace MC_Vec;

class Polygon : public Shape
{
private:
    int numOfPoints;
    Vector<QPoint> points;

public:
    Polygon(int id = -1);
    Polygon(int id, Vector<QPoint> points);
    Polygon(int id, QPen pen, QBrush brush, Vector<QPoint> points, int numOfpoints);
    ~Polygon() override;

    void draw(QPaintDevice* device, QPainter* painter) override;
    void move(const int x, const int y) override;
    double perimeter() override;
    double area() override;

    Vector<QPoint> getPointVector();

    int getNumPoints() const;
    int getX(int point) const;
    int getY(int point) const;

    void setX(int x, int coordNum);
    void setY(int y, int coordNum);
};

#endif
