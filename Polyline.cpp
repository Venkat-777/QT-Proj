#include "Polyline.h"

Polyline::Polyline(QPaintDevice* device = nullptr, int id = -1)
  : Shape(device, id, ShapeType::Polyline) 
{ }

Polyline::~Polyline() {}

void Polyline::draw(QPaintDevice* device)
{    
    QPainter& painter = getQPainter();
  
    painter.begin(device);
    painter.setPen(getPen());
    painter.setBrush(getBrush());
    // painter.drawRect(x, y, width, length);
    painter.end();
}

/*void Polyline::move(const int x, const int y)
{
    this->x = x;
    this->y = y;
} */
