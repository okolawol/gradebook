#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "QtDebug"
#include <string>
#include "GradeBook.h"
using namespace std;

LogInWindow::LogInWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
    gradeBook = new GradeBook();

    ui->gradeBookLabel->setStyleSheet("QLabel { color: white }");
    ui->usernameLabel->setStyleSheet("QLabel { color: white }");
    ui->passwordLabel->setStyleSheet("QLabel { color: white }");

    ui->usernameLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->passwordLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");

    //ui->logInButton->setStyleSheet("QPushButton{ color: white; background-color: #3A5FCD; border-style: outset; border-color: white; border-width: 2px; }");
    this->setStyleSheet("QMainWindow{ background-color: #27408B }");
}

LogInWindow::~LogInWindow()
{
    delete ui;
    delete gradeBook;
}

void LogInWindow::on_logInButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();


    if(gradeBook->authenticate(username.toStdString(),password.toStdString())){
        qDebug()<<username<<"  "<<password;
        w = new MainWindow();
        w->setMainUser(gradeBook->getCurrentUser());
        w->show();
        this->close();
    }
    else{
        ui->statusLabel->setText("<font color='red'>Invalid username or password</font>");
    }

}
