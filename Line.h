#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include <vector>
#include <cmath>

class Line : public Shape
{
private:
    QPointF point1;
    QPointF point2;
public:

    Line(QPaintDevice* device = nullptr, int id = -1);
    Line(QPaintDevice* device,int id,QPen pen, QBrush brush, int x1,int x2,int y1,int y2);
    ~Line();
    void draw(QPaintDevice* device) override;
    void move(const int translateX, const int translateY) override;
    double perimeter() override;
    double area() override;

    //Gets
    double getX1();
    double getY1();
    double getX2();
    double getY2();

    //Sets
    void setX1(double x1);
    void setY1(double y1);
    void setX2(double x2);
    void setY2(double y2);
};


#endif
