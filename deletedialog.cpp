#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{ background-color: #27408B }");
    ui->label->setStyleSheet("QLabel { color: white }");
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::on_yesPushButton_clicked()
{
    choice = true;
    this->close();
}

void DeleteDialog::on_noPushButton_clicked()
{
    choice = false;
    this->close();
}

bool DeleteDialog::getChoice(){
    return choice;
}
