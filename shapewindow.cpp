#include "shapewindow.h"
#include "ui_shapewindow.h"

#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QIcon>

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
    QLabel*      labels[4];
    QSpinBox*    spinBoxes[4];
    QHBoxLayout* horLayouts[4];

    for (int index {0}; index < 4; ++index)
    {
        labels[index]     = new QLabel(labelsText[index], ui->shapeEditor);
        spinBoxes[index]  = new QSpinBox(ui->shapeEditor);
        horLayouts[index] = new QHBoxLayout(ui->shapeEditor);

        // set to the width of the canvas
        spinBoxes[index]->setMaximum(1400);

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        horLayouts[index]->addWidget(labels[index]);
        horLayouts[index]->addWidget(spinBoxes[index]);

        ui->shapeForm->addRow(horLayouts[index]);

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
    QLabel*      labels[4];
    QSpinBox*    spinBoxes[4];
    QHBoxLayout* horLayouts[4];

    for (int index {0}; index < 4; ++index)
    {
        labels[index]     = new QLabel(labelsText[index], ui->shapeEditor);
        spinBoxes[index]  = new QSpinBox(ui->shapeEditor);
        horLayouts[index] = new QHBoxLayout(ui->shapeEditor);

        // Set to the width of the canvas
        spinBoxes[index]->setMaximum(1400);

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        horLayouts[index]->addWidget(labels[index]);
        horLayouts[index]->addWidget(spinBoxes[index]);

        ui->shapeForm->addRow(horLayouts[index]);

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
    QLabel*      labels[4];
    QSpinBox*    spinBoxes[4];
    QHBoxLayout* horLayouts[4];

    for (int index {0}; index < 4; ++index)
    {
        labels[index]     = new QLabel(labelsText[index], ui->shapeEditor);
        spinBoxes[index]  = new QSpinBox(ui->shapeEditor);
        horLayouts[index] = new QHBoxLayout(ui->shapeEditor);

        // set to the width of the canvas.
        spinBoxes[index]->setMaximum(1400);

        // Needs to set the current value of the shape!!
        spinBoxes[index]->setValue(100);

        horLayouts[index]->addWidget(labels[index]);
        horLayouts[index]->addWidget(spinBoxes[index]);

        ui->shapeForm->addRow(horLayouts[index]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);
    }

    displayPenBrushSettings();
}



void ShapeWindow::displayPolyForm()
{
    void (ShapeWindow::*spinFunctions[8])(int) { &ShapeWindow::changeX1, &ShapeWindow::changeY1,
                                                 &ShapeWindow::changeX2, &ShapeWindow::changeY2,
                                                 &ShapeWindow::changeX3, &ShapeWindow::changeY3,
                                                 &ShapeWindow::changeX4, &ShapeWindow::changeY4
                                                                                                };

    const QString labelsText[12] { "X1:", "Y1:", "X2:", "Y2:",
                                   "X3:", "Y3:", "X4:", "Y4:",
                                   "X5:", "Y5:", "X6:", "Y6:" };
    QLabel*      labels[8];
    QSpinBox*    spinBoxes[8];
    QHBoxLayout* horLayouts[8];

    // update to dynamically get the number of points!!
     for (int index {0}; index < 8; ++index)
     {
         labels[index]     = new QLabel(labelsText[index], ui->shapeEditor);
         spinBoxes[index]  = new QSpinBox(ui->shapeEditor);
         horLayouts[index] = new QHBoxLayout(ui->shapeEditor);

         // set to the width of the canvas.
         spinBoxes[index]->setMaximum(1400);

         // Needs to set the current value of the shape!!
         spinBoxes[index]->setValue(100);

         horLayouts[index]->addWidget(labels[index]);
         horLayouts[index]->addWidget(spinBoxes[index]);

         ui->shapeForm->addRow(horLayouts[index]);

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
    QLabel*      labels[11];
    QComboBox*   combos[5];
    QHBoxLayout* horLayouts[11];
    QLineEdit*   lineEdit;
    QSpinBox*    spinBoxes[5];


    // ** TextString **
    labels[0]     = new QLabel((QString)"TextString:", ui->shapeEditor);
    lineEdit      = new QLineEdit((QString)"The Text String", ui->shapeEditor);
    horLayouts[0] = new QHBoxLayout(ui->shapeEditor);

    horLayouts[0]->addWidget(labels[0]);
    horLayouts[0]->addWidget(lineEdit);

    ui->shapeForm->addRow(horLayouts[0]);

    // Add connection...


    // ** Text Dimensions & position **
    for (int index {0}; index < 4; ++index)
    {
        labels[index+1]      = new QLabel(labelsText[index], ui->shapeEditor);
        horLayouts[index+1]  = new QHBoxLayout(ui->shapeEditor);
        spinBoxes[index]     = new QSpinBox(ui->shapeEditor);

        spinBoxes[index]->setMinimum(0);
        spinBoxes[index]->setMaximum(1000);
        spinBoxes[index]->setValue(100);

        horLayouts[index+1]->addWidget(labels[index+1]);
        horLayouts[index+1]->addWidget(spinBoxes[index]);

        ui->shapeForm->addRow(horLayouts[index+1]);

        QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                         this,             spinFunctions[index]);

    }

    // ** TextPointSize **
    labels[5]     = new QLabel((QString)"TextPointSize:", ui->shapeEditor);
    spinBoxes[4]  = new QSpinBox(ui->shapeEditor);
    horLayouts[5] = new QHBoxLayout(ui->shapeEditor);

    spinBoxes[4]->setMinimum(-1);
    spinBoxes[4]->setMaximum(50);
    spinBoxes[4]->setValue(0);

    horLayouts[5]->addWidget(labels[5]);
    horLayouts[5]->addWidget(spinBoxes[4]);

    ui->shapeForm->addRow(horLayouts[5]);

    QObject::connect(spinBoxes[4], &QSpinBox::valueChanged,
                     this,         &ShapeWindow::changeTextPointSize);



    // ** TextColor **
    labels[6] = new QLabel((QString)"TextColor:", ui->shapeEditor);
    combos[0] = new QComboBox(ui->shapeEditor);
    horLayouts[6] = new QHBoxLayout(ui->shapeEditor);

    combos[0]->addItem((QIcon)":/img/white.png",   (QString)"White");
    combos[0]->addItem((QIcon)":/img/black.png",   (QString)"Black");
    combos[0]->addItem((QIcon)":/img/red.png",     (QString)"Red");
    combos[0]->addItem((QIcon)":/img/green.png",   (QString)"Green");
    combos[0]->addItem((QIcon)":/img/blue.png",    (QString)"Blue");
    combos[0]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan");
    combos[0]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[0]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow");
    combos[0]->addItem((QIcon)":/img/gray.png",    (QString)"Gray");

    horLayouts[6]->addWidget(labels[6]);
    horLayouts[6]->addWidget(combos[0]);

    ui->shapeForm->addRow(horLayouts[6]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextColor);


    // ** TextAllignment **
    labels[7]     = new QLabel((QString)"TextAllignment:", ui->shapeEditor);
    combos[1]     = new QComboBox(ui->shapeEditor);
    horLayouts[7] = new QHBoxLayout(ui->shapeEditor);

    combos[1]->addItem((QString)"AlignLeft");
    combos[1]->addItem((QString)"AlignRight");
    combos[1]->addItem((QString)"AlignTop");
    combos[1]->addItem((QString)"AlignBottom");
    combos[1]->addItem((QString)"AlignCenter");

    horLayouts[7]->addWidget(labels[7]);
    horLayouts[7]->addWidget(combos[1]);

    ui->shapeForm->addRow(horLayouts[7]);

    QObject::connect(combos[1], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextAllignment);



    // ** TextFontFamily **
    labels[8]     = new QLabel((QString)"TextFontFamily:", ui->shapeEditor);
    combos[2]     = new QComboBox(ui->shapeEditor);
    horLayouts[8] = new QHBoxLayout(ui->shapeEditor);

    combos[2]->addItem((QString)"Comic Sans MS");
    combos[2]->addItem((QString)"Courier");
    combos[2]->addItem((QString)"Helvetica");
    combos[2]->addItem((QString)"Times");

    horLayouts[8]->addWidget(labels[8]);
    horLayouts[8]->addWidget(combos[2]);

    ui->shapeForm->addRow(horLayouts[8]);

    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontFamily);


    // ** TextFontStyle **
    labels[9]     = new QLabel((QString)"TextFontStyle:", ui->shapeEditor);
    combos[3]     = new QComboBox(ui->shapeEditor);
    horLayouts[9] = new QHBoxLayout(ui->shapeEditor);

    combos[3]->addItem((QString)"Normal");
    combos[3]->addItem((QString)"Italic");
    combos[3]->addItem((QString)"Oblique");

    horLayouts[9]->addWidget(labels[9]);
    horLayouts[9]->addWidget(combos[3]);

    ui->shapeForm->addRow(horLayouts[9]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontStyle);


    // ** TextFontWeight **
    labels[10]     = new QLabel((QString)"TextFontWeight:", ui->shapeEditor);
    combos[4]      = new QComboBox(ui->shapeEditor);
    horLayouts[10] = new QHBoxLayout(ui->shapeEditor);

    combos[4]->addItem((QString)"Thin");
    combos[4]->addItem((QString)"Light");
    combos[4]->addItem((QString)"Normal");
    combos[4]->addItem((QString)"Bold");

    horLayouts[10]->addWidget(labels[10]);
    horLayouts[10]->addWidget(combos[4]);

    ui->shapeForm->addRow(horLayouts[10]);

    QObject::connect(combos[4], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeTextFontWeight);
}




void ShapeWindow::displayPenBrushSettings()
{
    QLabel*      labels[6];
    QComboBox*   combos[6];
    QHBoxLayout* horLayouts[6];


    // **  Pen Color **
    labels[0]     = new QLabel((QString)"PenColor:", ui->shapeEditor);
    combos[0]     = new QComboBox(ui->shapeEditor);
    horLayouts[0] = new QHBoxLayout(ui->shapeEditor);

    combos[0]->addItem((QIcon)":/img/white.png",   (QString)"White"  );
    combos[0]->addItem((QIcon)":/img/black.png",   (QString)"Black"  );
    combos[0]->addItem((QIcon)":/img/red.png",     (QString)"Red"    );
    combos[0]->addItem((QIcon)":/img/green.png",   (QString)"Green"  );
    combos[0]->addItem((QIcon)":/img/blue.png",    (QString)"Blue"   );
    combos[0]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan"   );
    combos[0]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[0]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow" );
    combos[0]->addItem((QIcon)":/img/gray.png",    (QString)"Gray"   );

    horLayouts[0]->addWidget(labels[0]);
    horLayouts[0]->addWidget(combos[0]);

    ui->shapeForm->addRow(horLayouts[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenColor);



    // ** PenStyle
    labels[1]     = new QLabel((QString)"PenStyle:", ui->shapeEditor);
    combos[1]     = new QComboBox(ui->shapeEditor);
    horLayouts[1] = new QHBoxLayout(ui->shapeEditor);

    combos[1]->addItem((QString)"NoPen");
    combos[1]->addItem((QString)"SolidLine");
    combos[1]->addItem((QString)"DashLine");
    combos[1]->addItem((QString)"DotLine");
    combos[1]->addItem((QString)"DashDotLine");
    combos[1]->addItem((QString)"DashDotDotLine");

    horLayouts[1]->addWidget(labels[1]);
    horLayouts[1]->addWidget(combos[1]);

    ui->shapeForm->addRow(horLayouts[1]);

    QObject::connect(combos[1], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenStyle);



    // ** PenCapStyle
    labels[2]     = new QLabel((QString)"PenCapStyle:", ui->shapeEditor);
    combos[2]     = new QComboBox(ui->shapeEditor);
    horLayouts[2] = new QHBoxLayout(ui->shapeEditor);

    combos[2]->addItem((QString)"FlatCap");
    combos[2]->addItem((QString)"SquareCap");
    combos[2]->addItem((QString)"RoundCap");

    horLayouts[2]->addWidget(labels[2]);
    horLayouts[2]->addWidget(combos[2]);

    ui->shapeForm->addRow(horLayouts[2]);

    QObject::connect(combos[2], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenCapStyle);



    // ** PenJoinStyle
    labels[3]     = new QLabel((QString)"PenJoinStyle:", ui->shapeEditor);
    combos[3]     = new QComboBox(ui->shapeEditor);
    horLayouts[3] = new QHBoxLayout(ui->shapeEditor);

    combos[3]->addItem((QString)"MiterJoin");
    combos[3]->addItem((QString)"BevelJoin");
    combos[3]->addItem((QString)"RoundJoin");

    horLayouts[3]->addWidget(labels[3]);
    horLayouts[3]->addWidget(combos[3]);

    ui->shapeForm->addRow(horLayouts[3]);

    QObject::connect(combos[3], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenJoinStyle);



    // ** BrushColor
    labels[4]     = new QLabel((QString)"BrushColor:", ui->shapeEditor);
    combos[4]     = new QComboBox(ui->shapeEditor);
    horLayouts[4] = new QHBoxLayout(ui->shapeEditor);

    combos[4]->addItem((QIcon)":/img/white.png",   (QString)"White");
    combos[4]->addItem((QIcon)":/img/black.png",   (QString)"Black");
    combos[4]->addItem((QIcon)":/img/red.png",     (QString)"Red");
    combos[4]->addItem((QIcon)":/img/green.png",   (QString)"Green");
    combos[4]->addItem((QIcon)":/img/blue.png",    (QString)"Blue");
    combos[4]->addItem((QIcon)":/img/cyan.png",    (QString)"Cyan");
    combos[4]->addItem((QIcon)":/img/magenta.png", (QString)"Magenta");
    combos[4]->addItem((QIcon)":/img/yellow.png",  (QString)"Yellow");
    combos[4]->addItem((QIcon)":/img/gray.png",    (QString)"Gray");

    horLayouts[4]->addWidget(labels[4]);
    horLayouts[4]->addWidget(combos[4]);

    ui->shapeForm->addRow(horLayouts[4]);

    QObject::connect(combos[4], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changeBrushColor);



    // ** BrushStyle
    labels[5]     = new QLabel((QString)"BrushStyle:", ui->shapeEditor);
    combos[5]     = new QComboBox(ui->shapeEditor);
    horLayouts[5] = new QHBoxLayout(ui->shapeEditor);

    combos[5]->addItem((QString)"SolidPattern");
    combos[5]->addItem((QString)"HorPattern");
    combos[5]->addItem((QString)"VerPattern");
    combos[5]->addItem((QString)"NoBrush");

    horLayouts[5]->addWidget(labels[5]);
    horLayouts[5]->addWidget(combos[5]);

    ui->shapeForm->addRow(horLayouts[5]);

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
void ShapeWindow::changeText(QString text){}
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
    Parser read;
    read.ReadShapeFile("Shape.txt");
    Vector<Shape *>vector;
    vector = read.getShapeVector();

    if (arg1 == "Rectangle"){
        //Polygon polygon;
        for (int i = 0; i != vector.size(); i++){
            if (vector[i]->getShape() == Shape::ShapeType::Polygon){
                ui->selectedShapes->addItem((QString::number)(vector[i]->getID()));

                ui->selectedShapes->addItem(/*(QIcon)":/img/rectangle.png",*/ (QString)"Rectangle");
                ui->selectedShapes->addItem(/*(QIcon)":/img/ellipse.png",  */ (QString)"Ellipse");

                //QObject::connect(ui->allShapes, &QComboBox::currentIndexChanged, this, );
            }
        }
        //ui->selectedShapes->addItem(polygon.getShape(vector));
    }
}
