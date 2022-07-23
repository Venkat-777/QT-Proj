#include "Parser.h"



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
Parser::Parser()
{
}


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
Parser::~Parser()
{
}


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
void Parser::ReadShapeFile(const string fileName)
{
    /*******************************************************************************
    * variables                                                                    *
    *******************************************************************************/
    ifstream inFile;     // PROC & PROC - input stream variable to read file
    string   identifier; // PROC & PROC - identifies what shape property is being read
    string   setType;    // PROC & PROC - determines what to set the indentifier to
    char     delimiter;  // PROC & PROC - determines when to stop reading the file

    QString  qTempString;   // PROC & PROC - used to read temporary QString
    string   tempString;    // PROC & PROC - used to read temporary string
    int      tempInt;       // PROC & PROC - used to read temporary integers

    int               shapeID;       // PROC & PROC - the shape's ID
    Shape::ShapeType  shapeType;     // PROC & PROC - the type of shape

    QPen              shapePen;      // PROC & PROC - pen properties of shape being read

    QBrush            shapeBrush;    // PROC & PROC - brush properties of shape being read

    QString           text;          // PROC & PROC - string of text         
    QFont             textFont;      // PROC & PROC - text font style
    Qt::AlignmentFlag textAlignFlag; // PROC & PROC - text alignment
    Qt::GlobalColor   textColor;     // PROC & PROC - text color


    Vector<QPoint>      definePoints;
    int                 defineLength;
    int                 defineWidth;
    int                 defineMinor;
    int                 defineMajor;
    int                 defineRadius;




    // open file
    inFile.open(fileName);

    // read the file
    while(inFile)
    {
        // remove "ShapeID: "
        ReadDelimiter(inFile, ':');

        // get shape id
        inFile >> shapeID;
        inFile.ignore(1000, '\n');


        // remove "ShapeType: "
        ReadDelimiter(inFile, ':');
        getline(inFile, setType);

        if(setType == "Line")
        {
          ReadPolyline(inFile, definePoints, shapePen);
          currentShape = new Line(shapeID, definePoints);
          currentShape -> setShape(Shape::ShapeType::Line);
          currentShape -> setPen(shapePen);

        }
        else if(setType == "Polyline")
        {
          ReadPolyline(inFile, definePoints, shapePen);
          currentShape = new Polyline(shapeID, definePoints);
          currentShape -> setShape(Shape::ShapeType::Polyline);
          currentShape -> setPen(shapePen);

        }
        else if(setType == "Polygon")
        {
          ReadPolygon(inFile, definePoints, shapePen, shapeBrush);
          currentShape = new Polygon(shapeID, definePoints);
          currentShape -> setShape(Shape::ShapeType::Polygon);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }

        else if(setType == "Rectangle")
        {
          ReadRectangle(inFile, definePoints, defineLength, defineWidth, shapePen, shapeBrush);
          currentShape = new Rectangle(shapeID, definePoints, defineLength, defineWidth);
          currentShape -> setShape(Shape::ShapeType::Rectangle);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(setType == "Square")
        {
            ReadRectangle(inFile, definePoints, defineLength, defineWidth, shapePen, shapeBrush);
            currentShape = new Rectangle(shapeID, definePoints, defineLength, defineWidth);
            currentShape -> setShape(Shape::ShapeType::Square);
            currentShape -> setPen(shapePen);
            currentShape -> setBrush(shapeBrush);

        }
        else if(setType == "Ellipse")
        {
          ReadEllipse(inFile, definePoints, defineMinor, defineMajor, shapePen, shapeBrush);
          currentShape = new Ellipse(shapeID, definePoints, defineMinor, defineMajor);
          currentShape -> setShape(Shape::ShapeType::Ellipse);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(setType == "Circle")
        {
          ReadEllipse(inFile, definePoints, defineMinor, defineMinor, shapePen, shapeBrush);
          currentShape = new Ellipse(shapeID, definePoints, defineMinor, defineMajor);
          currentShape -> setShape(Shape::ShapeType::Circle);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }
        else if(setType == "Text")
        {
          ReadText(inFile, definePoints, defineLength, defineWidth, text, textFont, textAlignFlag, textColor);
          currentShape = new Text(shapeID, definePoints, defineLength, defineWidth, text, textFont, textAlignFlag);
          currentShape -> setShape(Shape::ShapeType::Text);
          currentShape -> setPen(shapePen);
          currentShape -> setBrush(shapeBrush);

        }

        // ignore space between shapes
        inFile.ignore(1000, '\n');

        // clear identifier and setType for next shape reading
        identifier.clear();
        setType.clear();

        // push shape into vector
        shapeVector.push_back(currentShape);

        definePoints = Vector<QPoint>();

    } // END WHILE-LOOP

} // END METHOD



//***************************************************************************************************

MC_Vec::Vector<Shape*> Parser::getShapeVector() const
{
    return shapeVector;
}

//***************************************************************************************************

void Parser::ReadDelimiter(ifstream& fileName, char delimiter)
{
    // ignore everything prior and including the delimiter
    fileName.ignore(1000, delimiter);

    // ignore the space after the delimiter
    fileName.ignore(1000, ' ');
}

//***************************************************************************************************

// POLYLINE + LINE
// n points
void Parser::ReadPolyline(ifstream& fileName, Vector<QPoint>& definePoints, QPen& shapePen)
{
    Vector<int> tempDimensions;
    QPoint tempQPoint;


    tempDimensions = ReadDimensions(fileName);
    for(int index = 0 ; index < tempDimensions.size() ; index++)
    {
        tempQPoint.setX(tempDimensions[index++]);
        tempQPoint.setY(tempDimensions[index]);

        definePoints.push_back(tempQPoint);
    }

    ReadPenProperties(fileName, shapePen);
}

//***************************************************************************************************

// POLYGON
// n points
void Parser::ReadPolygon(ifstream& fileName, Vector<QPoint>& definePoints, QPen& shapePen, QBrush& shapeBrush)
{
    Vector<int> tempDimensions;
    QPoint tempQPoint;

    tempDimensions = ReadDimensions(fileName);
    for(int index = 0 ; index < tempDimensions.size() ; index++)
    {
        tempQPoint.setX(tempDimensions[index++]);
        tempQPoint.setY(tempDimensions[index]);

        definePoints.push_back(tempQPoint);
    }

    ReadPenProperties(fileName, shapePen);
    ReadBrushProperties(fileName, shapeBrush);
}

//***************************************************************************************************

// RECTANGLE + SQUARE
// 1 point, length, width
void Parser::ReadRectangle(ifstream& fileName, Vector<QPoint>& definePoints, int& defineLength, int& defineWidth, QPen& shapePen, QBrush& shapeBrush)
{
    Vector<int> tempDimensions;
    QPoint tempQPoint;

    tempDimensions = ReadDimensions(fileName);
    for(int index = 0 ; index < tempDimensions.size() ; index++)
    {
        switch(index)
        {
            case 0  :   tempQPoint.setX(tempDimensions[index++]);
                        tempQPoint.setY(tempDimensions[index]);
                        break;

            case 2  :   defineLength = tempDimensions[index];
                        break;
            case 3  :   defineWidth  = tempDimensions[index];
                        break;
        }

        definePoints.push_back(tempQPoint);
    }

    ReadPenProperties(fileName, shapePen);
    ReadBrushProperties(fileName, shapeBrush);
}

//***************************************************************************************************

// ELLIPSE + CIRCLE
// 1 point, minor axis, major axis
void Parser::ReadEllipse(ifstream& fileName, Vector<QPoint>& definePoints, int& minor, int& major, QPen& shapePen, QBrush& shapeBrush)
{
    Vector<int> tempDimensions;
    QPoint tempQPoint;

    tempDimensions = ReadDimensions(fileName);
    for(int index = 0 ; index < tempDimensions.size() ; index++)
    {
        switch(index)
        {
            case 0  :   tempQPoint.setX(tempDimensions[index++]);
                        tempQPoint.setY(tempDimensions[index]);
                        break;

            case 2  :   minor = tempDimensions[index];
                        break;
            case 3  :   major = tempDimensions[index];
                        break;
        }

         definePoints.push_back(tempQPoint);
    }

    ReadPenProperties(fileName, shapePen);
    ReadBrushProperties(fileName, shapeBrush);
}

//***************************************************************************************************

// TEXT
// 1 point, length, width
void Parser::ReadText(ifstream& fileName, Vector<QPoint>& definePoints, int& defineLength, int& defineWidth,
                      QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag, Qt::GlobalColor& textColor)
{
    Vector<int> tempDimensions;
    QPoint tempQPoint;

    tempDimensions = ReadDimensions(fileName);
    for(int index = 0 ; index < tempDimensions.size() ; index++)
    {
        switch(index)
        {
            case 0  :   tempQPoint.setX(tempDimensions[index++]);
                        tempQPoint.setY(tempDimensions[index]);
                        break;

            case 2  :   defineLength = tempDimensions[index];
                        break;
            case 3  :   defineWidth  = tempDimensions[index];
                        break;
        }

        definePoints.push_back(tempQPoint);
    }

    ReadTextProperties(fileName, text, textFont, textAlignFlag, textColor);
}

//***************************************************************************************************

void Parser::ReadPenProperties(ifstream& fileName, QPen& shapePen)
{
    string identifier;
    int tempInt;



    // remove "PenColor: "
    ReadDelimiter(fileName, ':');

    // get pen color
    getline(fileName, identifier);

    if(identifier == "white")
    {
      shapePen.setColor(Qt::white);
    }
    else if(identifier == "black")
    {
      shapePen.setColor(Qt::black);
    }
    else if(identifier == "red")
    {
      shapePen.setColor(Qt::red);
    }
    else if(identifier == "green")
    {
      shapePen.setColor(Qt::green);
    }
    else if(identifier == "blue")
    {
      shapePen.setColor(Qt::blue);
    }
    else if(identifier == "cyan")
    {
      shapePen.setColor(Qt::cyan);
    }
    else if(identifier == "magenta")
    {
      shapePen.setColor(Qt::magenta);
    }
    else if(identifier == "yellow")
    {
      shapePen.setColor(Qt::yellow);
    }
    else if(identifier == "gray")
    {
      shapePen.setColor(Qt::gray);
    }


    // remove "PenWidth: "
    ReadDelimiter(fileName, ':');

    // get pen width
    fileName >> tempInt;
    shapePen.setWidth(tempInt);
    fileName.ignore(1000,'\n');


    // remove "PenStyle: "
    ReadDelimiter(fileName, ':');

    // get pen style
    getline(fileName, identifier);

    if(identifier == "NoPen")
    {
      shapePen.setStyle(Qt::NoPen);
    }
    else if(identifier == "SolidLine")
    {
      shapePen.setStyle(Qt::SolidLine);
    }
    else if(identifier == "DashLine")
    {
      shapePen.setStyle(Qt::DashLine);
    }
    else if(identifier == "DotLine")
    {
      shapePen.setStyle(Qt::DotLine);
    }
    else if(identifier == "DashDotLine")
    {
      shapePen.setStyle(Qt::DashDotLine);
    }
    else if(identifier == "DashDotDotLine")
    {
      shapePen.setStyle(Qt::DashDotDotLine);
    }


    // remove "PenCapStyle: "
    ReadDelimiter(fileName, ':');

    // get pen cap style
    getline(fileName, identifier);

    if(identifier == "FlatCap")
    {
      shapePen.setCapStyle(Qt::FlatCap);
    }
    else if(identifier == "SquareCap")
    {
      shapePen.setCapStyle(Qt::SquareCap);
    }
    else if(identifier == "RoundCap")
    {
      shapePen.setCapStyle(Qt::RoundCap);
    }


    // remove "PenJoinStyle: "
    ReadDelimiter(fileName, ':');

    // get pen join style
    getline(fileName, identifier);

    if(identifier == "MiterJoin")
    {
      shapePen.setJoinStyle(Qt::MiterJoin);
    }
    else if(identifier == "BevelJoin")
    {
      shapePen.setJoinStyle(Qt::BevelJoin);
    }
    else if(identifier == "RoundJoin")
    {
      shapePen.setJoinStyle(Qt::RoundJoin);
    }
}

//***************************************************************************************************

void Parser::ReadBrushProperties(ifstream& fileName, QBrush& shapeBrush)
{
    string identifier;



    // remove "BrushColor: "
    ReadDelimiter(fileName, ':');

    // get brush color
    getline(fileName, identifier);

    if(identifier == "white")
    {
      shapeBrush.setColor(Qt::white);
    }
    else if(identifier == "black")
    {
      shapeBrush.setColor(Qt::black);
    }
    else if(identifier == "red")
    {
      shapeBrush.setColor(Qt::red);
    }
    else if(identifier == "green")
    {
      shapeBrush.setColor(Qt::green);
    }
    else if(identifier == "blue")
    {
      shapeBrush.setColor(Qt::blue);
    }
    else if(identifier == "cyan")
    {
      shapeBrush.setColor(Qt::cyan);
    }
    else if(identifier == "magenta")
    {
      shapeBrush.setColor(Qt::magenta);
    }
    else if(identifier == "yellow")
    {
      shapeBrush.setColor(Qt::yellow);
    }
    else if(identifier == "gray")
    {
      shapeBrush.setColor(Qt::gray);
    }


    // remove "BrushStyle: "
    ReadDelimiter(fileName, ':');

    // get brush style
    getline(fileName, identifier);

    if(identifier == "SolidPattern")
    {
      shapeBrush.setStyle(Qt::SolidPattern);
    }
    else if(identifier == "HorPattern")
    {
      shapeBrush.setStyle(Qt::HorPattern);
    }
    else if(identifier == "VerPattern")
    {
      shapeBrush.setStyle(Qt::VerPattern);
    }
    else if(identifier == "NoBrush")
    {
      shapeBrush.setStyle(Qt::NoBrush);
    }

}

//***************************************************************************************************

// TEXT
void Parser::ReadTextProperties(ifstream& fileName, QString& text, QFont& textFont, Qt::AlignmentFlag& textAlignFlag, Qt::GlobalColor& textColor)
{
    string identifier;
    QString qTempString;
    int tempInt;




    // remove "TextString: "
    ReadDelimiter(fileName, ':');

    // get text string
    getline(fileName, identifier);

    text.fromStdString(identifier);



    // remove "TextColor: "
    ReadDelimiter(fileName, ':');

    // get text color
    getline(fileName, identifier);

    if(identifier == "white")
    {
      textColor = Qt::GlobalColor::white;
    }
    else if(identifier == "black")
    {
      textColor = Qt::GlobalColor::black;
    }
    else if(identifier == "red")
    {
      textColor = Qt::GlobalColor::red;
    }
    else if(identifier == "green")
    {
      textColor = Qt::GlobalColor::green;
    }
    else if(identifier == "blue")
    {
      textColor = Qt::GlobalColor::blue;
    }
    else if(identifier == "cyan")
    {
      textColor = Qt::GlobalColor::cyan;
    }
    else if(identifier == "magenta")
    {
      textColor = Qt::GlobalColor::magenta;
    }
    else if(identifier == "yellow")
    {
      textColor = Qt::GlobalColor::yellow;
    }
    else if(identifier == "gray")
    {
      textColor = Qt::GlobalColor::gray;
    }



    // remove "TextAlignment: "
    ReadDelimiter(fileName, ':');

    // get text alignment
    getline(fileName, identifier);

    if(identifier == "AlignLeft")
    {
      textAlignFlag = Qt::AlignLeft;
    }
    else if(identifier == "AlignRight")
    {
      textAlignFlag = Qt::AlignRight;
    }
    else if(identifier == "AlignTop")
    {
      textAlignFlag = Qt::AlignTop;
    }
    else if(identifier == "AlignBottom")
    {
      textAlignFlag = Qt::AlignBottom;
    }
    else if(identifier == "AlignCenter")
    {
      textAlignFlag = Qt::AlignCenter;
    }


    // remove "TextPointSize: "
    ReadDelimiter(fileName, ':');

    // get text point size
    fileName >> tempInt;
    textFont.setPointSize(tempInt);
    fileName.ignore(1000,'\n');



    // remove "TextFontFamily: "
    ReadDelimiter(fileName, ':');

    // get text font family
    getline(fileName, identifier);
    qTempString.fromStdString(identifier);
    textFont.setFamily(qTempString);



    // remove "TextFontStyle: "
    ReadDelimiter(fileName, ':');

    // get text font style
    getline(fileName, identifier);

    if(identifier == "StyleNormal")
    {
      textFont.setStyle(QFont::StyleNormal);
    }
    else if(identifier == "StyleItalic")
    {
      textFont.setStyle(QFont::StyleItalic);
    }
    else if(identifier == "StyleOblique")
    {
      textFont.setStyle(QFont::StyleOblique);
    }



    // remove "TextFontWeight: "
    ReadDelimiter(fileName, ':');

    // get text font weight
    getline(fileName, identifier);

    if(identifier == "Thin")
    {
      textFont.setWeight(QFont::Thin);
    }
    else if(identifier == "Light")
    {
      textFont.setWeight(QFont::Light);
    }
    else if(identifier == "Normal")
    {
      textFont.setWeight(QFont::Normal);
    }
    else if(identifier == "Bold")
    {
      textFont.setWeight(QFont::Bold);
    }
}

//***************************************************************************************************

Vector<int> Parser::ReadDimensions(ifstream& fileName)
{
    /*******************************************************************************
    * variables                                                                    *
    *******************************************************************************/
    string readDimensions;          // PROC & PROC - reads dimensions as a string
    char   delimiter;               // PROC & PROC - determines when an integer has been read
    string singleDimension;         // PROC & PROC - reads 1 dimension from the string
    Vector<int> dimensions;         // PROC & PROC - stores the transformed string into integers



    // remove "ShapeDimensions: "
    ReadDelimiter(fileName, ':');

    // get dimensions as a string
    getline(fileName, readDimensions);

    // parse through string
    for(int index = 0 ; index < readDimensions.length() ; index++)
    {
        // get first string character
        delimiter = readDimensions[index];

        // ignore the space after a comma
        if(delimiter == ' ')
        {
            index++;
        }

        // check for a comma
        while(delimiter != ',' && index < readDimensions.length())
        {
            // add to single dimension
            singleDimension += readDimensions[index];

            // read next character
            index++;

            // determine if it is a comma
            delimiter = readDimensions[index];
        }


        // transform the single dimension string to an integer
        dimensions.push_back(stoi(singleDimension));

        // prep the single dimension to read the next one
        singleDimension.clear();
    }

    return dimensions;

} // END FUNCTION
