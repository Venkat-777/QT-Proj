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

    int              shapeID;     // PROC & PROC - the shape's ID
    Shape::ShapeType shapeType;   // PROC & PROC - the type of shape

    QPen             shapePen;    // PROC & PROC - pen properties of shape being read
    QBrush           shapeBrush;  // PROC & PROC - brush properties of shape being read


    // open file
    inFile.open("Shape.txt");

    // read the file
    while(inFile)
    {
        // get first character in text file
        inFile.get(delimiter);

        // determine if it is a new line character
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

        // if there is a break in the text file (e.g. a new line character)
        // store the shape and go to the next shape
        else
        {
            switch(shapeType)
            {
                case Shape::ShapeType::None      : break;

                case Shape::ShapeType::Line      : currentShape = new Line();
                                                   break;

                case Shape::ShapeType::Polyline  : currentShape = new Polyline();
                                                   break;

                case Shape::ShapeType::Polygon   : currentShape = new Polygon();
                                                   break;

                case Shape::ShapeType::Rectangle : currentShape = new Rectangle(nullptr, shapeID);
                                                   break;

                case Shape::ShapeType::Ellipse   : currentShape = new Ellipse();
                                                   break;

                case Shape::ShapeType::Text      : currentShape = new Text();
                                                   break;

                default :  "Error";
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
            else if(setType == "Ellipse")
            {
              currentShape -> setShape(Shape::ShapeType::Ellipse);
            }
            else if(setType == "Text")
            {
              currentShape -> setShape(Shape::ShapeType::Text);
            }
        }

        // ?????
//        else if(identifier == "ShapeDimensions")
//        {
//            getline(inFile, array[arrayPosition].ShapeDimensions);
//        }

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

        // ???????????
        // get pen width
        else if(identifier == "PenWidth")
        {
            int tempWidth;
            inFile >> tempWidth;
            shapePen.setWidth(tempWidth);

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

//        // ????
//        else if(identifier == "TextString")
//        {
//            getline(inFile, array[arrayPosition].TextString);
//        }

//        // ????
//        else if(identifier == "TextColor")
//        {
//            getline(inFile, setType);

//            if(setType == "white")
//            {
//              shapePen.setColor(Qt::white);
//            }
//            else if(setType == "black")
//            {
//              shapePen.setColor(Qt::black);
//            }
//            else if(setType == "red")
//            {
//              shapePen.setColor(Qt::red);
//            }
//            else if(setType == "green")
//            {
//              shapePen.setColor(Qt::green);
//            }
//            else if(setType == "blue")
//            {
//              shapePen.setColor(Qt::blue);
//            }
//            else if(setType == "cyan")
//            {
//              shapePen.setColor(Qt::cyan);
//            }
//            else if(setType == "magenta")
//            {
//              shapePen.setColor(Qt::magenta);
//            }
//            else if(setType == "yellow")
//            {
//              shapePen.setColor(Qt::yellow);
//            }
//            else if(setType == "gray")
//            {
//              shapePen.setColor(Qt::gray);
//            }
//        }

//        // ?????
//        else if(identifier == "TextAlignment")
//        {
//            getline(inFile, setType);

//            if(setType == "AlignLeft")
//            {
//              shapePen.setColor(Qt::white);
//            }
//            else if(setType == "AlignRight")
//            {
//              shapePen.setColor(Qt::black);
//            }
//            else if(setType == "AlignTop")
//            {
//              shapePen.setColor(Qt::red);
//            }
//            else if(setType == "AlignBottom")
//            {
//              shapePen.setColor(Qt::green);
//            }
//            else if(setType == "AlignCenter")
//            {
//              shapePen.setColor(Qt::blue);
//            }
//        }

//        // ?????
//        else if(identifier == "TextPointSize")
//        {
//            inFile >> array[arrayPosition].TextPointSize;
//            inFile.ignore(1000,'\n');
//        }

//        // ?????
//        else if(identifier == "TextFontFamily")
//        {
//            getline(inFile, array[arrayPosition].TextFontFamily);
//        }

//        // ????
//        else if(identifier == "TextFontStyle")
//        {
//            getline(inFile, setType);

//            if(setType == "StyleNormal")
//            {
//              shapePen.setColor(Qt::white);
//            }
//            else if(setType == "StyleItalic")
//            {
//              shapePen.setColor(Qt::black);
//            }
//            else if(setType == "StyleOblique")
//            {
//              shapePen.setColor(Qt::red);
//            }
//        }

//        // ?????
//        else if(identifier == "TextFontWeight")
//        {
//            getline(inFile, setType);

//            if(setType == "Thin")
//            {
//              shapePen.setColor(Qt::white);
//            }
//            else if(setType == "Light")
//            {
//              shapePen.setColor(Qt::black);
//            }
//            else if(setType == "Normal")
//            {
//              shapePen.setColor(Qt::red);
//            }
//            else if(setType == "Bold")
//            {
//              shapePen.setColor(Qt::red);
//            }
//        }

        // clear the identifier and go through next line in text file
        identifier.clear();

    } // END WHILE-LOOP (INFILE)

} // END METHOD
