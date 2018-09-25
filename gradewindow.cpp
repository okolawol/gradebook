#include "gradewindow.h"
#include "ui_gradewindow.h"
#include "mainwindow.h"
#include "criteriadialog.h"
#include "curvesdialog.h"
#include "coursedialog.h"
#include "deletedialog.h"
#include <QtDebug>
#include <sstream>

GradeWindow::GradeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GradeWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(10,4,this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Activity Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Weight"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Mark"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Max Mark"));


    ui->activityTableView->setModel(model);
    ui->activityTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    weightSum = 0;
    studentUsing = false;

    this->setStyleSheet("QMainWindow{ background-color: #27408B }");
    ui->classLabel->setStyleSheet("QLabel { color: #FFD700 }");
    ui->extraInfoLabel->setStyleSheet("QLabel { color: white }");
    ui->studentsLabel->setStyleSheet("QLabel { color: white }");
    ui->gradesLabel->setStyleSheet("QLabel { color: white }");
    ui->finalGradeLabel->setStyleSheet("QLabel { color: #FFD700 }");
    ui->studentListWidget->setStyleSheet("QListWidget{ border-width: 3px; border-color: #4169E1; border-style: outset;  }");
    ui->activityTableView->setStyleSheet("QTableView{ border-width: 3px; border-color: #6959CD; border-style: outset;  }");
}

GradeWindow::~GradeWindow()
{
    delete ui;
}

void GradeWindow::setCurrentClass(Class curClass){
    currentClass = curClass;

    QString className = QString::fromStdString(currentClass.getClassName());
    QString sectionID = QString::fromStdString(currentClass.getClassSection());

    QString profName1 = QString::fromStdString(currentClass.getInstructor().getFirstName());
    QString profName2 = QString::fromStdString(currentClass.getInstructor().getLastName());

    ui->classLabel->setText(className);
    ui->extraInfoLabel->setText("Section: "+sectionID+"\n"
                                +"Instructor: "+profName1+" "+profName2);


    vector<Student> students = currentClass.getStudents();
    for(int i=0; i< (int)students.size(); i++){
        Student tempStudent = students.at(i);

        QString firstName = QString::fromStdString(tempStudent.getFirstName());
        QString lastName = QString::fromStdString(tempStudent.getLastName());

        ui->studentListWidget->addItem(firstName+" "+lastName);
    }
    ui->studentListWidget->setCurrentRow(0);


    int selectedRow = ui->studentListWidget->currentRow();
    Student selectedStudent;
    for(int i=0 ; i< (int)students.size(); i++){
        if(i == selectedRow){
            selectedStudent = students.at(i);
            break;
        }
    }

    int studentID = atoi(selectedStudent.getID().c_str());
    updateGrades(studentID);

    ui->activityTableView->setCurrentIndex(model->index(0,0,QModelIndex()));
    currIndex = model->index(0,0,QModelIndex());
}
void GradeWindow::setCurrentUser(User user){
    currentUser = user;
    QString userType = QString::fromStdString(user.getUserType());

    if(userType.compare("admin") == 0){
        //disable nothing
    }
    else if(userType.compare("instructor") == 0){
        ui->editCourseButton->setEnabled(false);
    }
    else if(userType.compare("ta") == 0){
        ui->editCourseButton->setEnabled(false);
        ui->newCriteriaButton->setEnabled(false);
        ui->editActivityButton->setEnabled(false);
        ui->deleteActivityButton->setEnabled(false);
        ui->curveButton->setEnabled(false);
    }
    else {
        QString stdID = QString::fromStdString(user.getID());
        currentStudentID = stdID.toInt();

        vector<Student> students = currentClass.getStudents();
        for(int i=0; i< (int)students.size();i++){
            Student temp = students.at(i);
            if(temp.getID().compare(stdID.toStdString()) == 0){
                ui->studentListWidget->setCurrentRow(i);
            }
        }

        updateGrades(currentStudentID);
        studentUsing = true;

        ui->editCourseButton->setEnabled(false);
        ui->newCriteriaButton->setEnabled(false);
        ui->editActivityButton->setEnabled(false);
        ui->deleteActivityButton->setEnabled(false);
        ui->curveButton->setEnabled(false);
        ui->studentListWidget->setEnabled(false);
    }
}

void GradeWindow::on_backButton_clicked()
{
    w = new MainWindow();
    w->setMainUser(currentUser);
    w->show();
    this->close();

}

void GradeWindow::on_newCriteriaButton_clicked()
{
    CriteriaDialog c;
    c.currentClass = currentClass;
    c.weightSum = weightSum;
    c.setModal(true);
    c.exec();


    int selectedRow = 0;

    selectedRow = ui->studentListWidget->currentRow();

    vector<Student> students = currentClass.getStudents();
    Student selectedStudent;
    for(int i=0 ; i< (int)students.size(); i++){
        if(i == selectedRow){
            selectedStudent = students.at(i);
            break;
        }
    }

    int studentID = atoi(selectedStudent.getID().c_str());
    updateGrades(studentID);

    qApp->processEvents();

}

void GradeWindow::on_curveButton_clicked()
{
    CurvesDialog c2;
    c2.setModal(true);
    c2.setCurrentClass(currentClass);
    c2.exec();

    currentClass = c2.getCurrentClass();
}

void GradeWindow::on_studentListWidget_itemClicked(QListWidgetItem *item)
{


    int selectedRow = ui->studentListWidget->currentRow();

    vector<Student> students = currentClass.getStudents();
    Student selectedStudent;
    for(int i=0 ; i< (int)students.size(); i++){
        if(i == selectedRow){
            selectedStudent = students.at(i);
            break;
        }
    }

    int studentID = atoi(selectedStudent.getID().c_str());
    updateGrades(studentID);
}
void GradeWindow::updateGrades(int studentID){


    Grade grade = currentClass.getGrade(studentID);
    activities = grade.getActivities();
    currentStudentID = studentID;

    weightSum = 0;
    for(int i=0; i<(int)activities.size(); i++){
        Activity temp = activities.at(i);
        QString actName = QString::fromStdString(temp.getName());
        QString weight = QString::number(temp.getWeight());
        double mark = temp.getMark();
        int maxMark = temp.getMaxMark();

        QModelIndex index0 = model->index(i,0, QModelIndex());
        model->setData(index0,actName);

        QModelIndex index1 = model->index(i,1, QModelIndex());
        model->setData(index1,weight+"%");

        QModelIndex index2 = model->index(i,2, QModelIndex());
        model->setData(index2,mark);

        QModelIndex index3 = model->index(i,3, QModelIndex());
        model->setData(index3,maxMark);

        ui->activityTableView->resizeColumnsToContents();

        weightSum = weightSum + weight.toDouble();

    }
    if(currentClass.getLetterGradeReleased()){
        Grade grade = currentClass.getGrade(currentStudentID);
        QString finalGrade = QString::fromStdString(getLetterGrade(grade,currentClass.getLetterGradeRange()));
        ui->finalGradeLabel->setText("FINAL GRADE: "+finalGrade);
    }

}


void GradeWindow::on_studentListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

    QFont font = current->font();
    font.setBold(true);
    font.setPointSize(20);
    current->setFont(font);

    if(previous!=NULL){
        font = previous->font();
        font.setBold(false);
        font.setPointSize(9);
        previous->setFont(font);
    }


}

void GradeWindow::on_activityTableView_doubleClicked(const QModelIndex &index)
{
    if(!studentUsing){
        if(index.column() == 2){
            ui->activityTableView->edit(index);
            it = ui->activityTableView->itemDelegate();
            currIndex = index;

           connect(it,SIGNAL(closeEditor(QWidget*)),this,SLOT(setGradeToDB(QWidget*)));
        }
    }

}
void GradeWindow::setGradeToDB(QWidget *){

    QString mark = ui->activityTableView->model()->data(currIndex).toString();
    //qDebug()<<mark;

    if(mark.compare("") == 0){
        //do nothing
    }
    else{

        if(currIndex.row() < (int)activities.size()){
            Activity currAct = activities.at(currIndex.row());
            QString error = QString::fromStdString(checkExceedMax(mark.toDouble(),currAct));

            if(error.compare("") == 0){
                stringstream ss;
                ss << currentStudentID;
                string studentID = ss.str();
                //qDebug()<<QString::fromStdString(studentID);

                currentClass.setGrade(studentID,currAct.getActivityID(),mark.toDouble());

                if(currentClass.getLetterGradeReleased()){
                    //calculate final grade
                    //qDebug()<<currentStudentID;
                    Grade grade = currentClass.getGrade(currentStudentID);
                    QString finalGrade = QString::fromStdString(getLetterGrade(grade,currentClass.getLetterGradeRange()));
                    ui->finalGradeLabel->setText("FINAL GRADE: "+finalGrade);
                }
                ui->errorLabel->setText("");
            }
            else{
                ui->errorLabel->setText("<font color='red'>"+error+"</font>");
            }
        }
    }


    disconnect(it,SIGNAL(closeEditor(QWidget*)),this,SLOT(setGradeToDB(QWidget*)));
}

void GradeWindow::on_deleteActivityButton_clicked()
{
   if(currIndex.row() < (int)activities.size()){
       DeleteDialog d;
       d.setModal(true);
       d.exec();

       if(d.getChoice()){
           Activity currAct = activities.at(currIndex.row());
           currentClass.deleteActivity(currAct.getActivityID());

           model->removeRow(currIndex.row());
           updateGrades(currentStudentID);
       }
   }

}

void GradeWindow::on_activityTableView_clicked(const QModelIndex &index)
{
    currIndex = index;

    if(index.row() < (int)activities.size()){
        Activity currAct = activities.at(index.row());
        QString actName = QString::fromStdString(currAct.getName());
        ui->visualizeButton->setText("VIZUALIZE "+actName);
    }
}

void GradeWindow::on_editActivityButton_clicked()
{

     if(currIndex.row() < (int)activities.size()){
           Activity currAct = activities.at(currIndex.row());

           CriteriaDialog c;
           c.currentClass = currentClass;
           c.weightSum = weightSum;
           c.setCurrentActivity(currAct);
           c.setModal(true);
           c.exec();

           updateGrades(currentStudentID);
      }


}

void GradeWindow::on_editCourseButton_clicked()
{
    CourseDialog c;
    c.setModal(true);
    c.setCurrentClass(currentClass);
    c.exec();

    if(!c.wasCancelled){
        w = new MainWindow();
        w->setMainUser(currentUser);
        w->show();
        this->close();
    }
}

string GradeWindow::checkExceedMax(double newMark, Activity currAct){
    if((int)newMark <= currAct.getMaxMark()){
        return "";
    }
    else{
        return "ERROR! the newly entered mark must not exceed max mark";
    }
}

string GradeWindow::getLetterGrade(Grade grade, vector<double> letterGradeRange)
{
    string letterGrade = "";
    double gradePercentage = 0.0;
    vector<Activity> activities = grade.getActivities();
    double weight, mark, maxMark;
    int indexOfLetterGrade;

    if(activities.size() == 0)
    {
        letterGrade = "No Letter Grade Available";
        return letterGrade;
    }

    for(int i=0; i<(int)activities.size(); i++)
    {
        weight = activities.at(i).getWeight();
        mark = activities.at(i).getMark();
        maxMark = activities.at(i).getMaxMark();

        gradePercentage += (mark / maxMark) * weight;
    }

    //index 0 = A+, 1 = A, 2 = A-, ... , 10 = F
    for(int j=0; j<(int)letterGradeRange.size(); j++)
    {
        if(gradePercentage >= letterGradeRange.at(j))
        {
            indexOfLetterGrade = j;
            break;
        }
    }

    switch (indexOfLetterGrade)
    {
        case 0 :
            letterGrade = "A+";
            break;
        case 1 :
            letterGrade = "A";
            break;
        case 2 :
            letterGrade = "A-";
            break;
        case 3 :
            letterGrade = "B+";
            break;
        case 4 :
            letterGrade = "B";
            break;
        case 5 :
            letterGrade = "B-";
            break;
        case 6 :
            letterGrade = "C+";
            break;
        case 7 :
            letterGrade = "C";
            break;
        case 8 :
            letterGrade = "C-";
            break;
        case 9 :
            letterGrade = "D";
            break;
        case 10 :
            letterGrade = "F";
            break;
    }

    return letterGrade;
}
