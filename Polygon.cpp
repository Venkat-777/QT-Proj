#include "Polygon.h"

Polygon::Polygon(int id) : Shape(id), numOfPoints {}, points {}
{}

Polygon::Polygon(int id, QPen pen, QBrush brush, Vector<QPoint> points, int numOfPoints ) :
    Shape(id, Shape::ShapeType::Polygon, pen, brush), numOfPoints { numOfPoints }
{
    QPoint point;

    for (int i = 0; i < numOfPoints; i++)
    {
        point.setX(points[i].x());
        point.setY(points[i].y());

        this->points.push_back(point);
    }
}

Polygon::Polygon(int id, Vector<QPoint> points)
    : Shape(id), numOfPoints { points.size() }
{
    QPoint point;

    for (QPoint* ptr {points.begin()}; ptr != points.end(); ++ptr)
    {
        point.setX(ptr->x());
        point.setY(ptr->y());

        this->points.push_back(point);
    }
}

Polygon::~Polygon()
{

}

void Polygon::draw(QPaintDevice* device, QPainter* painter)
{
    painter->begin(device);
    painter->setPen(getPen());
    painter->setBrush(getBrush());

    //Copying contents of vector to an array
    QPoint pointsArray[numOfPoints];

    for (int i = 0; i < numOfPoints; ++i)
    {
        pointsArray[i] = points[i];
    }

    painter->drawPolygon(pointsArray, numOfPoints);

    painter->end();
}

void Polygon::move(const int x, const int y)
{
    for (int i = 0; i < numOfPoints; i++)
    {
        points[i].setX(points[i].x() + x);
        points[i].setY(points[i].y() + y);
    }


}

double Polygon::perimeter()
{
    return -1;
}

double Polygon::area()
{
    return -1;
}

Vector<QPoint> Polygon::getPointVector()
{
    return points;
}

int Polygon::getX(int point) const
{
    return points[point].x();
}

int Polygon::getNumPoints() const
{
    return numOfPoints;
}

int Polygon::getY(int point) const
{
    return points[point].y();
}

void Polygon::setX(int x,int coordNum)
{
    QPoint* point { &points[coordNum] };

    point->setX(x);
}

void Polygon::setY(int y,int coordNum)
{
    QPoint* point { &points[coordNum] };

    point->setY(y);
}
