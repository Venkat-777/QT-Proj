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

    Vector<int>         tempDimensions;
    Vector<QPoint>      definePoints;
    int                 defineLength;
    int                 defineWidth;
    int                 defineMinor;
    int                 defineMajor;
    int                 defineRadius;



    // open file
    inFile.open("Shape.txt");

    // read the file
    while(inFile)
    {
        // get first character in text file
        inFile.get(delimiter);

        // begin getting shape information
        if(delimiter != '\n')
        {
            // find the colon delimiter
            while(delimiter != ':')
            {
                // read into the identifier as text is parsed for the colon
                identifier += delimiter;

                // get next character
                inFile.get(delimiter);
            }

            // ignore space after the colon
            inFile.ignore(1000,' ');
        }

        // if there is a break in the text file (e.g. a new line character '\n')
        // store the shape and go to the next shape
        else
        {
            currentShape -> setPen(shapePen);
            currentShape -> setBrush(shapeBrush);

            switch(shapeType)
            {
                // shapeID contains the shape's unique ID
                // definePoints is a vector that contains points <QPoint1, QPoint2, etc.>
                //                                               where QPoint contains <(x1 ,y1), (x2, y2), etc.>
                // defineLength contains the length
                // defineWidth contains the width
                // defineMajor contains the major axis
                // defineMinor contains the minor axis
                // text, textFont, etc. contains all text information
                case Shape::ShapeType::None      : break;

                case Shape::ShapeType::Line      : currentShape = new Line(shapeID, definePoints);
                                                   break;

                case Shape::ShapeType::Polyline  : currentShape = new Polyline(shapeID, definePoints);
                                                   break;

                case Shape::ShapeType::Polygon   : currentShape = new Polygon(shapeID, definePoints);
                                                   break;

                case Shape::ShapeType::Rectangle : currentShape = new Rectangle(shapeID, definePoints, defineLength, defineWidth);
                                                   break;

                case Shape::ShapeType::Square    : currentShape = new Rectangle(shapeID, definePoints, defineLength, defineLength);
                                                   break;

                case Shape::ShapeType::Ellipse   : currentShape = new Ellipse(shapeID, definePoints, defineMajor, defineMinor);
                                                   break;

                case Shape::ShapeType::Circle   :  currentShape = new Ellipse(shapeID, definePoints, defineRadius, defineRadius);
                                                   break;

                case Shape::ShapeType::Text      : currentShape = new Text(shapeID, definePoints, defineLength, defineWidth,
                                                                           text, textFont, textAlignFlag, textColor);
                                                   break;
            }

            parserVector.push_back(currentShape);
        }

        // get shape id
        if(identifier == "ShapeId")
        {
            inFile >> shapeID;
            inFile.ignore(1000,'\n');
        }

        // get shape type
        else if(identifier == "ShapeType")
        {
            getline(inFile, setType);

            if(setType == "None")
            {
              currentShape -> setShape(Shape::ShapeType::None);
            }
            else if(setType == "Line")
            {
              currentShape -> setShape(Shape::ShapeType::Line);
            }
            else if(setType == "Polyline")
            {
              currentShape -> setShape(Shape::ShapeType::Polyline);
            }
            else if(setType == "Polygon")
            {
              currentShape -> setShape(Shape::ShapeType::Polygon);
            }
            else if(setType == "Rectangle")
            {
              currentShape -> setShape(Shape::ShapeType::Rectangle);
            }
            else if(setType == "Square")
            {
              currentShape -> setShape(Shape::ShapeType::Square);
            }
            else if(setType == "Ellipse")
            {
              currentShape -> setShape(Shape::ShapeType::Ellipse);
            }
            else if(setType == "Circle")
            {
              currentShape -> setShape(Shape::ShapeType::Circle);
            }
            else if(setType == "Text")
            {
              currentShape -> setShape(Shape::ShapeType::Text);
            }
        }

        else if(identifier == "ShapeDimensions")
        {
            tempDimensions = shapeDimensions(inFile);

            // two points
            if(shapeType == (Shape::ShapeType::Line) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    definePoints[index].setX(tempDimensions[index]);
                    definePoints[index].setY(tempDimensions[++index]);
                }
            }

            // n points
            else if(shapeType == (Shape::ShapeType::Polyline) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    definePoints[index].setX(tempDimensions[index]);
                    definePoints[index].setY(tempDimensions[++index]);
                }
            }

            // n points
            else if(shapeType == (Shape::ShapeType::Polygon) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    definePoints[index].setX(tempDimensions[index]);
                    definePoints[index].setY(tempDimensions[++index]);
                }
            }

            // one point, length, width
            else if(shapeType == (Shape::ShapeType::Rectangle) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    switch(index)
                    {
                        case 0  :   definePoints[index].setX(tempDimensions[index]);
                                    definePoints[index].setY(tempDimensions[++index]);
                                    break;

                        case 2  :   defineLength = tempDimensions[index];
                                    break;
                        case 3  :   defineWidth  = tempDimensions[index];
                                    break;
                    }
                }

            }

            // one point, semi major axis, semi minor axis
            else if(shapeType == (Shape::ShapeType::Ellipse) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    switch(index)
                    {
                        case 0  :   definePoints[index].setX(tempDimensions[index]);
                                    definePoints[index].setY(tempDimensions[++index]);
                                    break;

                        case 2  :   defineMajor = tempDimensions[index];
                                    break;
                        case 3  :   defineMinor = tempDimensions[index];
                                    break;
                    }
                }
            }

            // one point, length, width
            else if(shapeType == (Shape::ShapeType::Text) )
            {
                for(int index = 0 ; index < tempDimensions.size() ; index++)
                {
                    switch(index)
                    {
                        case 0  :   definePoints[index].setX(tempDimensions[index]);
                                    definePoints[index].setY(tempDimensions[++index]);
                                    break;

                        case 2  :   defineLength = tempDimensions[index];
                                    break;
                        case 3  :   defineWidth = tempDimensions[index];
                                    break;
                    }

                }

            }

        } // END SHAPE-DIMENSIONS

        // get pen colors
        else if(identifier == "PenColor")
        {
            getline(inFile, setType);

            if(setType == "white")
            {
              shapePen.setColor(Qt::white);
            }
            else if(setType == "black")
            {
              shapePen.setColor(Qt::black);
            }
            else if(setType == "red")
            {
              shapePen.setColor(Qt::red);
            }
            else if(setType == "green")
            {
              shapePen.setColor(Qt::green);
            }
            else if(setType == "blue")
            {
              shapePen.setColor(Qt::blue);
            }
            else if(setType == "cyan")
            {
              shapePen.setColor(Qt::cyan);
            }
            else if(setType == "magenta")
            {
              shapePen.setColor(Qt::magenta);
            }
            else if(setType == "yellow")
            {
              shapePen.setColor(Qt::yellow);
            }
            else if(setType == "gray")
            {
              shapePen.setColor(Qt::gray);
            }

        }

        // get pen width
        else if(identifier == "PenWidth")
        {
            inFile >> tempInt;
            shapePen.setWidth(tempInt);

            inFile.ignore(1000,'\n');
        }

        // get pen style
        else if(identifier == "PenStyle")
        {
            getline(inFile, setType);

            if(setType == "NoPen")
            {
              shapePen.setStyle(Qt::NoPen);
            }
            else if(setType == "SolidLine")
            {
              shapePen.setStyle(Qt::SolidLine);
            }
            else if(setType == "DashLine")
            {
              shapePen.setStyle(Qt::DashLine);
            }
            else if(setType == "DotLine")
            {
              shapePen.setStyle(Qt::DotLine);
            }
            else if(setType == "DashDotLine")
            {
              shapePen.setStyle(Qt::DashDotLine);
            }
            else if(setType == "DashDotDotLine")
            {
              shapePen.setStyle(Qt::DashDotDotLine);
            }

        }

        // get pen cap style
        else if(identifier == "PenCapStyle")
        {
            getline(inFile, setType);

            if(setType == "FlatCap")
            {
              shapePen.setCapStyle(Qt::FlatCap);
            }
            else if(setType == "SquareCap")
            {
              shapePen.setCapStyle(Qt::SquareCap);
            }
            else if(setType == "RoundCap")
            {
              shapePen.setCapStyle(Qt::RoundCap);
            }
        }

        // get pen join style
        else if(identifier == "PenJoinStyle")
        {
            getline(inFile, setType);

            if(setType == "MiterJoin")
            {
              shapePen.setJoinStyle(Qt::MiterJoin);
            }
            else if(setType == "BevelJoin")
            {
              shapePen.setJoinStyle(Qt::BevelJoin);
            }
            else if(setType == "RoundJoin")
            {
              shapePen.setJoinStyle(Qt::RoundJoin);
            }
        }

        // get brush color
        else if(identifier == "BrushColor")
        {
            getline(inFile, setType);

            if(setType == "white")
            {
              shapeBrush.setColor(Qt::white);
            }
            else if(setType == "black")
            {
              shapeBrush.setColor(Qt::black);
            }
            else if(setType == "red")
            {
              shapeBrush.setColor(Qt::red);
            }
            else if(setType == "green")
            {
              shapeBrush.setColor(Qt::green);
            }
            else if(setType == "blue")
            {
              shapeBrush.setColor(Qt::blue);
            }
            else if(setType == "cyan")
            {
              shapeBrush.setColor(Qt::cyan);
            }
            else if(setType == "magenta")
            {
              shapeBrush.setColor(Qt::magenta);
            }
            else if(setType == "yellow")
            {
              shapeBrush.setColor(Qt::yellow);
            }
            else if(setType == "gray")
            {
              shapeBrush.setColor(Qt::gray);
            }
        }

        // get brush style
        else if(identifier == "BrushStyle")
        {
            getline(inFile, setType);

            if(setType == "SolidPattern")
            {
              shapeBrush.setStyle(Qt::SolidPattern);
            }
            else if(setType == "HorPattern")
            {
              shapeBrush.setStyle(Qt::HorPattern);
            }
            else if(setType == "VerPattern")
            {
              shapeBrush.setStyle(Qt::VerPattern);
            }
            else if(setType == "NoBrush")
            {
              shapeBrush.setStyle(Qt::NoBrush);
            }
        }

        else if(identifier == "TextString")
        {
            getline(inFile, tempString);
            text.fromStdString(tempString);
        }

        else if(identifier == "TextColor")
        {
            getline(inFile, setType);

            if(setType == "white")
            {
              textColor = Qt::GlobalColor::white;
            }
            else if(setType == "black")
            {
              textColor = Qt::GlobalColor::black;
            }
            else if(setType == "red")
            {
              textColor = Qt::GlobalColor::red;
            }
            else if(setType == "green")
            {
              textColor = Qt::GlobalColor::green;
            }
            else if(setType == "blue")
            {
              textColor = Qt::GlobalColor::blue;
            }
            else if(setType == "cyan")
            {
              textColor = Qt::GlobalColor::cyan;
            }
            else if(setType == "magenta")
            {
              textColor = Qt::GlobalColor::magenta;
            }
            else if(setType == "yellow")
            {
              textColor = Qt::GlobalColor::yellow;
            }
            else if(setType == "gray")
            {
              textColor = Qt::GlobalColor::gray;
            }
        }

        else if(identifier == "TextAlignment")
        {
            getline(inFile, setType);

            if(setType == "AlignLeft")
            {
              textAlignFlag = Qt::AlignLeft;
            }
            else if(setType == "AlignRight")
            {
              textAlignFlag = Qt::AlignRight;
            }
            else if(setType == "AlignTop")
            {
              textAlignFlag = Qt::AlignTop;
            }
            else if(setType == "AlignBottom")
            {
              textAlignFlag = Qt::AlignBottom;
            }
            else if(setType == "AlignCenter")
            {
              textAlignFlag = Qt::AlignCenter;
            }
        }

        else if(identifier == "TextPointSize")
        {
            inFile >> tempInt;
            textFont.setPointSize(tempInt);
            inFile.ignore(1000,'\n');
        }

        else if(identifier == "TextFontFamily")
        {
            getline(inFile, tempString);
            qTempString.fromStdString(tempString);
            textFont.setFamily(qTempString);
        }

        else if(identifier == "TextFontStyle")
        {
            getline(inFile, setType);

            if(setType == "StyleNormal")
            {
              textFont.setStyle(QFont::StyleNormal);
            }
            else if(setType == "StyleItalic")
            {
              textFont.setStyle(QFont::StyleItalic);
            }
            else if(setType == "StyleOblique")
            {
              textFont.setStyle(QFont::StyleOblique);
            }
        }

        else if(identifier == "TextFontWeight")
        {
            getline(inFile, setType);

            if(setType == "Thin")
            {
              textFont.setWeight(QFont::Thin);
            }
            else if(setType == "Light")
            {
              textFont.setWeight(QFont::Light);
            }
            else if(setType == "Normal")
            {
              textFont.setWeight(QFont::Normal);
            }
            else if(setType == "Bold")
            {
              textFont.setWeight(QFont::Bold);
            }
        }

        // clear the identifier and setType and go through next line in text file
        identifier.clear();
        setType.clear();

    } // END WHILE-LOOP (INFILE)

} // END METHOD




Vector<int> Parser::shapeDimensions(ifstream& fileName)
{
    /*******************************************************************************
    * variables                                                                    *
    *******************************************************************************/
    string readDimensions;          // PROC & PROC - reads dimensions as a string
    char   delimiter;               // PROC & PROC - determines when an integer has been read
    string singleDimension;         // PROC & PROC - reads 1 dimension from the string
    Vector<int> dimensions;    // PROC & PROC - stores the transformed string into integers



    // get dimensions as a string
    getline(fileName, readDimensions);

    // parse through string
    for(int index = 0 ; index < readDimensions.length() ; index++)
    {
        // get first string character
        delimiter = readDimensions[index];

        // check for a comma
        while(delimiter != ',')
        {
            // add to single dimension
            singleDimension += readDimensions[index];

            // read next character
            index++;

            // determine if it is a comma
            delimiter = readDimensions[index];
        }

        // ignore the space after a comma
        if(delimiter == ' ')
        {
            index++;
        }

        // transform the single dimension string to an integer
        dimensions.push_back(stoi(singleDimension));

        // prep the single dimension to read the next one
        singleDimension.clear();
    }

    return dimensions;

} // END FUNCTION

