#include "shape.h"


/*****************************************************************************
* Constructor:  Class Shape                                                  *
* ---------------------------------------------------------------------------*
*   This constructor will set the id and type for the shape.                 *
*   Will also instatiate a QPainter object on the heap.                      *
*                                                                            *
*   Note: This is an abstract class, objects of shape cannot be created      *
* ---------------------------------------------------------------------------*
*  PRE-CONDITIONS:                                                           *
*   The following parameters can be optionally set with an argument          *
*                                                                            *
*     device (QPaintDivice) : The widget to do the paining on                *
*     id     (int)          : The shapes id                                  *
*     shape  (ShapeType)    : The type of shape                              *
* ---------------------------------------------------------------------------*
* POST-CONDITIONS:                                                           *
*     If arguments are provided, the shape will have instatiated a QPainter, *
*     an shape-id and shape-type will have been set.                         *
******************************************************************************/
Shape::Shape(QPaintDevice* device, int id, ShapeType shape)
    : painter { new QPainter(device) }, id { id }, shape { shape } {}


/*****************************************************************************
* Constructor:  Class Shape                                                  *
* ---------------------------------------------------------------------------*
*   This constructor will set the values for all data members                *
*                                                                            *
*   Note: This is an abstract class, objects of shape cannot be created      *
* ---------------------------------------------------------------------------*
*  PRE-CONDITIONS:                                                           *
*   The following parameters need a defined argument                         *
*                                                                            *
*     device (QPaintDivice) : The widget to do the paining on                *
*     id     (int)          : The shapes id                                  *
*     shape  (ShapeType)    : The type of shape                              *
*     pen    (QPen)         : The pen to draw the outline of the shape       *
*     brush  (QBrush)       : The brush to fill in the shape with            *
* ---------------------------------------------------------------------------*
* POST-CONDITIONS:                                                           *
*     If arguments are provided, the shape will have instatiated a QPainter, *
*     an shape-id and shape-type will have been set.                         *
******************************************************************************/
Shape::Shape(QPaintDevice* device, int id, ShapeType shape, QPen pen, QBrush brush)
    : painter { new QPainter(device) }, id { id }, shape { shape }, pen { pen }, brush { brush } {}



/*****************************************************************************
* Move Constructor:  Class Shape                                             *
* ---------------------------------------------------------------------------*
*   Moves the resources from the temp object to the new object               *
* ---------------------------------------------------------------------------*
*  PRE-CONDITIONS: A temp shape object is needed to move from                *
* ---------------------------------------------------------------------------*
* POST-CONDITIONS:                                                           *
*     The new object will point to the data of the temp object.              *
*     The temp object will point to null                                     *
******************************************************************************/
Shape::Shape(Shape&& rhs) noexcept
    : painter { std::move(rhs.painter) }, shape { std::move(rhs.shape) }, id { std::move(rhs.id) },
      pen { std::move(rhs.pen) },         brush { std::move(rhs.brush) }
{
    rhs.painter = nullptr;
}


/*****************************************************************************
* Desturctor:  Class Shape                                                   *
* ---------------------------------------------------------------------------*
*   Frees all resources associated with the Shape object                     *
* ---------------------------------------------------------------------------*
*  PRE-CONDITIONS:  <none>                                                   *
* ---------------------------------------------------------------------------*
* POST-CONDITIONS:  The object and all all resources are destroyed           *
******************************************************************************/
Shape::~Shape()
{
    delete painter;
}


/*****************************************************************************
* Method setShape:  Class Shape                                              *
* ---------------------------------------------------------------------------*
*  Mutator;  Sets the shapes type                                            *
* ---------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value             *
*                                                                            *
*      shape (ShapeType)  : The type of shape                                *
* ---------------------------------------------------------------------------*
* POST-CONDITIONS: The shapes type will be set to the value of the argument  *
******************************************************************************/
void Shape::setShape(const ShapeType shape)
{
    this->shape = shape;
}


/******************************************************************************
* Method setPen:  Class Shape                                                 *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the shapes pen                                              *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      pen (QPen&)  : A reference to a Qpen object                            *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS:                                                            *
*    The pen will be set with the values of thepen provided as an argument    *
*******************************************************************************/
void Shape::setPen(const QPen& pen)
{
    this->pen.setColor(pen.color());
    this->pen.setStyle(pen.style());
    this->pen.setCapStyle(pen.capStyle());
    this->pen.setJoinStyle(pen.joinStyle());
    this->pen.setWidthF(pen.widthF());
}


/******************************************************************************
* Method setBrush:  Class Shape                                               *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the brush's color & style                                   *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing arguments need a defined value              *
*                                                                             *
*    brush (QBrush&)  : A reference to a QBrush                               *
* ----------------------------------------------------------------------------*
*  POST-CONDITIONS:                                                           *
*    The brush will be set to the values of the brush passed as an argument   *
*******************************************************************************/
void Shape::setBrush(const QBrush& brush)
{
    this->brush.setColor(brush.color());
    this->brush.setStyle(brush.style());
}


/******************************************************************************
* Method setPenColor:  Class Shape                                            *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens color                                              *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      color (QColor)  : The color to set the pen to                          *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS:The pens color will be set to the value of the argument    *
*******************************************************************************/
void Shape::setPenColor(QColor color)
{
    pen.setColor(color);
}


/******************************************************************************
* Method setPenStyle:  Class Shape                                            *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens style                                              *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      style (Qt::PenStyle)  : The pens style                                 *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The pens style will be set to the value of the argument    *
*******************************************************************************/
void Shape::setPenStyle(Qt::PenStyle style)
{
    pen.setStyle(style);
}


/******************************************************************************
* Method setPenCapStyle:  Class Shape                                         *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens cap style                                          *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      capStyle (Qt::PenCapStyle)  : The style of the pen cap                 *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The pens cap style will be set to value of the argument    *
*******************************************************************************/
void Shape::setPenCapStyle(Qt::PenCapStyle capStyle)
{
    pen.setCapStyle(capStyle);
}


/******************************************************************************
* Method setPenJoinStyle:  Class Shape                                        *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens join style                                         *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      joinStyle (Qt::PenJoinStyle)  : The pens join style                    *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The pens join style will be set to value of the argument   *
*******************************************************************************/
void Shape::setPenJoinStyle(Qt::PenJoinStyle joinStyle)
{
    pen.setJoinStyle(joinStyle);
}


/******************************************************************************
* Method setPenWidth:  Class Shape                                            *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens width                                              *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      width (qreal)  : The pens width                                        *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The pens width will be set to value of the argument        *
*******************************************************************************/
void Shape::setPenWidth(qreal width)
{
    pen.setWidthF(width);
}


/******************************************************************************
* Method setBrushColor:  Class Shape                                          *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the brushes color                                           *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      color (QColor)  : The brushes color                                    *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The brush will be set to the color provided as an argument *
*******************************************************************************/
void Shape::setBrushColor(QColor color)
{
    brush.setColor(color);
}


/******************************************************************************
* Method setBrushStyle:  Class Shape                                          *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the brushes style                                           *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      style (Qt::BrushStyle)  : The brushes style                            *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The brush will be set to the style provided as an argument *
*******************************************************************************/
void Shape::setBrushStyle(Qt::BrushStyle style)
{
    brush.setStyle(style);
}


/******************************************************************************
* Method defaultStyle:  Class Shape                                           *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pen & brush to a default setting                        *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  <none>                                                    *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS:                                                            *
*   The pen & brush will be set to a default value - solid black              *
*******************************************************************************/
void Shape::defaultStyle()
{
     pen   = QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
     brush = QBrush(Qt::black,  Qt::SolidPattern);
}
