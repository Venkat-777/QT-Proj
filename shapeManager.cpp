#include "shapeManager.h"

ShapeManager::ShapeManager(QPaintDevice* device)
   : shapes {}, device { device }, painter { new QPainter } {}



ShapeManager::~ShapeManager()
{
    delete device;
    delete painter;

    for (Shape* shape : shapes)
    {
        delete shape;
    }
}



Shape* ShapeManager::getShape(int id) const
{
    for (Shape* shape : shapes)
    {
        if (shape->getID() == id)
        {
            return shape;
        }
    }

    return nullptr;
}



void ShapeManager::addShape(Shape* shape)
{
    shapes.push_back(shape);
}



void ShapeManager::removeShape(int id)
{
    Shape** sp   { shapes.begin() };
    Shape* shape { nullptr };

    while (sp != shapes.end())
    {
        shape = *sp;

        if (shape->getID() == id)
        {
            shapes.erase(sp);
        }

        ++sp;
    }
}



void ShapeManager::drawShapes() const
{
    for (Shape* shape : shapes)
    {
        shape->draw(device);
    }
}



void ShapeManager::sortShapes(bool (*compare)(Shape*, Shape*))
{
    int smallestIndex;

    for (int i {0}; i < shapes.size(); ++i )
    {
      smallestIndex = i;

      for (int j {i + 1}; j < shapes.size(); ++j)
      {
          if (compare(shapes[j], shapes[i]))
          {
              smallestIndex = j;
          }
      }

      std::swap(shapes[i], shapes[smallestIndex]);
    }
}
