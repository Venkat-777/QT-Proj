#ifndef TEXT_H
#define TEXT_H

#include "shape.h"
#include "vector.h"
#include <QFont>
#include <QString>
#include <QPoint>

using namespace MC_Vec;

class Text : public Shape
{
public:
    Text(int id = -1);
    Text(int id, Vector<QPoint> points, int length, int width,
         QString text, QFont font, Qt::AlignmentFlag flag,QPen pen, QBrush brush);
    ~Text() override;

    void draw(QPaintDevice * device, QPainter* painter) override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;

    void setText(QString text);
    void setFont(QFont font);
    void setFlag(Qt::AlignmentFlag flag);
    void setWidth(int width);
    void setLength(int length);
    void setX(int x);
    void setY(int y);

    QString& getText();
    QFont&   getFont();
    int      getWidth();
    int      getLength();
    int      getX();
    int      getY();
    Qt::AlignmentFlag getAlignment();

private:
    int width;
    int length;
    int x, y;
    QFont font;
    QString text;
    Qt::AlignmentFlag flag;
};

#endif // TEXT_H
