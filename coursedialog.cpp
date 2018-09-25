#include "coursedialog.h"
#include "ui_coursedialog.h"
#include <QtDebug>


CourseDialog::CourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseDialog)
{
    ui->setupUi(this);

    this->setStyleSheet("QDialog{ background-color: #27408B }");
    ui->addClass->setStyleSheet("QLabel { color: #FFD700 }");
    ui->courseName->setStyleSheet("QLabel { color: #FFD700 }");
    ui->sectionID->setStyleSheet("QLabel { color: #FFD700 }");
    ui->selectInstructor->setStyleSheet("QLabel { color: #FFD700 }");
    ui->selectTa->setStyleSheet("QLabel { color: #FFD700 }");
    ui->registeredTa->setStyleSheet("QLabel { color: white }");
    ui->inClassTa->setStyleSheet("QLabel { color: white }");
    ui->selectStudents->setStyleSheet("QLabel { color: #FFD700 }");
    ui->registeredStudents->setStyleSheet("QLabel { color: white }");
    ui->inClassStudents->setStyleSheet("QLabel { color: white }");

    ui->sectionLineEdit->setStyleSheet("QLineEdit{ border-width: 3px; border-color: #4169E1; border-style: outset; }");
    ui->allTaList->setStyleSheet("QListWidget{ border-width: 3px; border-color: #4169E1; border-style: outset;  }");
    ui->selectedTaList->setStyleSheet("QListWidget{ border-width: 3px; border-color: #6959CD; border-style: outset;  }");
    ui->allStudentList->setStyleSheet("QListWidget{ border-width: 3px; border-color: #4169E1; border-style: outset;  }");
    ui->selectedStudentList->setStyleSheet("QListWidget{ border-width: 3px; border-color: #6959CD; border-style: outset;  }");
    ui->gradeReleasedRadioButton->setStyleSheet("QRadioButton{ color: white }");


    wasCancelled = false;
    courseCount = 0;

    isEditing = false;
    ui->gradeReleasedRadioButton->setEnabled(false);

    courses = gradeBook.getCourses();
    for(int i = 0; i<(int)courses.size(); i++){
        Course tempCourse = courses.at(i);

        QString courseName = QString::fromStdString(tempCourse.getCourseName());

        ui->courseComboBox->addItem(courseName);
    }



    instructors = gradeBook.getUsers(1);
    for(int i = 0; i< (int)instructors.size(); i++){
        User tempUser = instructors.at(i);

        QString firstname = QString::fromStdString(tempUser.getFirstName());
        QString lastname = QString::fromStdString(tempUser.getLastName());
        QString userID = QString::fromStdString(tempUser.getID());

        ui->instructorComboBox->addItem(firstname+" "+lastname+"   ID:| "+userID);
    }


    tAs = gradeBook.getUsers(2);
    for(int i = 0; i<(int)tAs.size(); i++){
        User tempTa = tAs.at(i);

        QString firstname = QString::fromStdString(tempTa.getFirstName());
        QString lastname = QString::fromStdString(tempTa.getLastName());
        QString userID = QString::fromStdString(tempTa.getID());
        QString userType = QString::fromStdString(tempTa.getUserType());

        ui->allTaList->addItem(firstname+" "+lastname+"   ID:| "+userID+"     TYPE:|"+userType);
    }
    ui->allTaList->setCurrentRow(0);



    students = gradeBook.getUsers(3);
    for(int i = 0; i<(int)students.size(); i++){
        User tempStudent = students.at(i);

        QString firstname = QString::fromStdString(tempStudent.getFirstName());
        QString lastname = QString::fromStdString(tempStudent.getLastName());
        QString userID = QString::fromStdString(tempStudent.getID());
        QString userType = QString::fromStdString(tempStudent.getUserType());

        ui->allStudentList->addItem(firstname+" "+lastname+"   ID:| "+userID+"     TYPE:|"+userType);
    }
    ui->allStudentList->setCurrentRow(0);

}

CourseDialog::~CourseDialog()
{
    delete ui;
}

void CourseDialog::on_cancleButton_clicked()
{

    wasCancelled = true;
    this->close();

}

void CourseDialog::on_okButton_clicked()
{
    Course selectedCourse;
    int currIndex = ui->courseComboBox->currentIndex();
    selectedCourse = courses.at(currIndex);

    QString sectionID = ui->sectionLineEdit->text();
    int classID;

    if(!isEditing){
        classID = gradeBook.addClass(sectionID.toStdString(),selectedCourse.getCourseID(),semesterID);

    }
    else{
        classID = currentClass.getClassID();
        gradeBook.updateClass(classID,sectionID.toStdString(),selectedCourse.getCourseID(),currentClass.getSemesterID());
    }




    User selectedInstructor;
    currIndex = ui->instructorComboBox->currentIndex();
    selectedInstructor = instructors.at(currIndex);

    gradeBook.addUserToClass(selectedInstructor.getID(),classID);



    for(int i=0; i<(int)selectedTAs.size(); i++){
        User temp = selectedTAs.at(i);
        gradeBook.addUserToClass(temp.getID(),classID);
    }
    for(int i=0; i<(int)selectedStudents.size(); i++){
        User temp = selectedStudents.at(i);
        gradeBook.addUserToClass(temp.getID(),classID);
    }
    wasCancelled = false;
    this->close();
}

void CourseDialog::setCurrentClass(Class currClass){
    currentClass = currClass;
    isEditing = true;

    ui->addClass->setText("EDIT CLASS");
    ui->gradeReleasedRadioButton->setEnabled(true);

    ui->courseComboBox->setCurrentIndex(currentClass.getCourseID()-1);
    ui->sectionLineEdit->setText(QString::fromStdString(currentClass.getClassSection()));


    Instructor tempIns = currentClass.getInstructor();
    for(int i=0 ; i< (int)instructors.size(); i++){
        User tempIns2 = instructors.at(i);
        if(tempIns2.getID().compare(tempIns.getID()) == 0){
            ui->instructorComboBox->setCurrentIndex(i);
            break;
        }
    }


    vector<TA> tAs = currentClass.getTAs();
    for(int i=0; i< (int)tAs.size(); i++){
        TA tempTA = tAs.at(i);
        selectedTAs.push_back(tempTA);
    }
    refreshTAList();

    vector<Student> students = currentClass.getStudents();
    for(int i=0; i< (int)students.size(); i++){
        Student tempStd = students.at(i);
        selectedStudents.push_back(tempStd);
    }
    refreshStudentList();

    ui->gradeReleasedRadioButton->setChecked(currentClass.getLetterGradeReleased());
}

Class CourseDialog::getCurrentClass(){
    return currentClass;
}

void CourseDialog::on_addTaButton_clicked()
{
    boolean exists = false;
    User selTA = tAs.at(ui->allTaList->currentRow());

    for(int i = 0; i <(int)selectedTAs.size();i++){
        User temp = selectedTAs.at(i);
        if(selTA.getID().compare(temp.getID()) == 0){
            exists = true;
            break;
        }
    }
    if(exists){
       //do nothing
    }
    else{
        selectedTAs.push_back(selTA);
        refreshTAList();
    }

}

void CourseDialog::on_removeTaButton_clicked()
{
    if(!selectedTAs.empty()){
        int currSelected = ui->selectedTaList->currentRow();

        if(isEditing){
            User selTa = selectedTAs.at(currSelected);
            gradeBook.removeUserFromClass(selTa.getID(),currentClass.getClassID());
        }

        vector<User>::iterator i = selectedTAs.begin()+currSelected;
        selectedTAs.erase(i);
        refreshTAList();
        //qDebug() << currSelected;
    }

}

void CourseDialog::on_addStudentButton_clicked()
{
    boolean exists = false;
    User selStudent = students.at(ui->allStudentList->currentRow());

    for(int i=0; i< (int)selectedStudents.size();i++){
        User temp = selectedStudents.at(i);
        if(selStudent.getID().compare(temp.getID()) == 0){
            exists = true;
            break;
        }
    }
    if(exists){
        //do nothing
    }
    else{
        selectedStudents.push_back(selStudent);
        refreshStudentList();
    }
}
void CourseDialog::on_removeStudentButton_clicked()
{
    if(!selectedStudents.empty()){
        int currSelected = ui->selectedStudentList->currentRow();

        if(isEditing){
            User selStudent = selectedStudents.at(currSelected);
            gradeBook.removeUserFromClass(selStudent.getID(),currentClass.getClassID());
        }

        vector<User>::iterator i = selectedStudents.begin()+currSelected;
        selectedStudents.erase(i);
        refreshStudentList();
    }
}

void CourseDialog::refreshTAList(){
    for(int i=0; i< (int)itemsTA.size(); i++){
        ui->selectedTaList->removeItemWidget(itemsTA.at(i));
        delete itemsTA.at(i);
    }
    itemsTA.clear();

    for(int i=0; i < (int)selectedTAs.size(); i++){

        User selTA = selectedTAs.at(i);

        QString taName = QString::fromStdString(selTA.getFirstName());
        QString taLast = QString::fromStdString(selTA.getLastName());
        QString userID = QString::fromStdString(selTA.getID());
        QString userType = QString::fromStdString(selTA.getUserType());

        QListWidgetItem* qw = new QListWidgetItem(taName+" "+taLast+"   ID:| "+userID+"     TYPE:|"+userType);
        ui->selectedTaList->addItem(qw);
        itemsTA.push_back(qw);
    }
    ui->selectedTaList->setCurrentRow(0);
}


void CourseDialog::refreshStudentList(){
    for (int i=0; i< (int)itemsStudents.size(); i++){
        ui->selectedStudentList->removeItemWidget(itemsStudents.at(i));
        delete itemsStudents.at(i);
    }
    itemsStudents.clear();

    for(int i=0; i < (int)selectedStudents.size();i++){
        User selStudent = selectedStudents.at(i);

        QString stdName = QString::fromStdString(selStudent.getFirstName());
        QString stdLast = QString::fromStdString(selStudent.getLastName());
        QString userID = QString::fromStdString(selStudent.getID());
        QString userType = QString::fromStdString(selStudent.getUserType());

        QListWidgetItem* qw = new QListWidgetItem(stdName+" "+stdLast+"   ID:| "+userID+"     TYPE:|"+userType);
        ui->selectedStudentList->addItem(qw);
        itemsStudents.push_back(qw);
    }
    ui->selectedStudentList->setCurrentRow(0);
}

void CourseDialog::on_gradeReleasedRadioButton_toggled(bool checked)
{
    if(checked){
        currentClass.setLetterGradeReleased(checked);
    }
    else{
        currentClass.setLetterGradeReleased(checked);
    }
}
