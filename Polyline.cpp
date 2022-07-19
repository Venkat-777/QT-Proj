#include "Polyline.h"

Polyline::Polyline(QPaintDevice* device = nullptr, int id = -1)
  : Shape(device, id, ShapeType::Polyline), pointCount{0}
{ 
  for (int k = 0; k < SIZE; k++)
  {
    points[k].setX(0);
    points[k].setY(0);
  }
}

Polyline::Polyline(QPaintDevice* device, int id, QPen pen, QBrush brush, QPointF* points, int pointCount)
    : Shape{device, id, ShapeType::Polyline, pen, brush}
{
    this->pointCount = pointCount;
    for (int j = 0; j < pointCount; j++)
    {
        this->points[j].setX(points[j].x());
        this->points[j].setY(points[j].y());
    }
}

Polyline::~Polyline() {}

void Polyline::draw(QPaintDevice* device)
{    
    QPainter& painter = getQPainter();
  
    painter.begin(device);
    painter.setPen(getPen());
    painter.setBrush(getBrush());
    painter.drawPolyline(points, pointCount);
    painter.end();
}

void Polyline::move(const int newX, const int newY)
{
    for (int k = 0; k < pointCount; k++)
    {
        points[k].setX(points[k].x() + newX);
        points[k].setY(points[k].y() + newY);
    }
}

double Polyline::perimeter()
{
  return 0;
}

double Polyline::area()
{
  return 0;
}

void setNewCoords(int pointNum, int newX, int newY)
{
   points[pointNum] = QPointF(newX, newY);
}

int Polyline::getX(int pointNum) const
{
  return points[pointNum].x();
}

int Polyline::getY(int pointNum) const
{
  return points[pointNum].y();
}
