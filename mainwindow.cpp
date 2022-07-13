#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/imraanarbab/Downloads/TeamLogo.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Team Email: midnightcoder@gmail.com");
    ui->label_2->setText("Team Phone Number: 949-098-5673");
}



void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "jmark" && password == "1214")
     {
        QMessageBox::information(this, "Login", "Account is valid");
    }
    else
       {
        QMessageBox::warning(this, "Login", "Account is not valid and can't be found.");
    }
}

