#ifndef GRADEWINDOW_H
#define GRADEWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "Class.h"

class MainWindow;
class QListWidgetItem;
namespace Ui {
class GradeWindow;
}

class GradeWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GradeWindow(QWidget *parent = 0);
    ~GradeWindow();
    void setCurrentClass(Class curClass);
    void updateGrades(int studentID);
    void setCurrentUser(User user);
    
private slots:
    void on_backButton_clicked();

    void on_newCriteriaButton_clicked();

    void on_curveButton_clicked();

    void on_studentListWidget_itemClicked(QListWidgetItem *item);

    void on_studentListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_activityTableView_doubleClicked(const QModelIndex &index);

    void setGradeToDB(QWidget*);

    void on_deleteActivityButton_clicked();

    void on_activityTableView_clicked(const QModelIndex &index);

    void on_editActivityButton_clicked();

    void on_editCourseButton_clicked();

private:
    Ui::GradeWindow *ui;
    MainWindow *w;

    Class currentClass;
    User currentUser;

    int currentStudentID;
    double weightSum;

    vector<Activity> activities;
    QStandardItemModel *model;
    QAbstractItemDelegate *it;
    QModelIndex currIndex;

    string getLetterGrade(Grade grade, vector<double> letterGradeRange);
    string checkExceedMax(double newMark, Activity currAct);
    bool studentUsing;
};

#endif // GRADEWINDOW_H
