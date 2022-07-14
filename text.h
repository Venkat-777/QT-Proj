#ifndef TEXT_H
#define TEXT_H

#include "shape.h"
#include <string>

class Text : public Shape
{
public:
    Text(QPaintDevice * device = nullptr, int id = -1);
    ~Text() override;

    void draw(QPaintDevice * device) override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;

    void setText(QString text);
    void setFont(QFont font);
    void setFlag(Qt::AlignmentFlag flag);
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);

    QString getText();
    QFont getFont();
    int getWidth();
    int getHeight();
    int getX();
    int getY();

private:
    int width;
    int height;
    int x, y;
    QFont font;
    QString text;
    Qt::AlignmentFlag flag;


};

#endif // TEXT_H
