#ifndef CURVESDIALOG_H
#define CURVESDIALOG_H
#include "Class.h"

#include <QDialog>

namespace Ui {
class CurvesDialog;
}

class CurvesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CurvesDialog(QWidget *parent = 0);
    ~CurvesDialog();
    void setCurrentClass(Class currClass);
    Class getCurrentClass();
    
private slots:
    void on_cancleButton_clicked();

    void on_okButton_clicked();

private:
    Ui::CurvesDialog *ui;
    Class currentClass;
    vector<double> ranges;
    vector<QLineEdit*> lineEdits;

    string checkDouble(string score);
    bool onlyDigits(string str);
    string checkGrades(vector<double> grades);
};

#endif // CURVESDIALOG_H
