#ifndef SHAPEWINDOW_H
#define SHAPEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "shapemanager.h"


namespace Ui {
class ShapeWindow;
}

class ShapeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShapeWindow(QWidget *parent = nullptr);
    ~ShapeWindow();

    void paintEvent(QPaintEvent* event);

    void setupShapeEditor();

    void getSelectedShape();

    // Forms for each shape
    void displayRectangleForm();
    void displayLineForm();
    void displayTextForm();
    void displayEllipseForm();
    void displayPolygonForm();
    void displayPolylineForm();

    // Pen & Brush settings added to form
    void displayPenBrushSettings();


    void clearForm();


    // Change Width, Height & coordinates
    void changeX(int x); // use x1
    void changeY(int y); // use y1
    void changeW(int w);
    void changeH(int h);


    // Change coordinate points
    void changeX1(int x1);
    void changeY1(int y1);
    void changeX2(int x2);
    void changeY2(int y2);
    void changeX3(int x3);
    void changeY3(int y3);
    void changeX4(int x4);
    void changeY4(int y4);


    // change Pen & Brush
    void changePenColor(QString);
    void changePenStyle(QString);
    void changePenCapStyle(QString);
    void changePenJoinStyle(QString);
    void changeBrushColor(QString);
    void changeBrushStyle(QString);

    // change text settings
    void changeText();
    void changeTextPointSize(int);
    void changeTextColor(QString);
    void changeTextAllignment(QString);
    void changeTextFontFamily(QString);
    void changeTextFontStyle(QString);
    void changeTextFontWeight(QString);

  protected:
    QComboBox* colorCombo(QColor color);
    
  private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_allShapes_currentTextChanged(const QString &arg1);

    int sortId();

private:
    Ui::ShapeWindow *ui;
    ShapeManager shapeManager;
};

#endif // SHAPEWINDOW_H
    


