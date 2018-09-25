#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H
#include "GradeBook.h"
#include <QtGui>
#include <QtCore>

#include <QDialog>

namespace Ui {
class CourseDialog;
}
class QListWidgetItem;
class CourseDialog : public QDialog
{
    Q_OBJECT
    
public:
    bool wasCancelled;
    int courseCount;
    int semesterID;

    explicit CourseDialog(QWidget *parent = 0);
    ~CourseDialog();
    void setCurrentClass(Class currClass);
    Class getCurrentClass();
    
private slots:
    void on_cancleButton_clicked();

    void on_okButton_clicked();

    void on_addTaButton_clicked();

    void on_removeTaButton_clicked();

    void on_addStudentButton_clicked();

    void on_removeStudentButton_clicked();

    void on_gradeReleasedRadioButton_toggled(bool checked);

private:
    Ui::CourseDialog *ui;
    GradeBook gradeBook;

    vector<Course> courses;
    vector<User> instructors;
    vector<User> tAs;
    vector<User> students;

    vector<User> selectedTAs;
    vector<User> selectedStudents;
    vector<QListWidgetItem*> itemsTA;
    vector<QListWidgetItem*> itemsStudents;

    Class currentClass;
    bool isEditing;

    void refreshTAList();
    void refreshStudentList();
};

#endif // COURSEDIALOG_H
