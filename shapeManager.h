#ifndef SORTSHAPES_H
#define SORTSHAPES_H

#include <string>
#include "vector.h"
#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "polygon.h"
#include "line.h"
#include "text.h"

using namespace MC_Vec;
using std::string;

class ShapeManager
{
  public:
    ShapeManager(QPaintDevice* device);
    ShapeManager(const ShapeManager&) = delete;
    ShapeManager(ShapeManager&&)      = delete;
    ~ShapeManager();

    ShapeManager& operator=(const ShapeManager&) = delete;
    ShapeManager& operator=(ShapeManager&&)      = delete;

    Shape* getShape(int id) const;

    void addShape(Shape* shape);

    void removeShape(int id);

    void sortShapes(bool (*compare)(Shape*, Shape*));

    void drawShapes() const;

 //   void ReadShapeFile(const string fileName);

 //   void WriteShapeFile(const string fileName) const;


  private:
    Vector<Shape*> shapes;
    QPaintDevice*  device;
    QPainter*      painter;
};


#endif // SORTSHAPES_H
