#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class Polyline : public Shape
{
public:
    Polyline(QPaintDevice* device = nullptr, int id = -1);
    ~Polyline();
    
    void draw(QPaintDevice* device) override;
    void move(int x, int y) override;
    
private:

};

#endif
