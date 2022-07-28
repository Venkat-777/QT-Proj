#include "shapeManager.h"

ShapeManager::ShapeManager(QPaintDevice* device)
   : device { device }, painter { new QPainter }, shapes{}, currentShape {nullptr} {}



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
    // Drawing the canvas
    painter->begin(device);
    painter->fillRect(10, 10, 1500, 880, Qt::white);
    painter->end();

    for (Shape* shape : shapes)
    {
        shape->draw(device, painter);
    }
}



void ShapeManager::sortShapes(bool (*compare)(Shape*, Shape*))
{
    int index;

    for (int i {0}; i < shapes.size(); ++i )
    {
      index = i;

      for (int j {i + 1}; j < shapes.size(); ++j)
      {
          if (compare(shapes[j], shapes[i]))
          {
              index = j;
          }
      }

      std::swap(shapes[i], shapes[index]);
    }
}


/*******************************************************
 * PARSER PARSER PARSER PARSER PARSER PARSER [begin]
 *******************************************************/
/*****************************************************************************
* Method ReadShapeFile: Class ShapeManager                                   *
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
void ShapeManager::ReadShapeFile(const string fileName)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    ifstream    inFile;              // PROC & PROC - input file stream variable
                                     //
    int     shapeID;                 // PROC & PROC - shape ID
    string  shapeType;               // PROC & PROC - shape type
                                     //
    QPen    shapePen;                // PROC & PROC - shape's pen
    QBrush  shapeBrush;              // PROC & PROC - shape's brush
                                     //
    QString           text;          // PROC & PROC - text contained in text shape
    QFont             textFont;      // PROC & PROC - text font for text shape
    Qt::AlignmentFlag textAlignFlag; // PROC & PROC - text alignment for text shape
    Qt::GlobalColor   textColor;     // PROC & PROC - text color for text shape
                                     //
    Vector<QPoint>  definePoints;    // PROC & PROC - a vector of points (x,y)
    int             defineLength;    // PROC & PROC - shape's length
    int             defineWidth;     // PROC & PROC - shape's width
    int             defineMinor;     // PROC & PROC - shape's minor axis
    int             defineMajor;     // PROC & PROC - shape's major axis
    int             defineRadius;    // PROC & PROC - shape's radius



    // open file
    inFile.open(fileName);

    // read the file
    while(inFile)
    {
        // SHAPE ID
        // remove "ShapeID: "
        ReadDelimiter(inFile, ':');

        // get shape id
        inFile >> shapeID;
        inFile.ignore(1000, '\n');



        // SHAPE TYPE
        // remove "ShapeType: "
        ReadDelimiter(inFile, ':');

        // get shape type
        getline(inFile, shapeType);



        // CREATE SHAPES
        if(shapeType == "Line")
        {
          // defineLength and defineWidth = 0
          ReadDimensions(inFile, Shape::ShapeType::Line, definePoints, defineLength, defineWidth);
          ReadPenProperties(inFile, shapePen);

          currentShape = new Line(shapeID, definePoints);
          currentShape -> setShape(Shape::ShapeType::Line);
          currentShape -> setPen(shapePen);
        }
        else if(shapeType == "Polyline")
        {
          // defineLength and defineWidth = 0
          ReadDimensions(inFile, Shape::ShapeType::Polyline, definePoints, defineLength, defineWidth);
          ReadPenProperties(inFile, shapePen);

          currentShape = new Polyline(shapeID, definePoints, QPen(), QBrush());
          currentShape -> setShape(Shape::ShapeType::Polyline);
          currentShape -> setPen(shapePen);

        }
        else if(shapeType == "Polygon")
        {
          // defineLength and defineWidth = 0
          ReadDimensions(inFile, Shape::ShapeType::Polygon, definePoints, defineLength, defineWidth);
          ReadPenProperties(inFile, shapePen);
          ReadBrushProperties(inFile, shapeBrush);

          currentShape = new Polygon(shapeID, definePoints);
          currentShape -> setShape(Shape::ShapeType::Polygon);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }

        else if(shapeType == "Rectangle")
        {
          ReadDimensions(inFile, Shape::ShapeType::Rectangle, definePoints, defineLength, defineWidth);
          ReadPenProperties(inFile, shapePen);
          ReadBrushProperties(inFile, shapeBrush);

          currentShape = new Rectangle(shapeID, definePoints, defineLength, defineWidth);
          currentShape -> setShape(Shape::ShapeType::Rectangle);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(shapeType == "Square")
        {
            ReadDimensions(inFile, Shape::ShapeType::Square, definePoints, defineLength, defineWidth);
            ReadPenProperties(inFile, shapePen);
            ReadBrushProperties(inFile, shapeBrush);

            currentShape = new Rectangle(shapeID, definePoints, defineLength, defineLength);
            currentShape -> setShape(Shape::ShapeType::Square);
            currentShape -> setPen(shapePen);
            currentShape -> setBrush(shapeBrush);

        }
        else if(shapeType == "Ellipse")
        {
          ReadDimensions(inFile, Shape::ShapeType::Ellipse, definePoints, defineMinor, defineMajor);
          ReadPenProperties(inFile, shapePen);
          ReadBrushProperties(inFile, shapeBrush);

          currentShape = new Ellipse(shapeID, definePoints, defineMinor, defineMajor);
          currentShape -> setShape(Shape::ShapeType::Ellipse);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(shapeType == "Circle")
        {
          ReadDimensions(inFile, Shape::ShapeType::Circle, definePoints, defineRadius, defineRadius);
          ReadPenProperties(inFile, shapePen);
          ReadBrushProperties(inFile, shapeBrush);

          currentShape = new Ellipse(shapeID, definePoints, defineRadius, defineRadius);
          currentShape -> setShape(Shape::ShapeType::Circle);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(shapeType == "Text")
        {
          ReadDimensions(inFile, Shape::ShapeType::Text, definePoints, defineLength, defineWidth);
          ReadTextProperties(inFile, shapePen, text, textFont, textAlignFlag);

          currentShape = new Text(shapeID, definePoints, defineWidth, defineLength, text, textFont, textAlignFlag, QPen(), QBrush());
          currentShape -> setShape(Shape::ShapeType::Text);
          currentShape -> setPen(shapePen);
        }



        // store created shape into the vector
        shapes.push_back(currentShape);

        // ignore empty line between shapes in the input file
        inFile.ignore(1000, '\n');

        // clear shapeType; read in next shape in the file
        shapeType.clear();

        // clear the vector that contains the shape's points
        definePoints.clear();

    } // END WHILE-LOOP

    // close file
    inFile.close();

} // END METHOD


/*****************************************************************************
* Method ReadDelimiter:  Class ShapeManager                                  *
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
void ShapeManager::ReadDelimiter(ifstream& fileName, char delimiter)
{
    // ignore everything prior and including the delimiter
    fileName.ignore(1000, delimiter);

    // ignore the space after the delimiter
    fileName.ignore(1000, ' ');

} // END METHOD


/*****************************************************************************
* Method ReadDimensions:   Class ShapeManager                                *
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
void ShapeManager::ReadDimensions(ifstream& fileName, const Shape::ShapeType& shapeType, Vector<QPoint>& definePoints, int& dimA, int& dimB)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    char   readChar;            // PROC & PROC - reads individual characters
    string readDimensions;      // PROC & PROC - reads file dimensions into a string
    string singleDimension;     // PROC & PROC - a single dimension from readDimensions
    Vector<int> dimensions;     // PROC & PROC - stores the dimensions as integers
    QPoint      tempQPoint;     // PROC & PROC - a temporary point



    // SHAPE DIMENSIONS
    // remove "ShapeDimensions: "
    ReadDelimiter(fileName, ':');

    // get dimensions as a string
    getline(fileName, readDimensions);



    // TRANSFORM STRING DIMENSIONS TO INT DIMENSIONS
    // parse through string
    for(int index = 0 ; index < readDimensions.length() ; index++)
    {
        // get character
        readChar = readDimensions[index];

        // ignore the space after a comma
        if(readChar == ' ')
        {
            index++;
        }

        // check for a comma
        while(readChar != ',' && index < readDimensions.length())
        {
            // add to single dimension
            singleDimension += readDimensions[index];

            // read next character
            index++;

            // determine if it is a comma
            readChar = readDimensions[index];
        }

        // transform the single dimension string to an integer
        dimensions.push_back(stoi(singleDimension));

        // prep the single dimension to read the next one
        singleDimension.clear();

    } // END FOR-LOOP


    // GET POINTS
    if(shapeType == Shape::ShapeType::Line     ||
       shapeType == Shape::ShapeType::Polyline ||
       shapeType == Shape::ShapeType::Polygon)
    {
        for(int index = 0 ; index < dimensions.size() ; index++)
        {
            tempQPoint.setX(dimensions[index++]);
            tempQPoint.setY(dimensions[index]);

            definePoints.push_back(tempQPoint);
        }

        // these shapes do not have a length/width/minor/major/radius
        dimA = 0;
        dimB = 0;
    }

    // GET POINTS & LENGTH/WIDTH/MINOR/MAJOR/RADIUS
    if(shapeType == Shape::ShapeType::Rectangle ||
       shapeType == Shape::ShapeType::Square    ||
       shapeType == Shape::ShapeType::Ellipse   ||
       shapeType == Shape::ShapeType::Circle    ||
       shapeType == Shape::ShapeType::Text)
    {
        for(int index = 0 ; index < dimensions.size() ; index++)
        {
            switch(index)
            {
                case 0  :   tempQPoint.setX(dimensions[index++]);
                            tempQPoint.setY(dimensions[index]);
                            break;

                case 2  :   dimA = dimensions[index];
                            break;
                case 3  :   dimB  = dimensions[index];
                            break;
            }

            definePoints.push_back(tempQPoint);
        }
    }

} // END METHOD


/*****************************************************************************
* Method ReadPenProperties: Class ShapeManager                               *
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
void ShapeManager::ReadPenProperties(ifstream& fileName, QPen& shapePen)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    string identifier;  // PROC & PROC - identifies which pen property is read
    int tempInt;        // PROC & PROC - stores a temporary integer



    // PEN COLOR
    // remove "PenColor: "
    ReadDelimiter(fileName, ':');

    // get pen color
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_COLORS ; index++)
    {
        if(identifier == convert::colorList[index].s_color)
        {
            shapePen.setColor(convert::colorList[index].e_color);
        }
    }


    // PEN WIDTH
    // remove "PenWidth: "
    ReadDelimiter(fileName, ':');

    // get pen width
    fileName >> tempInt;
    shapePen.setWidth(tempInt);
    fileName.ignore(1000,'\n');


    // PEN STYLE
    // remove "PenStyle: "
    ReadDelimiter(fileName, ':');

    // get pen style
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_PEN_STYLES ; index++)
    {
        if(identifier == convert::penStyleList[index].s_penStyle)
        {
            shapePen.setStyle(convert::penStyleList[index].e_penStyle);
        }
    }


    // PEN CAP STYLE
    // remove "PenCapStyle: "
    ReadDelimiter(fileName, ':');

    // get pen cap style
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_CAP_STYLES ; index++)
    {
        if(identifier == convert::penCapStyleList[index].s_capStyle)
        {
            shapePen.setCapStyle(convert::penCapStyleList[index].e_capStyle);
        }
    }


    // PEN JOIN STYLE
    // remove "PenJoinStyle: "
    ReadDelimiter(fileName, ':');

    // get pen join style
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_JOIN_STYLES ; index++)
    {
        if(identifier == convert::penJoinStyleList[index].s_joinStyle)
        {
            shapePen.setJoinStyle(convert::penJoinStyleList[index].e_joinStyle);
        }
    }

} // END METHOD


/*****************************************************************************
* Method ReadBrushProperties:  Class ShapeManager                            *
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
void ShapeManager::ReadBrushProperties(ifstream& fileName, QBrush& shapeBrush)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    string identifier;  // PROC & PROC - identifies which brush property is read



    // BRUSH COLOR
    // remove "BrushColor: "
    ReadDelimiter(fileName, ':');

    // get brush color
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_COLORS ; index++)
    {
        if(identifier == convert::colorList[index].s_color)
        {
            shapeBrush.setColor(convert::colorList[index].e_color);
        }
    }


    // BRUSH STYLE
    // remove "BrushStyle: "
    ReadDelimiter(fileName, ':');

    // get brush style
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_BRUSH_STYLES ; index++)
    {
        if(identifier == convert::brushStyleList[index].s_brushStyle)
        {
            shapeBrush.setStyle(convert::brushStyleList[index].e_brushStyle);
        }
    }

} // END METHOD


/*****************************************************************************
* Method ReadTextProperties:  Class ShapeManager                             *
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
void ShapeManager::ReadTextProperties(ifstream& fileName, QPen& shapePen, QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    string identifier;  // PROC & PROC - identifies which brush property is read
    int tempInt;        // PROC & PROC - stores a temporary integer



    // TEXT STRING
    // remove "TextString: "
    ReadDelimiter(fileName, ':');

    // get text string
    getline(fileName, identifier);
    text = QString::fromStdString(identifier);


    // TEXT COLOR
    // remove "TextColor: "
    ReadDelimiter(fileName, ':');

    // get text color (using pen)
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_COLORS ; index++)
    {
        if(identifier == convert::colorList[index].s_color)
        {
            shapePen.setColor(convert::colorList[index].e_color);
        }
    }


    // TEXT ALIGNMENT
    // remove "TextAlignment: "
    ReadDelimiter(fileName, ':');

    // get text alignment
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_ALIGN_FLAGS ; index++)
    {
        if(identifier == convert::alignmentFlagList[index].s_fontAlignFlag)
        {
            textAlignFlag = convert::alignmentFlagList[index].e_fontAlignFlag;
        }
    }


    // TEXT POINT SIZE
    // remove "TextPointSize: "
    ReadDelimiter(fileName, ':');

    // get text point size
    fileName >> tempInt;
    textFont.setPointSize(tempInt);
    fileName.ignore(1000,'\n');


    // TEXT FONT FAMILY
    // remove "TextFontFamily: "
    ReadDelimiter(fileName, ':');

    // get text font family
    getline(fileName, identifier);
    textFont.setFamily(QString::fromStdString(identifier));


    // TEXT FONT STYLE
    // remove "TextFontStyle: "
    ReadDelimiter(fileName, ':');

    // get text font style
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_FONT_STYLES ; index++)
    {
        if(identifier == convert::fontStyleList[index].s_fontStyle)
        {
            textFont.setStyle(convert::fontStyleList[index].e_fontStyle);
        }
    }


    // TEXT FONT WEIGHT
    // remove "TextFontWeight: "
    ReadDelimiter(fileName, ':');

    // get text font weight
    getline(fileName, identifier);

    for(int index = 0 ; index < convert::NUM_FONT_WEIGHTS ; index++)
    {
        if(identifier == convert::fontWeightList[index].s_fontWeight)
        {
            textFont.setWeight(convert::fontWeightList[index].e_fontWeight);
        }
    }

} // END METHOD

/*******************************************************
 * PARSER PARSER PARSER PARSER PARSER PARSER [end]
 *******************************************************/
/*******************************************************
* SERIALIZER SERIALIZER SERIALIZER SERIALIZER [begin]
********************************************************/
/*****************************************************************************
* Method SaveFile:  Class ShapeManager                                       *
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
void ShapeManager::SaveFile(const string& fileName)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    ofstream outFile;           // PROC & PROC - output file stream variable
    Shape::ShapeType shapeType; // PROC & PROC - the shape being read



    // open file
    outFile.open(fileName);

    // parse through shape vector and write it to output file
    for(int index = 0 ; index < shapes.size() ; index++)
    {
        // get the current shape
        shapeType = shapes[index] -> getShape();

        // determine which shape and contents to write to file
        // typecast enumerated type to an integer
        switch(int(shapeType))
        {
            // none
            case 0: break;

            // line
            case 1: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO);
                    outFile << '\n';
                    break;

            // polyline
            case 2: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO);
                    outFile << '\n';
                    break;

            // polygon
            case 3: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO, BRUSH_INFO);
                    outFile << '\n';
                    break;

            // rectangle
            case 4: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO, BRUSH_INFO);
                    outFile << '\n';
                    break;

            // ellipse
            case 5: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO, BRUSH_INFO);
                    outFile << '\n';
                    break;

            // text
            case 6: OutputToFile(outFile, shapes[index], SHAPE_INFO, TEXT_INFO);
                    break;

            // circle
            case 7: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO, BRUSH_INFO);
                    outFile << '\n';
                    break;

            // square
            case 8: OutputToFile(outFile, shapes[index], SHAPE_INFO, PEN_INFO, BRUSH_INFO);
                    outFile << '\n';
                    break;

        } // END SWITCH

    } // END FOR LOOP

    // close file
    outFile.close();

} // END METHOD


/*****************************************************************************
* Method OutputToFile:  Class ShapeManager                                   *
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
void ShapeManager::OutputToFile(ofstream& fileName, Shape* shape, const Output& a, const Output& b, const Output& c, const Output& d)
{
    /*************************************************************************
    * CONSTANTS                                                              *
    *------------------------------------------------------------------------*
    *                                                                        *
    * REQUESTED OUTPUTS TO FILE                                              *
    *------------------------------------------------------------------------*
    * SIZE_AR :   number of unique outputs to print to file (a, b, c, d)     *
    *                                                                        *
    *************************************************************************/
    // REQUESTED OUTPUTS TO FILE
    const int SIZE_AR = 4;


    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    int printAr[SIZE_AR] = {a, b, c ,d};    // PROC & PROC - an array of the
                                            //               unique outputs
    QFont tempFont;                         // PROC & PROC - stores a temporary
                                            //               font



    // print to file each unique information requested
    for(int index = 0 ; index < SIZE_AR ; index++)
    {
        // determine which information to print
        switch(printAr[index])
        {
            case 0  : break;

            // print shape information to file
            case 1  : fileName << "ShapeId: "   << shape -> getID() << '\n';
                      fileName << "ShapeType: " << EnumToString(int(shape -> getShape()), convert::SHAPES) << '\n';
                      fileName << "ShapeDimensions: ";
                      if(shape -> getShape() == Shape::ShapeType::Line)
                      {
                          fileName << static_cast<Line*>(shape) -> getX1() << ", " << static_cast<Line*>(shape) -> getY1() << ", "
                                   << static_cast<Line*>(shape) -> getX2() << ", " << static_cast<Line*>(shape) -> getY2();
                      }
                      if(shape -> getShape() == Shape::ShapeType::Polyline)
                      {
                          Vector<QPoint> tempPoints = static_cast<Polyline*>(shape) -> getPointVector();
                          for(int i = 0 ; i < tempPoints.size() ; i++)
                          {
                              fileName << tempPoints[i].x() << ", " << tempPoints[i].y();
                              if(i != tempPoints.size() - 1)
                                  fileName << ", ";
                          }
                      }
                      if(shape -> getShape() == Shape::ShapeType::Polygon)
                      {
                          Vector<QPoint> tempPoints = static_cast<Polygon*>(shape) -> getPointVector();
                          for(int i = 0 ; i < tempPoints.size() ; i++)
                          {
                              fileName << tempPoints[i].x() << ", " << tempPoints[i].y();
                              if(i != tempPoints.size() - 1)
                                  fileName << ", ";
                          }

                      }
                      if(shape -> getShape() == Shape::ShapeType::Rectangle)
                      {
                          fileName << static_cast<Rectangle*>(shape) -> getX()      << ", " << static_cast<Rectangle*>(shape) -> getY() << ", "
                                   << static_cast<Rectangle*>(shape) -> getLength() << ", " << static_cast<Rectangle*>(shape) -> getWidth();
                      }
                      if(shape -> getShape() == Shape::ShapeType::Ellipse)
                      {
                          fileName << static_cast<Ellipse*>(shape) -> getX()      << ", " << static_cast<Ellipse*>(shape) -> getY() << ", "
                                   << static_cast<Ellipse*>(shape) -> getWidth()  << ", " << static_cast<Ellipse*>(shape) -> getLength();
                      }
                      if(shape -> getShape() == Shape::ShapeType::Text)
                      {
                          fileName << static_cast<Text*>(shape) -> getX()      << ", " << static_cast<Text*>(shape) -> getY() << ", "
                                   << static_cast<Text*>(shape) -> getWidth() << ", " << static_cast<Text*>(shape) -> getLength();
                      }
                      if(shape -> getShape() == Shape::ShapeType::Circle)
                      {
                          fileName << static_cast<Ellipse*>(shape) -> getX()      << ", " << static_cast<Ellipse*>(shape) -> getY() << ", "
                                   << static_cast<Ellipse*>(shape) -> getLength();
                      }
                      if(shape -> getShape() == Shape::ShapeType::Square)
                      {
                          fileName << static_cast<Rectangle*>(shape) -> getX()      << ", " << static_cast<Rectangle*>(shape) -> getY() << ", "
                                   << static_cast<Rectangle*>(shape) -> getLength();
                      }
                      fileName << '\n';
                      break;

            // prints pen information to file
            case 2  : fileName << "PenColor: " << QColorToString(shape -> getPen().color().name().toStdString()) << '\n';
                      fileName << "PenWidth: " << shape -> getPen().width() << '\n';
                      fileName << "PenStyle: "     << EnumToString(shape -> getPen().style(),     convert::PEN_STYLE) << '\n';
                      fileName << "PenCapStyle: "  << EnumToString(shape -> getPen().capStyle(),  convert::PEN_CAP)   << '\n';
                      fileName << "PenJoinStyle: " << EnumToString(shape -> getPen().joinStyle(), convert::PEN_JOIN)  << '\n';
                      break;

            // prints brush information to file
            case 3  : fileName << "BrushColor: " << QColorToString(shape -> getBrush().color().name().toStdString()) << '\n';
                      fileName << "BrushStyle: " << EnumToString(shape -> getBrush().style(), convert::BRUSH_STYLE)  << '\n';
                      break;

            // prints text information to file
            case 4  : tempFont = static_cast<Text*>(shape) -> getFont();
                      fileName << "TextString: "     << static_cast<Text*>(shape) -> getText().toStdString()           << '\n';
                      fileName << "TextColor: "      << QColorToString(shape -> getPen().color().name().toStdString()) << '\n';
                      fileName << "TextAlignment: "  << EnumToString(static_cast<Text*>(shape) -> getAlignment(), convert::ALIGNMENT_FLAG) << '\n';
                      fileName << "TextPointSize: "  << static_cast<Text*>(shape) -> getFont().pointSize() << '\n';
                      fileName << "TextFontFamily: " << static_cast<Text*>(shape) -> getFont().family().toStdString() << '\n';
                      fileName << "TextFontStyle: "  << EnumToString(static_cast<Text*>(shape) -> getFont().style(), convert::FONT_STYLE)   << '\n';
                      fileName << "TextFontWeight: " << EnumToString(static_cast<Text*>(shape) -> getFont().weight(), convert::FONT_WEIGHT);
                      break;

        } // END SWITCH

    } // END FOR LOOP

} // END METHOD


/*****************************************************************************
*  Method QColorToString:  Class ShapeManager                                *
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
string ShapeManager::QColorToString(const string& qcolor)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    string actualColor; // the translated color



    // find corresponding color in the 'convert::' namespace
    for(int index = 0 ; index < convert::NUM_COLORS ; index++)
    {
        if(qcolor == convert::colorList[index].hex_color)
        {
            actualColor = convert::colorList[index].s_color;
        }
    }

    // return the color
    return actualColor;

} // END METHOD


/*****************************************************************************
* Method EnumToString:  Class ShapeManager                                   *
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
string ShapeManager::EnumToString(const int& enumTypeValue, const int& enumListValue)
{
    /*************************************************************************
    * variables                                                              *
    *************************************************************************/
    string enumString {"error"};    // PROC & PROC - default string return



    // determine from which enumeration type to search
    switch(enumListValue)
    {
        // translate 'Shape::ShapeType::' to string
        case 0 :    for(int index = 0 ; index < convert::NUM_SHAPES ; index++)
                    {
                        if(enumTypeValue == int(convert::shapeList[index].e_shapeType))
                        {
                            enumString = convert::shapeList[index].s_shapeType;
                        }
                    }
                    break;

     // case 1 : translate 'QColorConstants::' to string, not used...special case...see method QColorToString

        // translate 'Qt::PenStyle::' to string
        case 2 :    for(int index = 0 ; index < convert::NUM_PEN_STYLES ; index++)
                    {
                        if(enumTypeValue == int(convert::penStyleList[index].e_penStyle))
                        {
                            enumString = convert::penStyleList[index].s_penStyle;
                        }
                    }
                    break;


        // translate 'Qt::PenCapStyle::' to string
        case 3 :    for(int index = 0 ; index < convert::NUM_CAP_STYLES ; index++)
                    {
                        if(enumTypeValue == int(convert::penCapStyleList[index].e_capStyle))
                        {
                            enumString = convert::penCapStyleList[index].s_capStyle;
                        }
                    }
                    break;

        // translate 'Qt::PenJoinStyle::' to string
        case 4 :    for(int index = 0 ; index < convert::NUM_JOIN_STYLES ; index++)
                    {
                        if(enumTypeValue == int(convert::penJoinStyleList[index].e_joinStyle))
                        {
                            enumString = convert::penJoinStyleList[index].s_joinStyle;
                        }
                    }
                    break;

        // translate 'Qt::BrushStyle::' to string
        case 5 :    for(int index = 0 ; index < convert::NUM_BRUSH_STYLES ; index++)
                    {
                        if(enumTypeValue == int(convert::brushStyleList[index].e_brushStyle))
                        {
                            enumString = convert::brushStyleList[index].s_brushStyle;
                        }
                    }
                    break;

        // translate 'Qt::AlignmentFlag::' to string
        case 6 :    for(int index = 0 ; index < convert::NUM_ALIGN_FLAGS ; index++)
                    {
                        if(enumTypeValue == int(convert::alignmentFlagList[index].e_fontAlignFlag))
                        {
                            enumString = convert::alignmentFlagList[index].s_fontAlignFlag;
                        }
                    }
                    break;

        // translate 'QFont::Style::' to string
        case 7 :    for(int index = 0 ; index < convert::NUM_FONT_STYLES ; index++)
                    {
                        if(enumTypeValue == int(convert::fontStyleList[index].e_fontStyle))
                        {
                            enumString = convert::fontStyleList[index].s_fontStyle;
                        }
                    }
                    break;

        // translate 'QFont::Weight::' to string
        case 8 :    for(int index = 0 ; index < convert::NUM_FONT_WEIGHTS ; index++)
                    {
                        if(enumTypeValue == int(convert::fontWeightList[index].e_fontWeight))
                        {
                            enumString = convert::fontWeightList[index].s_fontWeight;
                        }
                    }
                    break;

    } // END SWITCH

    // return translated enum to string
    return enumString;

} // END METHOD

/*******************************************************
* SERIALIZER SERIALIZER SERIALIZER SERIALIZER [end]
********************************************************/
