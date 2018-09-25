#ifndef SEMESTERDIALOG_H
#define SEMESTERDIALOG_H

#include <QDialog>
#include "GradeBook.h"

namespace Ui {
class SemesterDialog;
}

class SemesterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SemesterDialog(QWidget *parent = 0);
    ~SemesterDialog();
    
private slots:
    void on_okButton_clicked();

    void on_cancleButton_clicked();

private:
    Ui::SemesterDialog *ui;
    GradeBook gradeBook;

    string checkDouble(string score);
    bool onlyDigits(string str);
};

#endif // SEMESTERDIALOG_H
