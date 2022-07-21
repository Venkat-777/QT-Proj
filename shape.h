#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

class Shape
{
  public:
    enum class ShapeType { None, Line, Polyline, Polygon, Rectangle, Ellipse, Text, Circle, Square };

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
    *     device (QPaintDivice) : The widget to do the painting on               *
    *     id     (int)          : The shapes id                                  *
    *     shape  (ShapeType)    : The type of shape                              *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:                                                           *
    *     If arguments are provided, the shape will have instatiated a QPainter, *
    *     an shape-id and shape-type will have been set.                         *
    ******************************************************************************/
    Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::None);


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
    Shape(QPaintDevice* device, int id, ShapeType shape, QPen pen, QBrush brush);


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
    Shape(Shape&& rhs) noexcept;


    /*****************************************************************************
    * Desturctor:  Class Shape                                                   *
    * ---------------------------------------------------------------------------*
    *   Frees all resources associated with the Shape object                     *
    * ---------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                   *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:  The object and all all resources are destroyed           *
    ******************************************************************************/
    virtual ~Shape();


    /* Disabled Copy Constructor */
    Shape(const Shape&) = delete;

    /* Disabled Copy Assignment  */
    const Shape& operator=(const Shape& rhs) = delete;


    /*****************************************************************************
    * Method getShape:  Class Shape                                              *
    * ---------------------------------------------------------------------------*
    *  Accessor;  Gets and returns the type of shape                             *
    * ---------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                   *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:  Nothing will be modified.                                *
    *                                                                            *
    *   RETURNS: The type of shape.                                              *
    ******************************************************************************/
    ShapeType getShape() const { return shape; }


    /*****************************************************************************
    * Method getID:  Class Shape                                                 *
    * ---------------------------------------------------------------------------*
    *  Accessor;  Gets and returns the id of the shape                           *
    * ---------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                   *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:  Nothing will be modified.                                *
    *         RETURNS:  The shapes id                                            *
    ******************************************************************************/
    int getID() const { return id; }


    /*****************************************************************************
    * Method getPen:  Class Shape                                                *
    * ---------------------------------------------------------------------------*
    *  Accessor;  Gets and returns a reference to the shapes pen object          *
    * ---------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                   *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:  Nothing will be modified.                                *
    *                                                                            *
    *   RETURNS: A reference to the shapes pen object.                           *
    ******************************************************************************/
    const QPen& getPen() const { return pen; }


    /*****************************************************************************
    * Method getBrush:  Class Shape                                              *
    * ---------------------------------------------------------------------------*
    *  Accessor;  Gets and returns a reference to the shapes brush object        *
    * ---------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                   *
    * ---------------------------------------------------------------------------*
    * POST-CONDITIONS:  Nothing will be modified.                                *
    *                                                                            *
    *   RETURNS: A reference to the shapes brush object.                         *
    ******************************************************************************/
    const QBrush& getBrush() const { return brush; }


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
    void setShape(const ShapeType shape);


    /******************************************************************************
    * Method setPen:  Class Shape                                                 *
    * ----------------------------------------------------------------------------*
    *  Mutator;  Sets the shapes pen                                              *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
    *                                                                             *
    *      pen (QPen&)  : A reference to a Qpen                                   *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS:                                                            *
    *    The pen will be set with the values of the pen provided as an argument   *
    *******************************************************************************/
    void setPen(const QPen& pen);


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
    void setBrush(const QBrush& brush);


    /******************************************************************************
    * Method setPenColor:  Class Shape                                            *
    * ----------------------------------------------------------------------------*
    *  Mutator;  Sets the pens color                                              *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
    *                                                                             *
    *      color (QColor)  : The color to set the pen to                          *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS: The pens color will be set to the value of the argument    *
    *******************************************************************************/
    void setPenColor(QColor color);


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
    void setPenStyle(Qt::PenStyle style);


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
    void setPenCapStyle(Qt::PenCapStyle capStyle);


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
    void setPenJoinStyle(Qt::PenJoinStyle joinStyle);


    /******************************************************************************
    * Method setPenWidth:  Class Shape                                             *
    * ----------------------------------------------------------------------------*
    *  Mutator;  Sets the pens width                                              *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  The fallowing argument needs a defined value              *
    *                                                                             *
    *      width (qreal)  : The pens width                                        *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS: The pens width will be set to value of the argument        *
    *******************************************************************************/
    void setPenWidth(qreal width);


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
    void setBrushColor(QColor color);


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
    void setBrushStyle(Qt::BrushStyle);


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
    void defaultStyle();


    /******************************************************************************
    * Overloaded operator == :  Class Shape                                       *
    * ----------------------------------------------------------------------------*
    *  Compares the id of two shapes                                              *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  A shape must be on both sides of the operator             *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS:  No data members will be modified                          *
    *         RETURNS:  True/False wither the id of the two shape are equal       *
    *******************************************************************************/
    inline bool operator==(const Shape& rhs) const { return this->id == rhs.id; }


    /******************************************************************************
    * Overloaded operator < :  Class Shape                                        *
    * ----------------------------------------------------------------------------*
    *  Compares wither the id of one shape is less then the id of another shape   *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  A shape must be on both sides of the operator             *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS:  No data members will be modified                          *
    *         RETURNS:  True/False wither the id of the shape on the left is less *
    *                   then the id of the shape on the right side of operator    *
    *******************************************************************************/
    inline bool operator<(const Shape& rhs) const { return this->id < rhs.id; }


    /*** Pure Virtual Methods - To be defined by inherited classes  ***/

    virtual void draw(QPaintDevice* device) = 0;
    virtual void move(const int translateX, const int translateY) = 0;
    virtual double  perimeter() = 0;
    virtual double  area()      = 0;
    /*----------------------------------------------------------------*/


  protected:
    /******************************************************************************
    * Method getQPainter:  Class Shape                                            *
    * ----------------------------------------------------------------------------*
    *  Accessor;  Gets and returns a reference to the shapes Qpainter             *
    * ----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:  <none>                                                    *
    * ----------------------------------------------------------------------------*
    * POST-CONDITIONS: Nothing will be modified                                   *
    *         RETURNS: A reference to the QPainter                                *
    *******************************************************************************/
    QPainter& getQPainter() { return *painter; }


  private:
    QPainter* painter;  // pointer to a QPainter object
    ShapeType shape;    // the type of shape
    int       id;       // the shapes id
    QPen      pen;      // pen for drawing the outline of the shape
    QBrush    brush;    // brush for filling in the shape
};


#endif // SHAPE_H
