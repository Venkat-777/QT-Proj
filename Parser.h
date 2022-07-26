#ifndef PARSER_H_
#define PARSER_H_


// enumeration conversion database
#include "conversions.h"

// shape includes
#include "shape.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "text.h"

// vector includes
#include "vector.h"

// pre-processor directives
#include <iostream>
#include <string>
#include <fstream>

// using namespaces
using std::shared_ptr;
using std::string;
using std::ifstream;
using std::ofstream;
using MC_Vec::Vector;



/*******************************************************************************
* ENUMERATED TYPES                                                             *
*******************************************************************************/
// DETERMINES WHICH INFO TO PRINT TO AN OUTPUT FILE
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
    * Constructor:  Class Parser                                                 *
    *----------------------------------------------------------------------------*
    * This constructor will create an instance of Class Type Parser.             *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   none                                                                     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   none                                                                     *
    *****************************************************************************/
    Parser();

    /*****************************************************************************
    * Destructor:   Class Parser                                                 *
    *----------------------------------------------------------------------------*
    * This destructor will delete an instance of Class Type Parser.              *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   none                                                                     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   none                                                                     *
    *****************************************************************************/
    ~Parser();

  /*******************************************************************************
  * MUTATORS                                                                     *
  *******************************************************************************/
    /*****************************************************************************
    * Method ReadShapeFile: Class Parser                                         *
    *----------------------------------------------------------------------------*
    * This method will read a file and store its contents into the Shape Vector. *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName  -  the name of the file that contains the Shape contents *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will update the shape vector to the contents of the file     *
    *   provided.                                                                *
    *****************************************************************************/
    void ReadShapeFile(const string fileName);

    /*****************************************************************************
    * Method SaveFile:  Class Parser                                             *
    *----------------------------------------------------------------------------*
    * This method will read the existing vector of shapes and store it in an     *
    * output file.                                                               *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName  -  the name of the file that will be saved to            *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will create an output file.                                  *
    *****************************************************************************/
    void SaveFile(const string& fileName);


  /*******************************************************************************
  * ACCESSORS                                                                    *
  *******************************************************************************/
    /*****************************************************************************
    * Method getShapeVector: Class Parser                                        *
    *----------------------------------------------------------------------------*
    * This method will get the shape vector.                                     *
    *                                                                            *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   This method does not require any defined parameters.                     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   Returns the shape vector.                                                *
    *****************************************************************************/
    MC_Vec::Vector<Shape*> getShapeVector() const;


  private:
  /*******************************************************************************
  * variables                                                                    *
  *******************************************************************************/
    Shape* currentShape;                // PROC & PROC - a single shape
    MC_Vec::Vector<Shape*> shapeVector; // PROC & PROC - a vector containing all
                                        //               shapes read from input file

    /*******************************************************************************
    * helper methods                                                               *
    *******************************************************************************/
    /*****************************************************************************
    * Method ReadDelimiter:  Class Parser                                        *
    *----------------------------------------------------------------------------*
    * This method will ignore all characters up to and including the delimiter   *
    * specified in the file specified.                                           *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName  - an input file                                          *
    *         delimiter - desired character delimiter                            *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   Advances the file marker in the input file.                              *
    *****************************************************************************/
    void ReadDelimiter(ifstream& fileName, char delimiter);

    /*****************************************************************************
    * Method ReadDimensions:   Class Parser                                      *
    *----------------------------------------------------------------------------*
    * This method will determine the shape dimensions from an input file.        *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName      - an input file                                      *
    *         shapeType     - the type of shape                                  *
    *         definePoints  - a declared vector                                  *
    *         dimA          - a declared dimension                               *
    *         dimB          - a declared dimension                               *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will update the following parameters:                        *
    *          definePoints  -  updated to contain the dimension points          *
    *          dimA          -  updated to length/width/minor/major/radius dim   *
    *          dimB          -  updated to length/width/minor/major/radius dim   *
    *****************************************************************************/
    void ReadDimensions(ifstream& fileName, const Shape::ShapeType& shapeType, Vector<QPoint>& definePoints, int& dimA, int& dimB);

    /*****************************************************************************
    * Method ReadPenProperties: Class Parser                                     *
    *----------------------------------------------------------------------------*
    * This method will get the properties of the pen from an input file.         *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName      - the input file                                     *
    *         shapePen      - the shape's corresponding pen                      *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will update the following parameters:                        *
    *         shapePen -   the properties of the pen                             *
    *****************************************************************************/
    void ReadPenProperties(ifstream& fileName, QPen& shapePen);

    /*****************************************************************************
    * Method ReadBrushProperties:  Class Parser                                  *
    *----------------------------------------------------------------------------*
    * This method will get the properties of the brush from an input file.       *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName      - the input file                                     *
    *         shapeBrush    - the shape's corresponding brush                    *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will update the following parameters:                        *
    *         shapeBrush -   the properties of the brush                         *
    *****************************************************************************/
    void ReadBrushProperties(ifstream& fileName, QBrush& shapeBrush);

    /*****************************************************************************
    * Method ReadTextProperties:  Class Parser                                   *
    *----------------------------------------------------------------------------*
    * This method will get the properties of the text shape from an input file.  *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName      - the input file                                     *
    *         shapePen      - text's corresponding pen (used for color only)     *
    *         text          - the text's contents                                *
    *         textFont      - contains text font properties                      *
    *         textAlignFlag - alignment properties                               *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will update the following parameters:                        *
    *         shapePen      - the text color                                     *
    *         text          - the text's contents                                *
    *         textFont      - the text font properties                           *
    *         textAlignFlag - the text alignment properties                      *
    *****************************************************************************/
    void ReadTextProperties(ifstream& fileName, QPen& shapePen, QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag);

    /*****************************************************************************
    * Method OutputToFile:  Class Parser                                         *
    *----------------------------------------------------------------------------*
    * This method will write to the output file the requested information.       *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         fileName      -   the name of the file that will be saved to       *
    *         shape         -   the shape whose information is being printed     *
    *         a..b..c..d    -   the requested information to be printed          *
    *                           see enum Parser::Output                          *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will create an output file.                                  *
    *****************************************************************************/
    void OutputToFile(ofstream& fileName, Shape* shape, const Output& a = NONE, const Output& b = NONE, const Output& c = NONE, const Output& d = NONE);

    /*****************************************************************************
    *  Method QColorToString:  Class Parser                                      *
    *----------------------------------------------------------------------------*
    *  This method converts a QColor to string.                                  *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         qColor  -  the hexadecimal value of the QColor, in string form     *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method returns a string that corresponds to the QColor passed in.   *
    *****************************************************************************/
    string QColorToString(const string& qcolor);

    /*****************************************************************************
    * Method EnumToString:  Class Parser                                         *
    *----------------------------------------------------------------------------*
    * This method will translate an enum to a string.                            *
    *                                                                            *
    *   Example:                                                                 *
    * [translate] enumTypeValue : QFont::Weight::Thin                            *
    *      [from] enumListValue : convert::ListTypes::FONT_WEIGHT...             *
    *                                                                            *
    *       enumTypeValue & enumListValue must be related                        *
    *                                                                            *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   The following parameters require a defined value prior to calling the    *
    *   method:                                                                  *
    *         enumTypeValue  -  the desired enumeration to be translated         *
    *         enumListValue  -  enum ListTypes from 'convert::' namespace        *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   This method will return the corresponding string of the enumerated type  *
    *   provided.                                                                *
    *****************************************************************************/
    string EnumToString(const int& enumTypeValue, const int& enumListValue);
};

#endif
