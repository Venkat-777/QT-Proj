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


// vector includes
#include "vector.h"
#include <memory>

// file includes
#include <string>
#include <fstream>

// deftypes
using std::shared_ptr;
using std::string;
using std::ifstream;
using MC_Vec::Vector;


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

  /*******************************************************************************
  * ACCESSORS                                                                    *
  *******************************************************************************/
    /*****************************************************************************
    *  Method GetProperties:  Class Parser                                       *
    *----------------------------------------------------------------------------*
    *   xxxxxxxx.                                                                *
    *                                                                            *
    *----------------------------------------------------------------------------*
    *  PRE-CONDITIONS:                                                           *
    *   xxxxxxxx.                                                                *
    *----------------------------------------------------------------------------*
    *  POST-CONDITIONS:                                                          *
    *   xxxxxxxx.                                                                *
    *****************************************************************************/
    Shape GetProperties(const int& ID) const;


  private:
  /*******************************************************************************
  * variables                                                                    *
  *******************************************************************************/
    Shape* currentShape;                  // PROC & PROC - current Shape being read

    MC_Vec::Vector<Shape*> parserVector;  // PROC & PROC - a vector containing Shape properties

    Vector<int> shapeDimensions(ifstream& fileName);

};

#endif
