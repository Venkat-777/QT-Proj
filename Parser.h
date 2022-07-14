#ifndef PARSER_H_
#define PARSER_H_


// shape includes
#include "shape.h"
#include "Rectangle.h"

// vector includes
#include "vector.h"
#include <memory>
#include <string>
#include <fstream>

// deftypes
using std::shared_ptr;
using std::string;
using std::ifstream;


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
    std::unique_ptr<Shape> currentShape;                  // PROC & PROC - current Shape being read
    MC_Vec::Vector<shared_ptr<Shape>> parserVector;  // PROC & PROC - a vector containing Shape properties

};

#endif
