#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "coursedialog.h"
#include "gradewindow.h"
#include "semesterdialog.h"
#include <QMessageBox>
#include "deletedialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gradeBook = new GradeBook();

    semesters = gradeBook->getSemesters();
    refreshSemesterBox();

    if(!semesters.empty()){
        classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
        refreshUI();
    }
    classDelete = false;

    this->setStyleSheet("QMainWindow{ background-color: #27408B }");
    ui->userInfo->setStyleSheet("QLabel { color: white }");
    ui->welcome->setStyleSheet("QLabel { color: #FFD700}");
    ui->classSearchLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->deleteClassRadioButton->setStyleSheet("QRadioButton{ color: white }");

    ui->scrollArea->setStyleSheet("QScrollArea{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->changeSemesterLabel->setStyleSheet("QLabel { color: white }");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gradeBook;
}

void MainWindow::setMainUser(User user){
    gradeBook->setCurrentUser(user);

    QString firstName = QString::fromStdString(user.getFirstName());
    QString lastName = QString::fromStdString(user.getLastName());
    QString email = QString::fromStdString(user.getEmail());
    QString userType = QString::fromStdString(user.getUserType());

    ui->userInfo->setText(firstName+" "+lastName
                          +"\n"+email
                          +"\n"+userType+" view");
    ui->welcome->setText("Welcome "+firstName);

    if(userType.compare("admin") != 0){

        ui->addSemesterButton->setEnabled(false);
        ui->removeSemesterButton->setEnabled(false);
        ui->deleteClassRadioButton->setEnabled(false);
        ui->addCourseButton->setEnabled(false);
    }
}

void MainWindow::on_logOutButton_clicked()
{

    w = new LogInWindow();
    w->show();
    this->close();

}

void MainWindow::on_addCourseButton_clicked()
{
    if(semesters.empty()){
        QMessageBox::information(this,"CANNOT CREATE CLASS","You have to create a semester first");
    }
    else{
        CourseDialog d;
        d.setModal(true);
        d.courseCount = courseCount;
        d.semesterID = currentSemester.getSemesterID();
        d.exec();

        gradeBook->reOpenDatabaseConnection();
        classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
        refreshUI();
    }
}

void MainWindow::refreshUI(){

    for(int i=0 ; i< (int)buttons.size(); i++){
        ui->gridLayout->removeWidget(buttons.at(i));
        delete buttons.at(i);
        qApp->processEvents();
    }
    buttons.clear();



    if(classes.empty()){
        courseCount = 0;
    }
    else{
        courseCount = (int)classes.size();
        int row = 1;
        int column = 0;

        for(int i=0; i< (int)classes.size(); i++){
            Class tempClass = classes.at(i);

            QString className =QString::fromStdString(tempClass.getClassName());
            QString firstName = QString::fromStdString(tempClass.getInstructor().getFirstName());
            QString lastName = QString::fromStdString(tempClass.getInstructor().getLastName());
            QString sectionID = QString::fromStdString(tempClass.getClassSection());

            QPushButton *button = new QPushButton();
            button->setText(className+"\n"
                            +"Section: "+sectionID+"\n"
                            +"Instructor: "+firstName+" "+lastName);

            connect(button,SIGNAL(clicked()),this,SLOT(on_classButton_clicked()));
            //button->setStyleSheet("QPushButton{ color: white; background-color: #006400; border-style: outset; border-color: white; border-width: 2px; }");
            buttons.push_back(button);

            ui->gridLayout->addWidget(button,row,column);

            column++;
            if(column == 5){
                row++;
                column = 0;
            }

        }
    }
}

void MainWindow::refreshSemesterBox(){

    model = new QStringListModel(this);
    QStringList list;

    for(int i=0; i< (int)semesters.size(); i++){
        Semester temp = semesters.at(i);
        currentSemester = temp;

        int year = temp.getYear();
        QString term = QString::fromStdString(temp.getTerm());

        list.append(term+" "+QString::number(year));
    }
    model->setStringList(list);

    ui->semesterComboBox->setModel(model);
}

void MainWindow::on_classButton_clicked()
{
    Class selectedClass;
    QPushButton *button = (QPushButton*)QObject::sender();

    int selectedIndex = buttons.indexOf(button);
    selectedClass = classes.at(selectedIndex);

    if(classDelete){
        DeleteDialog d;
        d.setModal(true);
        d.exec();

        if(d.getChoice()){
            gradeBook->deleteClass(selectedClass);
            classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
            refreshUI();
        }
    }
    else{
        w2 = new GradeWindow();
        w2->setCurrentClass(selectedClass);

        //qDebug << QString::fromStdString(gradeBook->db->selectClassInformation((selectedClass.getClassID()))[0][0]);
        w2->setCurrentUser(gradeBook->getCurrentUser());
        w2->show();
        this->close();
    }

}


void MainWindow::on_searchButton_clicked()
{
    gradeBook->reOpenDatabaseConnection();

    QString searchString = ui->classSearchLineEdit->text();
    if(searchString.compare("") == 0){
        if(!semesters.empty()){
            classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
            refreshUI();
        }
    }
    else{
        classes = gradeBook->searchClass(searchString.toStdString());
        refreshUI();
    }

}

void MainWindow::on_classSearchLineEdit_returnPressed()
{
    on_searchButton_clicked();
}

void MainWindow::on_deleteClassRadioButton_toggled(bool checked)
{
    if(checked){
        QMessageBox::information(this,"DELETE ENABLED","remove a class by clicking it");
    }
    else{
        QMessageBox::information(this,"DELETE DISABLED","clicking a class will take you to the grading window");
    }

    classDelete = checked;
}

void MainWindow::on_addSemesterButton_clicked()
{
    SemesterDialog s;
    s.setModal(true);
    s.exec();

    gradeBook->reOpenDatabaseConnection();

    semesters = gradeBook->getSemesters();
    refreshSemesterBox();
}

void MainWindow::on_removeSemesterButton_clicked()
{
    if(!semesters.empty()){
        DeleteDialog d;
        d.setModal(true);
        d.exec();

        if(d.getChoice()){
            int currRow = ui->semesterComboBox->currentIndex();
            Semester semester = semesters.at(currRow);
            gradeBook->deleteSemester(semester.getSemesterID());

            semesters = gradeBook->getSemesters();
            refreshSemesterBox();

            if(!semesters.empty()){
                classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
                refreshUI();
            }
            else{
                classes = gradeBook->getAllClasses();
                refreshUI();
            }

        }

    }



}

void MainWindow::on_semesterComboBox_currentIndexChanged(int index)
{
    if(index == -1){
        //do nothing
    }
    else{
       currentSemester = semesters.at(index);
       classes = gradeBook->getAllClasses(currentSemester.getSemesterID());
       refreshUI();
    }
}
