#include "Polyline.h"

Polyline::Polyline(int id )
  : Shape(id), pointCount { 0 }, points { } { }


Polyline::Polyline(int id, Vector<QPoint> points)
    : Shape(id), pointCount { pointCount }
{
    QPoint point;

    for (QPoint* ptr {points.begin()}; ptr != points.end(); ++ptr)
    {
        point.setX(ptr->x());
        point.setY(ptr->y());

        this->points.push_back(point);
    }
}


Polyline::~Polyline() { }


void Polyline::draw(QPaintDevice* device, QPainter* painter)
{
    QPoint qPoints[pointCount];

    for (int i {0}; i < pointCount; ++i)
        qPoints[i] = points[i];

    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());
    painter->drawPolyline(qPoints, pointCount);
    painter->end();
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
  return -1;
}


double Polyline::area()
{
  return -1;
}


int Polyline::getX(int pointNum) const
{
  return points[pointNum].x();
}

int Polyline::getY(int pointNum) const
{
  return points[pointNum].y();
}

Vector<QPoint> Polyline::getPointVector()
{
    return points;
}

void Polyline::setX(int value, int point)
{
    QPoint* qPoint { &points[point] };

    qPoint->setX(value);
}

void Polyline::setY(int value, int point)
{
    QPoint* qPoint { &points[point] };

    qPoint->setY(value);
}

void ShapeManager::drawId(int id, int x, int y){}
