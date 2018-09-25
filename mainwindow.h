#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GradeBook.h"
#include <QtGui>
#include <QtCore>

class LogInWindow;
class GradeWindow;
class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMainUser(User user);
    void refreshUI();
    void refreshSemesterBox();
    
private slots:
    void on_logOutButton_clicked();

    void on_addCourseButton_clicked();

    void on_classButton_clicked();

    void on_searchButton_clicked();

    void on_classSearchLineEdit_returnPressed();

    void on_deleteClassRadioButton_toggled(bool checked);

    void on_addSemesterButton_clicked();

    void on_removeSemesterButton_clicked();

    void on_semesterComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    LogInWindow *w;
    GradeWindow *w2;
    GradeBook *gradeBook;
    int courseCount;
    vector<Class> classes;
    vector<Semester> semesters;
    Semester currentSemester;
    QStringListModel* model;
    QVector<QPushButton*> buttons;
    bool classDelete;
};

#endif // MAINWINDOW_H
