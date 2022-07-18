#include "Polygon.h"

Polygon::Polygon(QPaintDevice* device, int id) : Shape(device, id, ShapeType::Polygon), numOfPoints{0}
{}
Polygon::Polygon(QPaintDevice* device,int id,QPen pen, QBrush brush, QPointF* points,int numOfPoints ) :
         Shape{device, id, ShapeType::Polygon, pen, brush}
{
    this->numOfPoints = numOfPoints;
    for (int i = 0; i < numOfPoints; i++)
    {
        this->points[i].setX(points[i].x());
        this->points[i].setY(points[i].y());
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

    //Copying contents of vector to an array
    QPointF pointsArray[numOfPoints];
    for (int i = 0; i< numOfPoints; i++)
    {
        pointsArray[i].setX(points[i].x());
        pointsArray[i].setY(points[i].y());
    }

    painter.drawPolygon( pointsArray, numOfPoints);
}

void Polygon::move(const int translateX, const int translateY)
{
    for (int i = 0; i < numOfPoints; i++)
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
    points[numOfPoints] = QPointF(x,y);
    numOfPoints++;
}
