#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <vector>

int const SIZE = 50;
class Polygon : public Shape
{
private:
    int numOfSides;
    QPointF points[SIZE];

public:
    Polygon(QPaintDevice* device = nullptr, int id = -1);
    Polygon(QPaintDevice* device,int id,QPen pen, QBrush brush, QPointF* points, int numOfSides );
    ~Polygon() override;
    
    void draw(QPaintDevice* device) override;
    void move(const int translateX, const int translateY) override;
    double perimeter() override;
    double area() override;

    void setX(int x,int coordNum);
    void setY(int y,int coordNum);

    void newCoords(int x, int y);

    int getX() const;
    int getY() const;

};


#endif
