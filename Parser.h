#ifndef PARSER_H_
#define PARSER_H_


// shape includes
#include "shape.h"
#include "line.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"
#include "ellipse.h"
#include "text.h"
#include "conversions.h"


// vector includes
#include "vector.h"
#include <memory>

// file includes
#include <iostream>
#include <string>
#include <fstream>

// deftypes
using std::shared_ptr;
using std::string;
using std::ifstream;
using std::ofstream;
using MC_Vec::Vector;



enum Output
{
    NONE,
    SHAPE_INFO,
    PEN_INFO,
    BRUSH_INFO,
    TEXT_INFO,
};

// class declaration
class Parser
{
  public:
  /*******************************************************************************
  * CONSTRUCTORS & DESTRUCTORS                                                   *
  *******************************************************************************/
    /*****************************************************************************
    *  Constructor:  Class Parser                                                *
    *----------------------------------------------------------------------------*
    *  This constructor will create an instance of Class Type Parser.            *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   none                                                                     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   The constructor will initialize its Shape & Vector to empty.             *
    *****************************************************************************/
    Parser();

    /*****************************************************************************
    *  Destructor:  Class Parser                                                 *
    *----------------------------------------------------------------------------*
    *  This destructor will delete an instance of Class Type Parser.             *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   none                                                                     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This destructor will delete an instance of Class Type Parser.            *
    *****************************************************************************/
    ~Parser();

  /*******************************************************************************
  * MUTATORS                                                                     *
  *******************************************************************************/
    /*****************************************************************************
    *  Method ReadShapeFile:  Class Parser                                       *
    *----------------------------------------------------------------------------*
    *  This method will read a file and store its contents into the Shape Vector.*
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName  -  the name of the file that contains the Shape contents *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will modify the Shape & Vector to contain the contents of    *
    *   the file provided.                                                       *
    *****************************************************************************/
    void ReadShapeFile(const string fileName);

    /*****************************************************************************
    *  Method ReadShapeFile:  Class Parser                                       *
    *----------------------------------------------------------------------------*
    *  This method will read a file and store its contents into the Shape Vector.*
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName  -  the name of the file that contains the Shape contents *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will modify the Shape & Vector to contain the contents of    *
    *   the file provided.                                                       *
    *****************************************************************************/
    void SaveFile();



  /*******************************************************************************
  * ACCESSORS                                                                    *
  *******************************************************************************/
    /*****************************************************************************
    *  Method getShapeVector:  Class Parser                                      *
    *----------------------------------------------------------------------------*
    *   xxxxxxxx.                                                                *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   read file must be performed first.                                       *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   returns the shape vector.                                                *
    *****************************************************************************/
    MC_Vec::Vector<Shape*> getShapeVector() const;

protected:
    int StringToEnum(const string& type);
    string EnumToString(const int& enumTypeValue, const int& enumListValue);





  private:
  /*******************************************************************************
  * variables                                                                    *
  *******************************************************************************/
    Shape* currentShape;                  // PROC & PROC - current Shape being read

    MC_Vec::Vector<Shape*> shapeVector;  // PROC & PROC - a vector containing Shape properties




    void OutputToFile(ofstream& fileName, Shape* shape, const Output& a = NONE, const Output& b = NONE, const Output& c = NONE, const Output& d = NONE);

    void ReadDelimiter(ifstream& fileName, char delimiter);

    void ReadPolyline(ifstream& fileName, Vector<QPoint>& definePoints, QPen& shapePen);

    void ReadPolygon(ifstream& fileName, Vector<QPoint>& definePoints, QPen& shapePen, QBrush& shapeBrush);

    void ReadRectangle(ifstream& fileName, Vector<QPoint>& definePoints, int& defineLength, int& defineWidth, QPen& shapePen, QBrush& shapeBrush);

    void ReadEllipse(ifstream& fileName, Vector<QPoint>& definePoints, int& minor, int& major, QPen& shapePen, QBrush& shapeBrush);

    void ReadText(ifstream& fileName, Vector<QPoint>& definePoints, int& defineLength, int& defineWidth,
                  QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag, Qt::GlobalColor& textColor);

    void ReadPenProperties(ifstream& fileName, QPen& shapePen);

    void ReadBrushProperties(ifstream& fileName, QBrush& shapeBrush);

    void ReadTextProperties(ifstream& fileName, QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag, Qt::GlobalColor& textColor);

    Vector<int> ReadDimensions(ifstream& fileName);



};

#endif
