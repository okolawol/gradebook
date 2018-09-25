#include "semesterdialog.h"
#include "ui_semesterdialog.h"

SemesterDialog::SemesterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SemesterDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{ background-color: #27408B }");
    ui->label->setStyleSheet("QLabel { color: #FFD700 }");
    ui->yearLabel->setStyleSheet("QLabel { color: white }");
    ui->termLabel->setStyleSheet("QLabel { color: white }");

    ui->yearLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->termLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
}

SemesterDialog::~SemesterDialog()
{
    delete ui;
}

void SemesterDialog::on_okButton_clicked()
{
    QString year = ui->yearLineEdit->text();
    QString term = ui->termLineEdit->text();

    if(year.compare("") == 0){
        //do nothing
        ui->errorLabel->setText("<font color='red'>no empty fields allowed</font>");
    }
    else if(term.compare("") == 0){
        //do nothing
        ui->errorLabel->setText("<font color='red'>no empty fields allowed</font>");
    }
    else{
        QString error = QString::fromStdString(checkDouble(year.toStdString()));
        if(error.compare("") == 0){
            gradeBook.addSemester(year.toStdString(),term.toStdString());
            this->close();
        }
        else{
            ui->errorLabel->setText("<font color='red'>"+error+"</font>");
        }
    }
}

void SemesterDialog::on_cancleButton_clicked()
{
    this->close();
}

string SemesterDialog::checkDouble(string score){
    string errorMessage = "";
    int dpCount = 0;

    char* temp = &score[0];
        for(int i = 0; i < (int)score.length(); i++)
        {
            if(temp[i] == '.')
                dpCount ++;
        }

        if(!onlyDigits(score) || dpCount > 1) // Found alphabets
        {
            errorMessage = "Non-numerical characters are not allowed for year";
            return errorMessage;
        }
        else
        {
            errorMessage = "";
            return errorMessage;
        }

}
bool SemesterDialog::onlyDigits(string str){
    size_t found = str.find_first_not_of(".0123456789");

        // Found alphabets in str
        if (found != string::npos)
        {
            return false;
        }

        else // Can't find any alphabet
        {
            return true;
        }
}
