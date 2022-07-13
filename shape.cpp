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
void Shape::setShape(ShapeType shape)
{
    this->shape = shape;
}


/******************************************************************************
* Method setPen:  Class Shape                                                 *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the color of the shapes pen                                 *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      color (Qt::GlobalColor)  : The pens color                              *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS: The pens color will be set to the value of the argument    *
*******************************************************************************/
void Shape::setPen(Qt::GlobalColor color)
{
    pen.setColor(color);
}


/******************************************************************************
* Method setPen:  Class Shape                                                 *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the pens color, style, cap-style, join-style and width      *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
*                                                                             *
*      color     (Qt::GlobalColor)   : The color of the pen                   *
*      style     (Qt::PenStyle )     : The style of the pen                   *
*      capStyle  (Qt::PenCapStyle)   : The style of the pen cap               *
*      joinStyle (Qt::PenJointStyle) : The style of the pens join             *
*                                                                             *
*   Options:                                                                  *
*    PenStyle     - SolidLine, DashLine, DotLine, DashDotLine, DashDotDotLine *
*    PenCapStyle  - SquareCap, FlatCap, RoundCap                              *
*    PenJoinStyle - BevelJoin, MilterJoin, RoundJoin                          *
* ----------------------------------------------------------------------------*
*  POST-CONDITIONS:                                                           *
*    The shapes pen will be set with the values of all the arguments provided *
*******************************************************************************/
void Shape::setPen(Qt::GlobalColor  color,
                   Qt::PenStyle     penStyle,
                   Qt::PenCapStyle  capStyle,
                   Qt::PenJoinStyle joinStyle,
                   qreal            width)
{
    pen.setColor(color);
    pen.setStyle(penStyle);
    pen.setCapStyle(capStyle);
    pen.setJoinStyle(joinStyle);
    pen.setWidthF(width);
}


/******************************************************************************
* Method setBrush:  Class Shape                                               *
* ----------------------------------------------------------------------------*
*  Mutator;  Sets the brush's color & style                                   *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:  The fallowing arguments need a defined value              *
*                                                                             *
*      color     (Qt::GlobalColor)  : The color of the brush                  *
*      style     (Qt::BrushStyle )  : The style of the brush                  *
*                                                                             *
*   Options:                                                                  *
*    BrushStyle - SolidPattern,   Dense(1-7)Pattern, HorPattern,   VerPattern,*
*                 CrossPattern,   BDiagPattern,      FDiagPattern, NoBrush    *
*                 TexturePattern, DiagCrossPattern,  LinearGradientPattern,   *
*                 RadialGradientPattern, ConicalGradientPattern,              *
* ----------------------------------------------------------------------------*
*  POST-CONDITIONS:                                                           *
*    The brush's color and style will be set with the arugments provided      *
*******************************************************************************/
void Shape::setBrush(Qt::GlobalColor color, Qt::BrushStyle style)
{
    brush.setColor(color);
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


/******************************************************************************
* Method drawRect:  Class Shape                                               *
* ----------------------------------------------------------------------------*
*  Uses the shapes pen & brush to draw a rectangle                            *
* ----------------------------------------------------------------------------*
*  PRE-CONDITIONS:                                                            *
*     The following parameters needs a defined argument                       *
*       width  (int) : the width of the rectangle                             *
*       height (int) : the height of the rectangle                            *
*                                                                             *
*     The following parameters are optional                                   *
*       x (int) : x-coordinate of the upper-left corner                       *
*       y (int) : y-coordinate of the upper-left corner                       *
* ----------------------------------------------------------------------------*
* POST-CONDITIONS:  No data members will be modified                          *
*                   Draws a rectangle of the given width & height             *
*******************************************************************************/
void Shape::drawRect(int width, int height, int x, int y)
{
    painter->drawRect(x, y, width, height);
}
