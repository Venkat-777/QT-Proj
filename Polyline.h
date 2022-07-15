#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"
const int SIZE = 50;

class Polyline : public Shape
{
public:
    Polyline(QPaintDevice* device = nullptr, int id = -1);
    ~Polyline() override;
    
    void draw(QPaintDevice* device) override;
    //void move(int x, int y) override;
    
private:
    int pointCount;
    QPointF points[SIZE];
};

#endif
