#include "criteriadialog.h"
#include "ui_criteriadialog.h"
#include <QtDebug>

CriteriaDialog::CriteriaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CriteriaDialog)
{
    ui->setupUi(this);
    isEditing = false;

    this->setStyleSheet("QDialog{ background-color: #27408B }");
    ui->dialogLabel->setStyleSheet("QLabel { color: #FFD700 }");
    ui->activtiyNameLabel->setStyleSheet("QLabel { color: white }");
    ui->weightLabel->setStyleSheet("QLabel { color: white }");
    ui->maxMarkLabel->setStyleSheet("QLabel { color: white }");
    ui->label3->setStyleSheet("QLabel { color: white }");

    ui->activityNameLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->activityWeightLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->maxMarkLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
}

CriteriaDialog::~CriteriaDialog()
{
    delete ui;
}

void CriteriaDialog::on_cancleButton_clicked()
{
    this->close();
}

void CriteriaDialog::setCurrentActivity(Activity activity){
    currActivity = activity;
    isEditing = true;

    QString actName = QString::fromStdString(activity.getName());
    QString actWeight = QString::number(activity.getWeight());
    QString actMaxMark = QString::number(activity.getMaxMark());

    ui->activityNameLineEdit->setText(actName);
    ui->activityWeightLineEdit->setText(actWeight);
    ui->maxMarkLineEdit->setText(actMaxMark);

    ui->dialogLabel->setText("EDIT ACTIVITY");
}

void CriteriaDialog::on_okButton_clicked()
{

    QString activityName = ui->activityNameLineEdit->text();
    QString activityWeight = ui->activityWeightLineEdit->text();
    QString activityMaxMark = ui->maxMarkLineEdit->text();

    if(activityName.compare("")==0){
        ui->errorLabel->setText("<font color='red'>must have activity name</font>");
    }
    else if(activityWeight.compare("")==0){
         ui->errorLabel->setText("<font color='red'>must have activity weight</font>");
    }
    else if(activityMaxMark.compare("")==0){
         ui->errorLabel->setText("<font color='red'>must have max mark</font>");
    }
    else{
        QString error = QString::fromStdString(weightSumCheck(activityWeight.toDouble(),weightSum));
        QString error2 = QString::fromStdString(checkDouble(activityWeight.toStdString()));
        QString error3 = QString::fromStdString(checkDouble(activityMaxMark.toStdString()));
        QString error4 = QString::fromStdString(checkString(activityName.toStdString()));

        if(error.compare("") != 0){
            ui->errorLabel->setText("<font color='red'>"+error+"</font>");
        }
        else if(error2.compare("") != 0){
             ui->errorLabel->setText("<font color='red'>"+error2+"</font>");
        }
        else if(error3.compare("") != 0){
             ui->errorLabel->setText("<font color='red'>"+error3+"</font>");
        }
        else if(error4.compare("") != 0){
            ui->errorLabel->setText("<font color='red'>"+error4+"</font>");
        }
        else{
            if(!isEditing){
                currentClass.addActivity(activityName.toStdString(),activityWeight.toDouble(),activityMaxMark.toDouble());
                this->close();
            }
            else{
                int activityID = currActivity.getActivityID();
                int classID = currentClass.getClassID();
                currentClass.updateActivity(activityID,classID,activityName.toStdString()
                                            ,activityMaxMark.toDouble(),activityWeight.toDouble());
                this->close();
            }
        }

    }


}

string CriteriaDialog::weightSumCheck(double newInput,double currentSum){
    double testSum = currentSum + newInput;
    if(testSum <= 100){
        return "";
    }
    else{
        return "ERROR,weight of all activities must not exceed 100%";
    }
}
string CriteriaDialog::checkDouble(string score){
    string errorMessage = "";
        int dpCount = 0;

        char* temp = &score[0];
        for(int i = 0; i <(int)score.length(); i++)
        {
            if(temp[i] == '.')
                dpCount ++;
        }

        if(!onlyDigits(score) || dpCount > 1) // Found alphabets
        {
            errorMessage = "Non-numerical characters are not allowed for weight/max mark";
            return errorMessage;
        }
        else
        {
            errorMessage = "";
            return errorMessage;
        }
}
bool CriteriaDialog::onlyDigits(string str){
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

string CriteriaDialog::checkString(string str){
    string errorMessage = "";
        char empty = ' ';
        int length = str.length();
        size_t found = str.find_first_not_of(" ");

        // Found something that is not space, i.e. string not empty
        if(found != string::npos)
        {
            // String starts and end with space
            if(str[0] == empty && str[length-1] == empty)
            {
                errorMessage = "activity field cannot start and end with space";
                return errorMessage;
            }
            // String starts with space
            else if(str[0] == empty)
            {
                errorMessage = "activity field cannot start with a space";
                return errorMessage;
            }

            else if(str[length-1] == empty)
            {
                errorMessage = "activtiy field cannot end with a space";
                return errorMessage;
            }

            errorMessage = "";
            return errorMessage;
        }


        else
        {
            // string is completely empty
            errorMessage = "Field cannot be completely empty";
            return errorMessage;
        }
}
