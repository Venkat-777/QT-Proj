#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"
const int SIZE = 50;

class Polyline : public Shape
{
public:
    Polyline(QPaintDevice* device = nullptr, int id = -1);
    Polyline(QPaintDevice* device, int id, QPen pen, QBrush brush, QPointF* points, int pointCount);
    ~Polyline() override;
    
    void draw(QPaintDevice* device) override;
    void move(const int newX, const int newY) override;
    double perimeter() override;
    double area() override;
    
    void setNewCoords(int pointNum, int newX, int newY); 
    
    int getX(int pointNum) const;
    int getY(int pointNum) const;
    
private:
    int pointCount;
    QPointF points[SIZE];
};

#endif
