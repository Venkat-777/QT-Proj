#include "shapewindow.h"
#include "ui_shapewindow.h"

#include "shape.h"
#include "Polygon.h"
#include "vector.h"

#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QIcon>
#include <vector>


ShapeWindow::ShapeWindow(QWidget *parent) // update to pass our canvas widget as parent!!
    : QMainWindow(parent), ui(new Ui::ShapeWindow), shapeManager(parent)
{
    ui->setupUi(this);

    // Placeholders until we get the actual shapes
    ui->shapeComboBox->addItem(/*(QIcon)":/img/rectangle.png",*/ (QString)"Rectangle");
    ui->shapeComboBox->addItem(/*(QIcon)":/img/ellipse.png",  */ (QString)"Ellipse");
    ui->shapeComboBox->addItem(/*(QIcon)":/img/polygon.png",  */ (QString)"Polygon");
    ui->shapeComboBox->addItem(/*(QIcon)":/img/polyline.png", */ (QString)"Polyline");
    ui->shapeComboBox->addItem(/*(QIcon)":/img/line.png",     */ (QString)"Line");
    ui->shapeComboBox->addItem(/*(QIcon)":/img/text.png",     */ (QString)"Text");

    // connection to signal the selected shape
    QObject::connect(ui->shapeComboBox, &QComboBox::currentIndexChanged,
                     this,              &ShapeWindow::getSelectedShape);

    // update to set with the id of the first shape
    ui->idLCD->display(2);
    ui->idLCD->setPalette(Qt::black);

    // initialize with first shape
    displayRectangleForm();
}


ShapeWindow::~ShapeWindow()
{
    delete ui;
}


void ShapeWindow::getSelectedShape()
{
    QString textShape { ui->shapeComboBox->currentText() };

    clearForm();

    if (textShape == "Rectangle")
    {
        displayRectangleForm();
    }
    else if (textShape == "Ellipse")
    {
        displayEllipseForm();
    }
    else if (textShape == "Line")
    {
        displayLineForm();
    }
    else if (textShape == "Text")
    {
        displayTextForm();
    }
    else if (textShape == "Polygon" || textShape == "Polyline")
    {
        displayPolyForm();
    }

}


void ShapeWindow::displayRectangleForm()
{
     const QString labelsText[4] { "X:", "Y:", "Width:", "Height:" };

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

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}


void ShapeWindow::displayEllipseForm()
{
    const QString labelsText[4] { "X:", "Y:", "Minor Axis:", "Major Axis:" };

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

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}



void ShapeWindow::displayLineForm()
{
    const QString labelsText[4] { "X1:", "Y1:", "X2:", "Y2:"};

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

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}



void ShapeWindow::displayPolyForm()
{
    const QString labelsText[12] { "X1:", "Y1:", "X2:", "Y2:",
                                   "X3:", "Y3:", "X4:", "Y4:",
                                   "X5:", "Y5:", "X6:", "Y6:" };

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

         // Needs to set the current value of the shape!!
         spinBoxes[index]->setValue(100);

         ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

         QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                          this,             spinFunctions[index]);
     }

     displayPenBrushSettings();
}



void ShapeWindow::displayTextForm()
{
    const QString labelsText[4] {"X1:", "Y1:", "Width:", "Length:" };

    void (ShapeWindow::*spinFunctions[4])(int) { &ShapeWindow::changeX,
                                                 &ShapeWindow::changeY,
                                                 &ShapeWindow::changeW,
                                                 &ShapeWindow::changeH };
    QComboBox* combos[5];
    QSpinBox*  spinBoxes[5];
    QLineEdit*  lineEdit { new QLineEdit((QString)"The Text String", ui->shapeEditor) };

    ui->shapeForm->addRow((QString)"TextString:", lineEdit);

    QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &ShapeWindow::changeText);


    // ** Text Dimensions & position **
    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index] = new QSpinBox(ui->shapeEditor);

        // adjust values!!
        spinBoxes[index]->setMinimum(0);
        spinBoxes[index]->setMaximum(1000);
        spinBoxes[index]->setValue(100);

        ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);

    }

    // ** TextPointSize **
    spinBoxes[4]  = new QSpinBox(ui->shapeEditor);

    spinBoxes[4]->setMinimum(-1);
    spinBoxes[4]->setMaximum(50);
    spinBoxes[4]->setValue(0);

    ui->shapeForm->addRow((QString)"TextPointSize:", spinBoxes[4]);

    QObject::connect(spinBoxes[4], &QSpinBox::valueChanged,
                     this,         &ShapeWindow::changeTextPointSize);



    // ** TextColor **
    combos[0] = new QComboBox(ui->shapeEditor);

    combos[0]->addItem((QIcon)":/img/white.png",   (QString)"White");
    combos[0]->addItem((QIcon)":/img/black.png",   (QString)"Black");
    combos[0]->addItem((QIcon)":/img/red.png",     (QString)"Red");
    combos[0]->addItem((QIcon)":/img/green.png",   (QString)"Green");
    combos[0]->addItem((QIcon)":/img/blue.png",    (QString)"Blue");
    combos[0]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan");
    combos[0]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[0]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow");
    combos[0]->addItem((QIcon)":/img/gray.png",    (QString)"Gray");

    ui->shapeForm->addRow((QString)"TextColor:", combos[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextColor);


    // ** TextAllignment **
    combos[1] = new QComboBox(ui->shapeEditor);

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

    combos[2]->addItem((QString)"Comic Sans MS");
    combos[2]->addItem((QString)"Courier");
    combos[2]->addItem((QString)"Helvetica");
    combos[2]->addItem((QString)"Times");

    ui->shapeForm->addRow((QString)"TextFontFamily:", combos[2]);


    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontFamily);


    // ** TextFontStyle **

    combos[3] = new QComboBox(ui->shapeEditor);

    combos[3]->addItem((QString)"Normal");
    combos[3]->addItem((QString)"Italic");
    combos[3]->addItem((QString)"Oblique");

    ui->shapeForm->addRow((QString)"TextFontFamily:", combos[3]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontStyle);


    // ** TextFontWeight **
    combos[4] = new QComboBox(ui->shapeEditor);

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
    QComboBox*   combos[6];

    // **  Pen Color **
    combos[0]     = new QComboBox(ui->shapeEditor);

    combos[0]->addItem((QIcon)":/img/white.png",   (QString)"White"  );
    combos[0]->addItem((QIcon)":/img/black.png",   (QString)"Black"  );
    combos[0]->addItem((QIcon)":/img/red.png",     (QString)"Red"    );
    combos[0]->addItem((QIcon)":/img/green.png",   (QString)"Green"  );
    combos[0]->addItem((QIcon)":/img/blue.png",    (QString)"Blue"   );
    combos[0]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan"   );
    combos[0]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[0]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow" );
    combos[0]->addItem((QIcon)":/img/gray.png",    (QString)"Gray"   );

    ui->shapeForm->addRow((QString)"PenColor:", combos[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenColor);



    // ** PenStyle
    combos[1] = new QComboBox(ui->shapeEditor);

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

    combos[2]->addItem((QString)"FlatCap");
    combos[2]->addItem((QString)"SquareCap");
    combos[2]->addItem((QString)"RoundCap");

    ui->shapeForm->addRow((QString)"PenCapStyle:", combos[2]);

    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenCapStyle);



    // ** PenJoinStyle
    combos[3] = new QComboBox(ui->shapeEditor);

    combos[3]->addItem((QString)"MiterJoin");
    combos[3]->addItem((QString)"BevelJoin");
    combos[3]->addItem((QString)"RoundJoin");

    ui->shapeForm->addRow((QString)"PenJoinStyle:", combos[3]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenJoinStyle);



    // ** BrushColor
    combos[4]     = new QComboBox(ui->shapeEditor);

    combos[4]->addItem((QIcon)":/img/white.png",   (QString)"White");
    combos[4]->addItem((QIcon)":/img/black.png",   (QString)"Black");
    combos[4]->addItem((QIcon)":/img/red.png",     (QString)"Red");
    combos[4]->addItem((QIcon)":/img/green.png",   (QString)"Green");
    combos[4]->addItem((QIcon)":/img/blue.png",    (QString)"Blue");
    combos[4]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan");
    combos[4]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[4]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow");
    combos[4]->addItem((QIcon)":/img/gray.png",    (QString)"Gray");

    ui->shapeForm->addRow((QString)"BrushColor:", combos[4]);

    QObject::connect(combos[4], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeBrushColor);



    // ** BrushStyle
    combos[5] = new QComboBox(ui->shapeEditor);


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

void ShapeWindow::on_pushButton_2_clicked()
{
    //ShapeManager::addShape();
    ui->addOrDelete->setText(" is Added.");
}


void ShapeWindow::on_pushButton_clicked()
{
    ui->addOrDelete->setText(" is Deleted.");
}


void ShapeWindow::on_allShapes_currentTextChanged(const QString &arg1)
{
    ui->shapeName->setText(arg1);
    shapeManager.ReadShapeFile("Shape.txt");
    //read.ReadShapeFile("Shape.txt");
    Vector<Shape*>vector /* = PLACE HOLDER*/;
    //vector = read.getShapeVector();

    QString currentShape;
    currentShape=ui->allShapes->currentText();

    if (currentShape == "Polygon"){
        ui->selectedShapes->addItem("Here are the Polygons");

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Polygon){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }

    }   else if (currentShape == "Ellipse")
    {
        ui->selectedShapes->addItem("Here are the Ellipse");
        //ui->selectedShapes->addItem(QString::number(vector[1]->getID()));

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Ellipse){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }
    }   else if (currentShape == "Line")
    {
        ui->selectedShapes->addItem("Here are the Line");
        //ui->selectedShapes->addItem(QString::number(vector[1]->getID()));

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Line){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }
    }   else if (currentShape == "Polyline")
    {
        ui->selectedShapes->addItem("Here are the Polyline");
        //ui->selectedShapes->addItem(QString::number(vector[1]->getID()));

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Polyline){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }
    }   else if (currentShape == "Rectangle")
    {
        ui->selectedShapes->addItem("Here are the Rectangle");
        //ui->selectedShapes->addItem(QString::number(vector[1]->getID()));

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Rectangle){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }
    }   else if (currentShape == "Text")
    {
        ui->selectedShapes->addItem("Here are the Text");
        //ui->selectedShapes->addItem(QString::number(vector[1]->getID()));

        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Text){
                ui->selectedShapes->addItem(QString::number(vector[i]->getID()));
            }
        }
    }
}

