#include "shapewindow.h"
#include "ui_shapewindow.h"

#include <map>
#include <QString>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QIcon>
#include <vector>
#include <QMessageBox>


using sType  = Shape::ShapeType;
using qFlag  = Qt::AlignmentFlag;


ShapeWindow::ShapeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ShapeWindow), shapeManager(this)
{
    ui->setupUi(this);

    shapeManager.ReadShapeFile("V:/QT Workspace/MidnightCoder/shapes.txt");
    //shapeManager.SaveFile("V:/QT Workspace/MidnightCoder/shapes.txt");

    setupShapeEditor();

    QObject::connect(ui->shapeComboBox, &QComboBox::currentIndexChanged,
                     this,              &ShapeWindow::getSelectedShape);
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

    clearComboBox();

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
    Rectangle* rect { dynamic_cast<Rectangle*>(shapeManager.getShape(ui->idLCD->value())) };

    QSpinBox* spinBoxes[2];
    QSlider*  sliders[2];

    sliders[0]   = createSlider(10, 1300, rect->getX());
    sliders[1]   = createSlider(10, 830,  rect->getY());
    spinBoxes[0] = createSpinBox(10, 1300, 10, rect->getWidth());
    spinBoxes[1] = createSpinBox(10, 1300, 10, rect->getLength());

    ui->shapeForm->addRow((QString)"X:", sliders[0]);
    ui->shapeForm->addRow((QString)"Y:", sliders[1]);
    ui->shapeForm->addRow((QString)"Width:",  spinBoxes[0]);
    ui->shapeForm->addRow((QString)"Height:", spinBoxes[1]);

    QObject::connect(sliders[0],   &QSlider::valueChanged,  this, &ShapeWindow::changeX);
    QObject::connect(sliders[1],   &QSlider::valueChanged,  this, &ShapeWindow::changeY);
    QObject::connect(spinBoxes[0], &QSpinBox::valueChanged, this, &ShapeWindow::changeW);
    QObject::connect(spinBoxes[1], &QSpinBox::valueChanged, this, &ShapeWindow::changeH);

    displayPenBrushSettings();
}


void ShapeWindow::displayEllipseForm()
{
    Ellipse* ellipse { dynamic_cast<Ellipse*>(shapeManager.getShape(ui->idLCD->value())) };

    QSpinBox* spinBoxes[2];
    QSlider*  sliders[2];

    sliders[0]   = createSlider(10, 1300, ellipse->getX());
    sliders[1]   = createSlider(10,  830, ellipse->getY());
    spinBoxes[0] = createSpinBox(10, 1300, 10, ellipse->getWidth());
    spinBoxes[1] = createSpinBox(10, 1300, 10, ellipse->getLength());

    ui->shapeForm->addRow((QString)"X:", sliders[0]);
    ui->shapeForm->addRow((QString)"Y:", sliders[1]);
    ui->shapeForm->addRow((QString)"Width:",  spinBoxes[0]);
    ui->shapeForm->addRow((QString)"Height:", spinBoxes[1]);

    QObject::connect(sliders[0],   &QSlider::valueChanged,  this, &ShapeWindow::changeX);
    QObject::connect(sliders[1],   &QSlider::valueChanged,  this, &ShapeWindow::changeY);
    QObject::connect(spinBoxes[0], &QSpinBox::valueChanged, this, &ShapeWindow::changeW);
    QObject::connect(spinBoxes[1], &QSpinBox::valueChanged, this, &ShapeWindow::changeH);

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
    QSlider*  sliders[2];
    QSpinBox* spinBoxes[4];

    sliders[0] = createSlider(5, 1300, line->getX1());
    sliders[1] = createSlider(5, 880, line->getY1());

    ui->shapeForm->addRow((QString)"X:", sliders[0]);
    ui->shapeForm->addRow((QString)"Y:", sliders[1]);

    QObject::connect(sliders[0], &QSlider::valueChanged, this, &ShapeWindow::moveXaxis);
    QObject::connect(sliders[1], &QSlider::valueChanged, this, &ShapeWindow::moveYaxis);

    for (int index {0}; index < 4; ++index)
    {
        spinBoxes[index] = createSpinBox(10, 1200, 10, points[index]);

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
    QSlider*  sliders[2];
    QSpinBox* spinBoxes[8];

    sliders[0] = createSlider(10, 1300, points[0]);
    sliders[1] = createSlider(10, 830, points[1]);

    ui->shapeForm->addRow((QString)"X:", sliders[0]);
    ui->shapeForm->addRow((QString)"Y:", sliders[1]);

    QObject::connect(sliders[0], &QSlider::valueChanged, this, &ShapeWindow::moveXaxis);
    QObject::connect(sliders[1], &QSlider::valueChanged, this, &ShapeWindow::moveYaxis);


     for (int index {0}; index < 8; ++index)
     {
         spinBoxes[index] = createSpinBox(10, 1200, 10, points[index]);

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
    QSlider* sliders[2];
    QSpinBox* spinBoxes[8];

    sliders[0] = createSlider(10, 1300, points[0]);
    sliders[1] = createSlider(10, 830, points[1]);

    ui->shapeForm->addRow((QString)"X:", sliders[0]);
    ui->shapeForm->addRow((QString)"Y:", sliders[1]);

    QObject::connect(sliders[0], &QSlider::valueChanged, this, &ShapeWindow::moveXaxis);
    QObject::connect(sliders[1], &QSlider::valueChanged, this, &ShapeWindow::moveYaxis);

     for (int index {0}; index < 8; ++index)
     {
         spinBoxes[index] = createSpinBox(10, 1200, 10, points[index]);

         ui->shapeForm->addRow(labelsText[index], spinBoxes[index]);

         QObject::connect(spinBoxes[index], &QSpinBox::valueChanged,
                          this,             spinFunctions[index]);
     }

     displayPenBrushSettings();
}


void ShapeWindow::displayTextForm()
{
    Text* text { dynamic_cast<Text*>(shapeManager.getShape(ui->idLCD->value())) };

    int dimensions[4] { text->getX(), text->getY(), text->getWidth(), text->getLength() };

    QLineEdit* lineEdit { new QLineEdit(text->getText(), ui->shapeEditor) };

    qFlag  flag  { text->getAlignment() };
    QFont  font  { text->getFont() };
    QColor color { text->getPen().color() };

    QComboBox* combos[5];
    QSpinBox*  spinBoxes[3];
    QSlider*   sliders[2];

    sliders[0]   = createSlider(10,  1300,     dimensions[0]);
    sliders[1]   = createSlider(10,   830,     dimensions[1]);
    spinBoxes[0] = createSpinBox(10, 1200, 10, dimensions[2]);
    spinBoxes[1] = createSpinBox(10, 1200, 10, dimensions[3]);

    ui->shapeForm->addRow((QString)"TextString:", lineEdit);
    ui->shapeForm->addRow((QString)"X:",          sliders[0]);
    ui->shapeForm->addRow((QString)"Y:",          sliders[1]);
    ui->shapeForm->addRow((QString)"Width:",      spinBoxes[0]);
    ui->shapeForm->addRow((QString)"Length:",     spinBoxes[1]);

    QObject::connect(lineEdit,     &QLineEdit::textEdited,  this, &ShapeWindow::changeText);
    QObject::connect(sliders[0],   &QSlider::valueChanged,  this, &ShapeWindow::changeX   );
    QObject::connect(sliders[1],   &QSlider::valueChanged,  this, &ShapeWindow::changeY   );
    QObject::connect(spinBoxes[0], &QSpinBox::valueChanged, this, &ShapeWindow::changeW   );
    QObject::connect(spinBoxes[1], &QSpinBox::valueChanged, this, &ShapeWindow::changeH   );



    // ** TextPointSize **
    spinBoxes[2] = createSpinBox(-1, 50, 1, font.pointSize());

    ui->shapeForm->addRow((QString)"TextPointSize:", spinBoxes[2]);

    QObject::connect(spinBoxes[2], &QSpinBox::valueChanged,
                     this,         &ShapeWindow::changeTextPointSize);



    // ** TextColor **
    combos[0] = colorCombo(color);

    ui->shapeForm->addRow((QString)"TextColor:", combos[0]);

    QObject::connect(combos[0], &QComboBox::currentTextChanged,
                     this,      &ShapeWindow::changePenColor);



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
        combos[3]->addItem((QString)"Normal");
    }
    else if (font.style() == QFont::StyleItalic)
    {
        combos[3]->addItem((QString)"Italic");
    }
    else if (font.style() == QFont::StyleOblique)
    {
        combos[3]->addItem((QString)"Oblique");
    }

    combos[3]->addItem((QString)"Normal");
    combos[3]->addItem((QString)"Italic");
    combos[3]->addItem((QString)"Oblique");

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
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    QPen pen     { shape->getPen()   };
    QBrush brush { shape->getBrush() };

    QSpinBox*  spinBox;
    QComboBox* combos[6];


    // ** Pen Width **
    spinBox = createSpinBox(1, 15, 1, shape->getPen().width());

    ui->shapeForm->addRow((QString)"PenWidth:", spinBox);

    QObject::connect(spinBox, &QSpinBox::valueChanged, this, &ShapeWindow::changePenWidth);


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


    // **** Brush Settings *****

    if (   shape->getShape() != sType::Line
        && shape->getShape() != sType::Polyline)
    {

        // ** BrushColor **
        combos[4] = colorCombo(brush.color());

        ui->shapeForm->addRow((QString)"BrushColor:", combos[4]);

        QObject::connect(combos[4], &QComboBox::currentTextChanged,
                         this,      &ShapeWindow::changeBrushColor);



        // ** BrushStyle **
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
                         this,      &ShapeWindow::changeBrushStyle);
    }
}


void ShapeWindow::clearComboBox()
{
    while (ui->shapeComboBox->count())
    {
        ui->shapeComboBox->removeItem(0);
    }
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


// ** SpinBox **
QSpinBox* ShapeWindow::createSpinBox(int min, int max, int step, int value)
{
    QSpinBox* spinBox = new QSpinBox(ui->shapeEditor);

    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setSingleStep(step);
    spinBox->setValue(value);

    return spinBox;
}


// ** Slider **
QSlider* ShapeWindow::createSlider(int min, int max, int position)
{
    QSlider* slider = { new QSlider(Qt::Horizontal, ui->shapeEditor) };

    slider->setRange(min, max);

    slider->setSliderPosition(position);

    return slider;
}





// *****  RESPONDING TO SIGNALS *****


void ShapeWindow::moveXaxis(int x)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    if (shape->getShape() == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->move(x - polygon->getX(0), 0);
    }
    else if (shape->getShape() == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->move(x - polyline->getX(0), 0);
    }
    else
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->move(x - line->getX1(), 0);
    }

    update();
}


void ShapeWindow::moveYaxis(int y)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    if (shape->getShape() == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->move(0, y - polygon->getY(0));
    }
    else if (shape->getShape() == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->move(0, y - polyline->getY(0));
    }
    else
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->move(0, y - line->getY1());
    }

    update();
}



// **** Change X, Y, Width & Height  (Rectangle, Ellips, & Text) ****

void ShapeWindow::changeX(int x)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Rectangle || type == sType::Square)
    {
        Rectangle* rect { dynamic_cast<Rectangle*>(shape) };

        rect->setX(x);
    }
    else if (type == sType::Ellipse || type == sType::Circle)
    {
        Ellipse* ellipse { dynamic_cast<Ellipse*>(shape) };

        ellipse->setX(x);
    }
    else
    {
        Text* text { dynamic_cast<Text*>(shape) };

        text->setX(x);
    }

    update();
}


void ShapeWindow::changeY(int y)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Rectangle || type == sType::Square)
    {
        Rectangle* rect { dynamic_cast<Rectangle*>(shape) };

        rect->setY(y);
    }
    else if (type == sType::Ellipse || type == sType::Circle)
    {
        Ellipse* ellipse { dynamic_cast<Ellipse*>(shape) };

        ellipse->setY(y);
    }
    else
    {
        Text* text { dynamic_cast<Text*>(shape) };

        text->setY(y);
    }

    update();
}


void ShapeWindow::changeW(int w)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Rectangle || type == sType::Square)
    {
        Rectangle* rect { dynamic_cast<Rectangle*>(shape) };

        rect->setWidth(w);
    }
    else if (type == sType::Ellipse || type == sType::Circle)
    {
        Ellipse* ellipse { dynamic_cast<Ellipse*>(shape) };

        ellipse->setWidth(w);
    }
    else
    {
        Text* text { dynamic_cast<Text*>(shape) };

        text->setWidth(w);
    }

    update();
}


void ShapeWindow::changeH(int h)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Rectangle || type == sType::Square)
    {
        Rectangle* rect { dynamic_cast<Rectangle*>(shape) };

        rect->setLength(h);
    }
    else if (type == sType::Ellipse || type == sType::Circle)
    {
        Ellipse* ellipse { dynamic_cast<Ellipse*>(shape) };

        ellipse->setLength(h);
    }
    else
    {
        Text* text { dynamic_cast<Text*>(shape) };

        text->setLength(h);
    }

    update();
}


// **** Change coordinates for line, Polyline, & Polygon  ****

void ShapeWindow::changeX1(int x1)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Line)
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->setX(x1, 0);
    }
    else if (type == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setX(x1, 0);
    }
    else
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setX(x1, 0);
    }

    update();
}


void ShapeWindow::changeY1(int y1)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Line)
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->setY(y1, 0);
    }
    else if (type == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setY(y1, 0);
    }
    else
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setY(y1, 0);
    }

    update();
}


void ShapeWindow::changeX2(int x2)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Line)
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->setX(x2, 1);
    }
    else if (type == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setX(x2, 1);
    }
    else
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setX(x2, 1);
    }

    update();
}


void ShapeWindow::changeY2(int y2)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Line)
    {
        Line* line { dynamic_cast<Line*>(shape) };

        line->setY(y2, 1);
    }
    else if (type == sType::Polyline)
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setY(y2, 1);
    }
    else
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setY(y2, 1);
    }

    update();
}


//  **** Polygon & Polyline  ****

void ShapeWindow::changeX3(int x3)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setX(x3, 2);
    }
    else
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setX(x3, 2);
    }

    update();
}


void ShapeWindow::changeY3(int y3)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setY(y3, 2);
    }
    else
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setY(y3, 2);
    }

    update();
}


void ShapeWindow::changeX4(int x4)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setX(x4, 3);
    }
    else
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setX(x4, 3);
    }

    update();
}


void ShapeWindow::changeY4(int y4)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    sType  type  { shape->getShape() };

    if (type == sType::Polygon)
    {
        Polygon* polygon { dynamic_cast<Polygon*>(shape) };

        polygon->setY(y4, 3);
    }
    else
    {
        Polyline* polyline { dynamic_cast<Polyline*>(shape) };

        polyline->setY(y4, 3);
    }

    update();
}


 // **** Change Pen & Brush settings ****

void ShapeWindow::changePenWidth(int width)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    shape->setPenWidth(width);

    update();
}


void ShapeWindow::changePenColor(QString color)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    shape->setPenColor(QColor(color));

    update();
}


void ShapeWindow::changePenStyle(QString penStyle)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    std::map<QString, Qt::PenStyle> map { {"SolidLine",      Qt::SolidLine     },
                                          {"DashLine",       Qt::DashLine      },
                                          {"DotLine",        Qt::DotLine       },
                                          {"DashDotLine",    Qt::DashDotLine   },
                                          {"DashDotDotLine", Qt::DashDotDotLine} };
    shape->setPenStyle(map[penStyle]);

    update();
}


void ShapeWindow::changePenCapStyle(QString capStyle)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    std::map<QString, Qt::PenCapStyle> map { {"FlatCap",   Qt::FlatCap   },
                                             {"SquareCap", Qt::SquareCap },
                                             {"RoundCap",  Qt::RoundCap  } };

    shape->setPenCapStyle(map[capStyle]);

    update();
}


void ShapeWindow::changePenJoinStyle(QString joinStyle)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    std::map<QString, Qt::PenJoinStyle> map  { {"MiterJoin", Qt::MiterJoin},
                                               {"BevelJoin", Qt::BevelJoin},
                                               {"RoundJoin", Qt::RoundJoin} };
    shape->setPenJoinStyle(map[joinStyle]);

    update();
}


void ShapeWindow::changeBrushColor(QString color)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    shape->setBrushColor(QColor(color));

    update();
}


void ShapeWindow::changeBrushStyle(QString style)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };

    std::map<QString, Qt::BrushStyle> map { {"SolidPattern", Qt::SolidPattern},
                                            {"HorPattern",   Qt::HorPattern  },
                                            {"VerPattern",   Qt::VerPattern  },
                                            {"NoBrush",      Qt::NoBrush     } };
    shape->setBrushStyle(map[style]);

    update();
}




// ****  Change Text settings  ****

void ShapeWindow::changeText(QString txt)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    text->setText(txt);

    update();
}


void ShapeWindow::changeTextPointSize(int pointSize)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    text->getFont().setPointSize(pointSize);

    update();
}


// changed by pen.
//void ShapeWindow::changeTextColor(QString color){}


void ShapeWindow::changeTextAllignment(QString alignment)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    std::map <QString, qFlag> map { {"AlignLeft",   qFlag::AlignLeft  },
                                    {"AlignRight",  qFlag::AlignRight },
                                    {"AlignTop",    qFlag::AlignTop   },
                                    {"AlignBottom", qFlag::AlignBottom},
                                    {"AlignCenter", qFlag::AlignCenter} };
    text->setFlag(map[alignment]);

    update();
}


void ShapeWindow::changeTextFontFamily(QString fontFamily)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    text->getFont().setFamily(fontFamily);

    update();
}


void ShapeWindow::changeTextFontStyle(QString fontStyle)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    std::map<QString, QFont::Style> map { {"Normal",  QFont::Style::StyleNormal },
                                          {"Italic",  QFont::Style::StyleItalic },
                                          {"Oblique", QFont::Style::StyleOblique} };

    text->getFont().setStyle(map[fontStyle]);

    update();
}


void ShapeWindow::changeTextFontWeight(QString fontWeight)
{
    Shape* shape { shapeManager.getShape(ui->idLCD->value()) };
    Text*  text  { dynamic_cast<Text*>(shape)                };

    std::map<QString, QFont::Weight> map { {"Thin",   QFont::Weight::Thin  },
                                           {"Light",  QFont::Weight::Light },
                                           {"Normal", QFont::Weight::Normal},
                                           {"Bold",   QFont::Weight::Bold  } };

    text->getFont().setWeight(map[fontWeight]);

    update();
}

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
    //clearComboBox();
    //setupShapeEditor();
    Vector<Shape*>vector = shapeManager.getShapes();

    QString currentShape;
    currentShape=ui->allShapes->currentText();

    Vector<QPoint> pointSet;
    QPoint points;
    points.setX(10);
    points.setY(10);
    pointSet.push_back(points);


    if (currentShape == "Rectangle"){
        shapeManager.sortShapes([](Shape * a, Shape * b){return *b < *a;});

        int id = shapeManager.getShapes()[0]->getID() + 1;
        // add new rectangle
        Rectangle* add = new Rectangle(id, 10, 10, QPen(), QBrush(), 15, 15);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Rectangle");
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    } else if (currentShape == "Line"){
        int id = shapeManager.getShapes().size() + 1;
        // add new line
        Line* add = new Line(id, QPen(), QBrush(), 10, 10, 15, 15);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Line");
        //update();
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    } else if (currentShape == "Ellipse"){
        int id = shapeManager.getShapes().size() + 1;
        // add new ellipse
        Ellipse* add = new Ellipse(id, pointSet, 10, 10);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Ellipse");
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    } else if (currentShape == "Polygon"){
        int id = shapeManager.getShapes().size() + 1;
        // add new polygon
        Polygon* add = new Polygon(id, QPen(), QBrush(), pointSet, 5);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Polygon");
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    } else if (currentShape == "Polyline"){
        int id = shapeManager.getShapes().size() + 1;
        // add new polyline
        Polyline* add = new Polyline(id, pointSet);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Polyline");
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    } else if (currentShape == "Text"){
        int id = shapeManager.getShapes().size() + 1;
        // add new text
        QFont font;
        font.setWeight(QFont::Weight::Thin);
        font.setStyle(QFont::Style::StyleNormal);
        //font.setFamilies();
        //font.set
        Text* add = new Text(id, pointSet, 10, 10, "Default Text", font, Qt::AlignmentFlag::AlignCenter);
        //vector.push_back(add);
        shapeManager.addShape(add);
        ui->shapeComboBox->addItem(QString::number(id) + ": Text");
        //shapeManager.drawShapes();
        //clearComboBox();
        //setupShapeEditor();
    }
    //setupShapeEditor();
    ui->addOrDelete->setText(" is Added.");
}


void ShapeWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Delete", "Are you sure you want to delete?"/*OPTIONAL: , QMessageBox::YES | QMessageBox::NO*/);
        if (reply == QMessageBox::Yes){
            QString ids = ui->selectedShapes->currentText();
            int currentId = 0;
            currentId = ids.toInt();
            shapeManager.removeShape(currentId);
            ui->addOrDelete->setText(" is Deleted.");
            //getSelectedShape();
            QString targetID;
            for (int i = 0; i < (ui->shapeComboBox->count()); i++){
                targetID = ui->shapeComboBox->itemText(i);
                if (targetID[0] == QString::number(currentId)){

                    ui->shapeComboBox->removeItem(i);
                }
            }
        }
}


void ShapeWindow::on_allShapes_currentTextChanged(const QString &arg1)
{
    ui->shapeName->setText(arg1);


    QString currentShape;
    currentShape=ui->allShapes->currentText();

    if (currentShape == "Polygon"){
        ui->selectedShapes->addItem("Here are the Polygon");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Polygon){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }   else if (currentShape == "Ellipse")
    {
        ui->selectedShapes->addItem("Here are the Ellipse");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Ellipse || shape->getShape() == Shape::ShapeType::Circle){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }   else if (currentShape == "Line")
    {
        ui->selectedShapes->addItem("Here are the Line");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Line){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }   else if (currentShape == "Polyline")
    {
        ui->selectedShapes->addItem("Here are the Polyline");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Polyline){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }   else if (currentShape == "Rectangle")
    {
        ui->selectedShapes->addItem("Here are the Rectangle");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Rectangle || shape->getShape() == Shape::ShapeType::Square){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }   else if (currentShape == "Text")
    {
        ui->selectedShapes->addItem("Here are the Text");
        for (auto shape : shapeManager.getShapes()){
            if (shape->getShape() == Shape::ShapeType::Text){
                ui->selectedShapes->addItem(QString::number(shape->getID()));
            }
        }
    }
}
