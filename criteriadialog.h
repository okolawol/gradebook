#ifndef CRITERIADIALOG_H
#define CRITERIADIALOG_H

#include <QDialog>
#include "Class.h"

namespace Ui {
class CriteriaDialog;
}

class CriteriaDialog : public QDialog
{
    Q_OBJECT
    
public:
    Class currentClass;
    double weightSum;

    explicit CriteriaDialog(QWidget *parent = 0);
    ~CriteriaDialog();
    void setCurrentActivity(Activity activity);
    
private slots:
    void on_cancleButton_clicked();

    void on_okButton_clicked();

private:
    Ui::CriteriaDialog *ui; 
    Activity currActivity;
    boolean isEditing;

    string weightSumCheck(double newInput, double currentSum);
    string checkDouble(string score);
    bool onlyDigits(string str);
    string checkString(string str);
};

#endif // CRITERIADIALOG_H
