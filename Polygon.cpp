#include "Polygon.h"

Polygon::Polygon(QPaintDevice* device, int id) : Shape(device, id, ShapeType::Polygon), numOfSides{0}
{
    for (int i = 0; i < SIZE; i++)
    {
        points[i].setX(0);
        points[i].setY(0);
    }
}
Polygon::Polygon(QPaintDevice* device,int id,QPen pen, QBrush brush, QPointF* points,int numOfSides ) :
         Shape{device, id, ShapeType::Polygon, pen, brush}
{
    this->numOfSides = numOfSides;
    for (int i = 0; i < numOfSides; i++)
    {
        this->points->setX(points->x());
        this->points->setY(points->y());
    }
    

}
Polygon::~Polygon()
{

}
    
void Polygon::draw(QPaintDevice* device)
{
    QPainter& painter = getQPainter();
    painter.begin(device);
    painter.setPen(getPen());
    painter.setBrush(getBrush());

    painter.drawPolygon(points, numOfSides);
}

void Polygon::move(const int translateX, const int translateY)
{
    for (int i = 0; i < numOfSides; i++)
    {
        //I need to translate each x,y value
        points[i].setX(points[i].x() + translateX);
        points[i].setY(points[i].y() + translateY);
    }
    

}
double Polygon::perimeter()
{
    return 0;
}
double Polygon::area()
{
    return 0;
}
void Polygon::newCoords(int x,int y)
{
    points[numOfSides] = QPointF(x,y);
    numOfSides++;
}
