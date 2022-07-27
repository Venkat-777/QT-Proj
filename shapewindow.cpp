#include "shapewindow.h"
#include "ui_shapewindow.h"

#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QIcon>
#include <QPen>
#include <vector>
#include <QMessageBox>

using sType = Shape::ShapeType;  
using qFlag = Qt::AlignmentFlag;


ShapeWindow::ShapeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ShapeWindow), shapeManager(this)
{
    ui->setupUi(this);

    shapeManager.ReadShapeFile("V:/QT Workspace/MidnightCoder/shapes.txt");

    setupShapeEditor();
}


ShapeWindow::~ShapeWindow()
{
    delete ui;
}


void ShapeWindow::paintEvent(QPaintEvent* event)
{
    shapeManager.drawShapes();
}


void ShapeWindow::setupShapeEditor()
{
    QString shapeString;

    ui->idLCD->display(shapeManager.getShapes()[0]->getID());
    ui->idLCD->setPalette(Qt::black);

    for (auto shape : shapeManager.getShapes())
    {
        shapeString = QString(QChar(shape->getID() + 48));

        switch (shape->getShape())
        {
            case sType::Rectangle : shapeString.append(": Rectangle");
                                    break;

            case sType::Square    : shapeString.append(": Rectangle");
                                    break;

            case sType::Ellipse   : shapeString.append(": Ellipse");
                                    break;

            case sType::Circle    : shapeString.append(": Ellipse");
                                    break;

            case sType::Polygon   : shapeString.append(": Polygon");
                                    break;

            case sType::Polyline  : shapeString.append(": Polyline");
                                    break;

            case sType::Line      : shapeString.append(": Line");
                                    break;

            case sType::Text      : shapeString.append(": Text");
                                    break;
            default : break;
        }

        ui->shapeComboBox->addItem(/*(QIcon)"",*/ shapeString);
    }

    switch(shapeManager.getShapes()[0]->getShape())
    {
        case sType::Rectangle : displayRectangleForm();
                                break;

        case sType::Square    : displayRectangleForm();
                                break;

        case sType::Ellipse   : displayEllipseForm();
                                break;

        case sType::Circle    : displayEllipseForm();
                                break;

        case sType::Polygon   : displayPolygonForm();
                                break;

        case sType::Polyline  : displayPolylineForm();
                                break;

        case sType::Line      : displayLineForm();
                                break;

        case sType::Text      : displayTextForm();
                                break;
        default : break;
    }

    QObject::connect(ui->shapeComboBox, &QComboBox::currentIndexChanged,
                     this,              &ShapeWindow::getSelectedShape);
}


void ShapeWindow::getSelectedShape()
{
    QString textShape { ui->shapeComboBox->currentText() };

    ui->idLCD->display(textShape[0].digitValue());

    clearForm();

    if (textShape.endsWith("Rectangle"))
    {
        displayRectangleForm();
    }
    else if (textShape.endsWith("Ellipse"))
    {
        displayEllipseForm();
    }
    else if (textShape.endsWith("Line"))
    {
        displayLineForm();
    }
    else if (textShape.endsWith("Text"))
    {
        displayTextForm();
    }
    else if (textShape.endsWith("Polygon"))
    {
        displayPolygonForm();
    }
    else if (textShape.endsWith("Polyline"))
    {
        displayPolylineForm();
    }

}


void ShapeWindow::displayRectangleForm()
{
    const QString labelsText[4] { "X:", "Y:", "Width:", "Height:" };

    Rectangle* rect { dynamic_cast<Rectangle*>(shapeManager.getShape(ui->idLCD->value())) };

    int dimensions[4] {rect->getX(), rect->getY(), rect->getWidth(), rect->getLength() };

    void (ShapeWindow::*spinFunctions[4])(int) { &ShapeWindow::changeX,
                                                 &ShapeWindow::changeY,
                                                 &ShapeWindow::changeW,
                                                 &ShapeWindow::changeH };
    QSpinBox* spinBoxes[4];

    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index] = new QSpinBox(ui->shapeEditor);

        // set to the width of the canvas
        spinBoxes[index]->setMaximum(1400);

        spinBoxes[index]->setValue(dimensions[index]);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}


void ShapeWindow::displayEllipseForm()
{
    const QString labelsText[4] { "X:", "Y:", "Minor Axis:", "Major Axis:" };

    Ellipse* ellipse { dynamic_cast<Ellipse*>(shapeManager.getShape(ui->idLCD->value())) };

    int dimensions[4] { ellipse->getX(), ellipse->getY(), ellipse->getWidth(), ellipse->getLength() };

    void (ShapeWindow::*spinFunctions[4])(int) { &ShapeWindow::changeX,
                                                 &ShapeWindow::changeY,
                                                 &ShapeWindow::changeW,
                                                 &ShapeWindow::changeH };
    QSpinBox* spinBoxes[4];

    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index] = new QSpinBox(ui->shapeEditor);

        // Set to the width of the canvas
        spinBoxes[index]->setMaximum(1400);

        spinBoxes[index]->setValue(dimensions[index]);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}



void ShapeWindow::displayLineForm()
{
    const QString labelsText[4] { "X1:", "Y1:", "X2:", "Y2:"};

    Line* line { dynamic_cast<Line*>(shapeManager.getShape(ui->idLCD->value())) };

    int points[4] { line->getX1(), line->getY1(), line->getX2(), line->getY2() };

    void (ShapeWindow::*spinFunctions[4])(int) { &ShapeWindow::changeX1,
                                                 &ShapeWindow::changeY1,
                                                 &ShapeWindow::changeX2,
                                                 &ShapeWindow::changeY2 };
    QSpinBox* spinBoxes[4];

    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index]  = new QSpinBox(ui->shapeEditor);

        // set to the width of the canvas.
        spinBoxes[index]->setMaximum(1400);

        spinBoxes[index]->setValue(points[index]);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}



void ShapeWindow::displayPolygonForm()
{
    const QString labelsText[8] { "X1:", "Y1:", "X2:", "Y2:",
                                  "X3:", "Y3:", "X4:", "Y4:" };

    Polygon* polygon { dynamic_cast<Polygon*>(shapeManager.getShape(ui->idLCD->value())) };

    int points[8] { polygon->getX(0), polygon->getY(0), polygon->getX(1), polygon->getY(1),
                    polygon->getX(2), polygon->getY(2), polygon->getX(3), polygon->getY(3) };

    void (ShapeWindow::*spinFunctions[8])(int) { &ShapeWindow::changeX1, &ShapeWindow::changeY1,
                                                 &ShapeWindow::changeX2, &ShapeWindow::changeY2,
                                                 &ShapeWindow::changeX3, &ShapeWindow::changeY3,
                                                 &ShapeWindow::changeX4, &ShapeWindow::changeY4
                                                                                                };
    QSpinBox* spinBoxes[8];

    // update to dynamically get the number of points!!
     for (int index {0}; index < 8; ++index)
     {
         spinBoxes[index]  = new QSpinBox(ui->shapeEditor);

         // set to the width of the canvas.
         spinBoxes[index]->setMaximum(1400);

         spinBoxes[index]->setValue(points[index]);

         ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

         QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                          this,             spinFunctions[index]);
     }

     displayPenBrushSettings();
}


void ShapeWindow::displayPolylineForm()
{
    const QString labelsText[8] { "X1:", "Y1:", "X2:", "Y2:",
                                  "X3:", "Y3:", "X4:", "Y4:" };

    Polyline* polyline { dynamic_cast<Polyline*>(shapeManager.getShape(ui->idLCD->value())) };

    int points[8] { polyline->getX(0), polyline->getY(0), polyline->getX(1), polyline->getY(1),
                    polyline->getX(2), polyline->getY(2), polyline->getX(3), polyline->getY(3) };

    void (ShapeWindow::*spinFunctions[8])(int) { &ShapeWindow::changeX1, &ShapeWindow::changeY1,
                                                 &ShapeWindow::changeX2, &ShapeWindow::changeY2,
                                                 &ShapeWindow::changeX3, &ShapeWindow::changeY3,
                                                 &ShapeWindow::changeX4, &ShapeWindow::changeY4
                                                                                                 };
    QSpinBox* spinBoxes[8];

     for (int index {0}; index < 8; ++index)
     {
         spinBoxes[index]  = new QSpinBox(ui->shapeEditor);

         // set to the width of the canvas.
         spinBoxes[index]->setMaximum(1400);

         spinBoxes[index]->setValue(points[index]);

         ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

         QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                          this,             spinFunctions[index]);
     }

     displayPenBrushSettings();
}


void ShapeWindow::displayTextForm()
{
    const QString labelsText[4] {"X1:", "Y1:", "Width:", "Length:" };

    Text* text { dynamic_cast<Text*>(shapeManager.getShape(ui->idLCD->value())) };

    int dimensions[4] { text->getX(), text->getY(), text->getWidth(), text->getLength() };

    void (ShapeWindow::*spinFunctions[4])(int) { &ShapeWindow::changeX,
                                                 &ShapeWindow::changeY,
                                                 &ShapeWindow::changeW,
                                                 &ShapeWindow::changeH };

    QLineEdit* lineEdit { new QLineEdit(text->getText(), ui->shapeEditor) };

    qFlag  flag  { text->getAlignment() };
    QFont  font  { text->getFont() };
    QColor color { text->getPen().color() };

    QComboBox* combos[5];
    QSpinBox*  spinBoxes[5];


    ui->shapeForm->addRow((QString)"TextString:", lineEdit);

    QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &ShapeWindow::changeText);


    // ** Text Dimensions & position **
    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index] = new QSpinBox(ui->shapeEditor);

        // adjust values!!
        spinBoxes[index]->setMinimum(0);
        spinBoxes[index]->setMaximum(1400);
        spinBoxes[index]->setValue(dimensions[index]);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);

    }

    // ** TextPointSize **
    spinBoxes[4]  = new QSpinBox(ui->shapeEditor);

    spinBoxes[4]->setMinimum(-1);
    spinBoxes[4]->setMaximum(50);
    spinBoxes[4]->setValue(font.pointSize());

    ui->shapeForm->addRow((QString)"TextPointSize:", spinBoxes[4]);

    QObject::connect(spinBoxes[4], &QSpinBox::valueChanged,
                     this,         &ShapeWindow::changeTextPointSize);



    // ** TextColor **
    combos[0] = colorCombo(color);

    ui->shapeForm->addRow((QString)"TextColor:", combos[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextColor);



    // ** TextAllignment **
    combos[1] = new QComboBox(ui->shapeEditor);

    switch(flag)
    {
        case qFlag::AlignLeft   : combos[1]->addItem((QString)"AlignLeft");
                                  break;
        case qFlag::AlignRight  : combos[1]->addItem((QString)"AlignRight");
                                  break;
        case qFlag::AlignTop    : combos[1]->addItem((QString)"AlignTop");
                                  break;
        case qFlag::AlignBottom : combos[1]->addItem((QString)"AlignBottom");
                                  break;
        case qFlag::AlignCenter : combos[1]->addItem((QString)"AlignCenter");
                                  break;
        default : break;
    }

    combos[1]->addItem((QString)"AlignLeft");
    combos[1]->addItem((QString)"AlignRight");
    combos[1]->addItem((QString)"AlignTop");
    combos[1]->addItem((QString)"AlignBottom");
    combos[1]->addItem((QString)"AlignCenter");

    ui->shapeForm->addRow((QString)"TextAllignment:", combos[1]);

    QObject::connect(combos[1], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextAllignment);



    // ** TextFontFamily **
    combos[2] = new QComboBox(ui->shapeEditor);

    combos[2]->addItem(font.family());
    combos[2]->addItem((QString)"Courier");
    combos[2]->addItem((QString)"Helvetica");
    combos[2]->addItem((QString)"Times");
    combos[2]->addItem((QString)"Comic Sans MS");

    ui->shapeForm->addRow((QString)"TextFontFamily:", combos[2]);


    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontFamily);


    // ** TextFontStyle **
    combos[3] = new QComboBox(ui->shapeEditor);

    if (font.style() == QFont::StyleNormal)
    {
        combos[3]->addItem((QString)"StyleNormal");
    }
    else if (font.style() == QFont::StyleItalic)
    {
        combos[3]->addItem((QString)"StyleItalic");
    }
    else if (font.style() == QFont::StyleOblique)
    {
        combos[3]->addItem((QString)"StyleOblique");
    }

    combos[3]->addItem((QString)"StyleNormal");
    combos[3]->addItem((QString)"StyleItalic");
    combos[3]->addItem((QString)"StyleOblique");

    ui->shapeForm->addRow((QString)"TextFontStyle:", combos[3]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontStyle);


    // ** TextFontWeight **
    combos[4] = new QComboBox(ui->shapeEditor);

    switch(font.weight())
    {
        case QFont::Thin   : combos[4]->addItem((QString)"Thin");
                             break;
        case QFont::Light  : combos[4]->addItem((QString)"Light");
                             break;
        case QFont::Normal : combos[4]->addItem((QString)"Normal");
                             break;
        case QFont::Bold   : combos[4]->addItem((QString)"Bold");
                             break;
        default :  break;
    }

    combos[4]->addItem((QString)"Thin");
    combos[4]->addItem((QString)"Light");
    combos[4]->addItem((QString)"Normal");
    combos[4]->addItem((QString)"Bold");

    ui->shapeForm->addRow((QString)"TextFontWeight:", combos[4]);

    QObject::connect(combos[4], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontWeight);
}




void ShapeWindow::displayPenBrushSettings()
{
    QPen pen     { shapeManager.getShape(ui->idLCD->value())->getPen()   };
    QBrush brush { shapeManager.getShape(ui->idLCD->value())->getBrush() };

    QComboBox* combos[6];


    // **  Pen Color **
    combos[0] = colorCombo(pen.color());

    ui->shapeForm->addRow((QString)"PenColor:", combos[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenColor);


    // ** PenStyle
    combos[1] = new QComboBox(ui->shapeEditor);

    if (pen.style() == Qt::NoPen)
    {
        combos[1]->addItem((QString)"NoPen");
    }
    else if (pen.style() == Qt::SolidLine)
    {
        combos[1]->addItem((QString)"SolidLine");
    }
    else if (pen.style() == Qt::DashLine)
    {
        combos[1]->addItem((QString)"DashLine");
    }
    else if (pen.style() == Qt::DotLine)
    {
        combos[1]->addItem((QString)"DotLine");
    }
    else if (pen.style() == Qt::DashDotLine)
    {
        combos[1]->addItem((QString)"DashDotLine");
    }
    else if (pen.style() == Qt::DashDotDotLine)
    {
        combos[1]->addItem((QString)"DashDotDotLine");
    }

    combos[1]->addItem((QString)"NoPen");
    combos[1]->addItem((QString)"SolidLine");
    combos[1]->addItem((QString)"DashLine");
    combos[1]->addItem((QString)"DotLine");
    combos[1]->addItem((QString)"DashDotLine");
    combos[1]->addItem((QString)"DashDotDotLine");

    ui->shapeForm->addRow((QString)"PenStyle:", combos[1]);

    QObject::connect(combos[1], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenStyle);


    // ** PenCapStyle
    combos[2] = new QComboBox(ui->shapeEditor);

    if (pen.capStyle() == Qt::FlatCap)
    {
        combos[2]->addItem((QString)"FlatCap");
    }
    else if (pen.capStyle() == Qt::SquareCap)
    {
        combos[2]->addItem((QString)"SquareCap");
    }
    else if (pen.capStyle() == Qt::RoundCap)
    {
        combos[2]->addItem((QString)"RoundCap");
    }

    combos[2]->addItem((QString)"FlatCap");
    combos[2]->addItem((QString)"SquareCap");
    combos[2]->addItem((QString)"RoundCap");

    ui->shapeForm->addRow((QString)"PenCapStyle:", combos[2]);

    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenCapStyle);



    // ** PenJoinStyle
    combos[3] = new QComboBox(ui->shapeEditor);

    if (pen.joinStyle() == Qt::MiterJoin)
    {
        combos[3]->addItem((QString)"MiterJoin");
    }
    else if (pen.joinStyle() == Qt::BevelJoin)
    {
        combos[3]->addItem((QString)"BevelJoin");
    }
    else if (pen.joinStyle() == Qt::RoundJoin)
    {
        combos[3]->addItem((QString)"RoundJoin");
    }

    combos[3]->addItem((QString)"MiterJoin");
    combos[3]->addItem((QString)"BevelJoin");
    combos[3]->addItem((QString)"RoundJoin");

    ui->shapeForm->addRow((QString)"PenJoinStyle:", combos[3]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenJoinStyle);


    // ** BrushColor
    combos[4] = colorCombo(brush.color());

    ui->shapeForm->addRow((QString)"BrushColor:", combos[4]);

    QObject::connect(combos[4], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeBrushColor);



    // ** BrushStyle
    combos[5] = new QComboBox(ui->shapeEditor);

    if (brush.style() == Qt::SolidPattern)
    {
        combos[5]->addItem((QString)"SolidPattern");
    }
    else if (brush.style() == Qt::HorPattern)
    {
        combos[5]->addItem((QString)"HorPattern");
    }
    else if (brush.style() == Qt::VerPattern)
    {
        combos[5]->addItem((QString)"VerPattern");
    }
    else if (brush.style() == Qt::NoBrush)
    {
        combos[5]->addItem((QString)"NoBrush");
    }

    combos[5]->addItem((QString)"SolidPattern");
    combos[5]->addItem((QString)"HorPattern");
    combos[5]->addItem((QString)"VerPattern");
    combos[5]->addItem((QString)"NoBrush");

    ui->shapeForm->addRow((QString)"BrushStyle:", combos[5]);

    QObject::connect(combos[5], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeBrushColor);
}




void ShapeWindow::clearForm()
{
    while (ui->shapeForm->rowCount())
    {
        ui->shapeForm->removeRow(0);
    }
}



// **** Configuring Widgets *****


QComboBox* ShapeWindow::colorCombo(QColor color)
{
    QComboBox* box { new QComboBox };

    if (color == QColorConstants::White)
    {
        box->addItem((QIcon)":/img/white.png", (QString)"White");
    }
    else if (color == QColorConstants::Black)
    {
        box->addItem((QIcon)":/img/black.png", (QString)"Black");
    }
    else if (color == QColorConstants::Red)
    {
        box->addItem((QIcon)":/img/red.png", (QString)"Red");
    }
    else if (color == QColorConstants::Green)
    {
        box->addItem((QIcon)":/img/green.png", (QString)"Green");
    }
    else if (color == QColorConstants::Blue)
    {
        box->addItem((QIcon)":/img/blue.png", (QString)"Blue");
    }
    else if (color == QColorConstants::Cyan)
    {
        box->addItem((QIcon)":/img/cyan.png", (QString)"Cyan");
    }
    else if (color == QColorConstants::Magenta)
    {
        box->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    }
    else if (color == QColorConstants::Yellow)
    {
        box->addItem((QIcon)":/img/yellow.png", (QString)"Yellow");
    }
    else if (color == QColorConstants::Gray)
    {
        box->addItem((QIcon)":/img/gray.png", (QString)"Gray");
    }

    box->addItem((QIcon)":/img/white.png",   (QString)"White");
    box->addItem((QIcon)":/img/black.png",   (QString)"Black");
    box->addItem((QIcon)":/img/red.png",     (QString)"Red");
    box->addItem((QIcon)":/img/green.png",   (QString)"Green");
    box->addItem((QIcon)":/img/blue.png",    (QString)"Blue");
    box->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan");
    box->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    box->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow");
    box->addItem((QIcon)":/img/gray.png",    (QString)"Gray");

    return box;
}







// *****  RESPONDING TO SIGNALS *****


// Change X, Y, Width & Height  (Rectangle, Ellips, & Text)
void ShapeWindow::changeX(int x)
{
//     int id = ui->idLCD->value();

    // get the shape...
    // set x
    // update()
}

void ShapeWindow::changeY(int y)
{
//     int id = ui->idLCD->value();

    // get the shape
    // set y
    // update()
}

void ShapeWindow::changeW(int w)
{
//     int id = ui->idLCD->value();

    // get the shape
    // set width
    // update()
}

void ShapeWindow::changeH(int h)
{
//     int id = ui->idLCD->value();

    // get the shape
    // set height/length
    // update()
}




// Change coordinates for line, Polyline, & Polygon
void ShapeWindow::changeX1(int x1){}
void ShapeWindow::changeY1(int y1){}
void ShapeWindow::changeX2(int x2){}
void ShapeWindow::changeY2(int y2){}
void ShapeWindow::changeX3(int x3){}
void ShapeWindow::changeY3(int y3){}
void ShapeWindow::changeX4(int x4){}
void ShapeWindow::changeY4(int y4){}



 // Change Pen & Brush settings
void ShapeWindow::changePenColor(QString color) {}
void ShapeWindow::changePenStyle(QString penStyle){}
void ShapeWindow::changePenCapStyle(QString capStyle){}
void ShapeWindow::changePenJoinStyle(QString joinStyle){}
void ShapeWindow::changeBrushColor(QString color){}
void ShapeWindow::changeBrushStyle(QString color){}



// Change Text settings
void ShapeWindow::changeText(){}
void ShapeWindow::changeTextPointSize(int pointSize) {}
void ShapeWindow::changeTextColor(QString color)     {}
void ShapeWindow::changeTextAllignment(QString allignment){}
void ShapeWindow::changeTextFontFamily(QString fontFamily){}
void ShapeWindow::changeTextFontStyle(QString fontStyle)  {}
void ShapeWindow::changeTextFontWeight(QString fontWeight){}

int ShapeWindow::sortId(){
    int id = 0;
    for (int i = 0; i != shapeManager.getShapes().size(); i++){
        if (id < shapeManager.getShapes()[i]->getID()){
            id = shapeManager.getShapes()[i]->getID();
        }
        //shapeManager.getShapes()[i]->getID();

    //id = shapeManager.getShapes()[shapeManager.getShapes().size()]->getID();
    }
    return id;
}

void ShapeWindow::on_pushButton_2_clicked()
{
    Vector<Shape*>vector = shapeManager.getShapes();
    
    QString currentShape;
    currentShape=ui->allShapes->currentText();
    
    Vector<QPoint> pointSet;
    QPoint points;
    points.setX(10);
    points.setY(10);
    pointSet.push_back(points);
    
    if (currentShape == "Rectangle"){
        int id = sortId() + 1;
        // add new rectangle
        Rectangle* add = new Rectangle(id, pointSet, 10, 10);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    } else if (currentShape == "Line"){
        int id = sortId() + 1;
        // add new line
        Line* add = new Line(id, pointSet);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    } else if (currentShape == "Ellipse"){
        int id = sortId() + 1;
        // add new ellipse
        Ellipse* add = new Ellipse(id, pointSet, 10, 10);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    } else if (currentShape == "Polygon"){
        int id = sortId() + 1;
        // add new polygon
        Polygon* add = new Polygon(id, pointSet);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    } else if (currentShape == "Polyline"){
        int id = sortId() + 1;
        // add new polyline
        Polyline* add = new Polyline(id, pointSet);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    } else if (currentShape == "Text"){
        int id = sortId() + 1;
        // add new text
        QFont font;
        font.setWeight(QFont::Weight::Thin);
        font.setStyle(QFont::Style::StyleNormal);
        Text* add = new Text(id, pointSet, 10, 10, "Default Text", font, Qt::AlignmentFlag::AlignCenter);
        vector.push_back(add);
        shapeManager.addShape(add);
        setupShapeEditor();
    }

    ui->addOrDelete->setText(" is Added.");
}


void ShapeWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Delete", "Are you sure you want to delete?"/*OPTIONAL: , QMessageBox::YES | QMessageBox::NO*/);
        if (reply == QMessageBox::Yes){
            int currentId = 0;
            currentId = ui->selectedShapes->currentIndex();
            shapeManager.removeShape(currentId);
            ui->addOrDelete->setText(" is Deleted.");
        }
}


void ShapeWindow::on_allShapes_currentTextChanged(const QString &arg1)
{
    ui->shapeName->setText(arg1);


    QString currentShape;
    currentShape=ui->allShapes->currentText();

    if (currentShape == "Polygon"){
        ui->selectedShapes->addItem("Here are the Polygon");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Polygon){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }   else if (currentShape == "Ellipse")
    {
        ui->selectedShapes->addItem("Here are the Ellipse");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Ellipse){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }   else if (currentShape == "Line")
    {
        ui->selectedShapes->addItem("Here are the Line");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Line){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }   else if (currentShape == "Polyline")
    {
        ui->selectedShapes->addItem("Here are the Polyline");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Polyline){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }   else if (currentShape == "Rectangle")
    {
        ui->selectedShapes->addItem("Here are the Rectangle");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Rectangle){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }   else if (currentShape == "Text")
    {
        ui->selectedShapes->addItem("Here are the Text");
        for (int i = 0; i != shapeManager.getShapes().size(); i++){
            if (shapeManager.getShapes()[i]->getShape() == Shape::ShapeType::Text){
                ui->selectedShapes->addItem(QString::number(shapeManager.getShapes()[i]->getID()));
            }
        }
    }
}
