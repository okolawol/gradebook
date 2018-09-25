#include "curvesdialog.h"
#include "ui_curvesdialog.h"
#include <QtDebug>

CurvesDialog::CurvesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurvesDialog)
{
    ui->setupUi(this);

    this->setStyleSheet("QDialog{ background-color: #27408B }");
    ui->label->setStyleSheet("QLabel { color: #FFD700 }");
    ui->labelBounds->setStyleSheet("QLabel { color: white }");
    ui->label_2->setStyleSheet("QLabel { color: white }");
    ui->label_3->setStyleSheet("QLabel { color: white }");
    ui->label_4->setStyleSheet("QLabel { color: white }");
    ui->label_5->setStyleSheet("QLabel { color: white }");
    ui->label_6->setStyleSheet("QLabel { color: white }");
    ui->label_7->setStyleSheet("QLabel { color: white }");
    ui->label_8->setStyleSheet("QLabel { color: white }");
    ui->label_9->setStyleSheet("QLabel { color: white }");
    ui->label_10->setStyleSheet("QLabel { color: white }");
    ui->label_11->setStyleSheet("QLabel { color: white }");
    ui->label_12->setStyleSheet("QLabel { color: white }");
}

CurvesDialog::~CurvesDialog()
{
    delete ui;
}
void CurvesDialog::setCurrentClass(Class currClass){
    qDebug()<<"HERE";
    currentClass = currClass;
    ranges = currentClass.getLetterGradeRange();
    if(ranges.at(0) != -1){
        ui->lineEdit0->setText(QString::number(ranges.at(0)));
        ui->lineEdit1->setText(QString::number(ranges.at(1)));
        ui->lineEdit2->setText(QString::number(ranges.at(2)));
        ui->lineEdit3->setText(QString::number(ranges.at(3)));
        ui->lineEdit4->setText(QString::number(ranges.at(4)));
        ui->lineEdit5->setText(QString::number(ranges.at(5)));
        ui->lineEdit6->setText(QString::number(ranges.at(6)));
        ui->lineEdit7->setText(QString::number(ranges.at(7)));
        ui->lineEdit8->setText(QString::number(ranges.at(8)));
        ui->lineEdit9->setText(QString::number(ranges.at(9)));
        ui->lineEdit10->setText(QString::number(ranges.at(10)));
    }
    lineEdits.push_back(ui->lineEdit0);
    lineEdits.push_back(ui->lineEdit1);
    lineEdits.push_back(ui->lineEdit2);
    lineEdits.push_back(ui->lineEdit3);
    lineEdits.push_back(ui->lineEdit4);
    lineEdits.push_back(ui->lineEdit5);
    lineEdits.push_back(ui->lineEdit6);
    lineEdits.push_back(ui->lineEdit7);
    lineEdits.push_back(ui->lineEdit8);
    lineEdits.push_back(ui->lineEdit9);
    lineEdits.push_back(ui->lineEdit10);
}

Class CurvesDialog::getCurrentClass(){
    return currentClass;
}

void CurvesDialog::on_cancleButton_clicked()
{
    this->close();
}

void CurvesDialog::on_okButton_clicked()
{
    boolean empty = false;
    vector<double> inputs;
    QString error = "";

    for(int i=0; i< (int)lineEdits.size(); i++){
        QLineEdit* lEdit = lineEdits.at(i);
        QString value = lEdit->text();


        if(lEdit->text().compare("") == 0){
            empty = true;
            break;
        }
        else if(error.compare("") != 0){
            break;
        }
        else{
            error = QString::fromStdString(checkDouble(value.toStdString()));
            inputs.push_back(lEdit->text().toDouble());
        }
    }



    if(empty){
        //error message
        ui->errorLabel->setText("<font color='red'>Cannot have empty field</font>");
    }
    else if(error.compare("") != 0){
        ui->errorLabel->setText("<font color='red'>"+error+"</font>");
    }
    else{
        QString error = QString::fromStdString(checkGrades(inputs));
        if(error.compare("") != 0){
            ui->errorLabel->setText("<font color='red'>"+error+"</font>");
        }
        else{
            currentClass.updateLetterGradeRangeOnDB(inputs);
            this->close();
        }


    }

}

string CurvesDialog::checkDouble(string score){
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
            errorMessage = "Non-numerical characters are not allowed.";
            return errorMessage;
        }
        else
        {
            errorMessage = "";
            return errorMessage;
        }
}
bool CurvesDialog::onlyDigits(string str){
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

string CurvesDialog::checkGrades(vector<double> grades){
    string errorMessage = "";
        int size = 11;
        for(int i = 0; i < size - 2; i++)
        {
            if(grades[i] <= grades[i+1])
            {
                errorMessage = "The letter grade minimum should be strictly higher than the previous letter grade minimum.";
                return errorMessage;
            }

        }

        if(grades[size-1] != 0.0)
        {
            errorMessage = "The minimum for the letter grade 'F' must start from 0.";
            return errorMessage;
        }

        else if(grades[0] > 100)
        {
            errorMessage = "The minimum for the letter grade 'A+' must be less than 100.";
            return errorMessage;
        }

        errorMessage = "";
        return errorMessage;
}
