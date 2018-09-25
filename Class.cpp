#include "Class.h"
#include "QtDebug"

using namespace std;


Class::Class() {
}

Class::Class(int newClassID, string newClassSection, int newCourseID, int newSemesterID, DatabaseIF* db) {
    this->db = db;

    classID = newClassID;
	classSection = newClassSection;
	courseID = newCourseID;
    semesterID = newSemesterID;
    letterGradeReleased = false;


    vector< vector<string> > results;
    results = db->selectLetterGradeRange(classID);
    //qDebug()<<QString::fromStdString(results[0][1]);
    if(results.empty()){
        for (int i = 0; i < 11; i++) {
            letterGradeRange.push_back(-1);
        }
        db->insertLetterGradeRange(classID,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
    }
    else{
        for(int i=1; i< (int)results[0].size(); i++){
            string out = results[0][i];
            double out2 = atof(out.c_str());
            letterGradeRange.push_back(out2);
        }
    }



}

Class::~Class() {
}

void Class::setClassID (int new_ClassID) {
	classID = new_ClassID;
}
int Class::getClassID() {
    return classID;
}
int Class::getCourseID(){
    return courseID;
}
void Class::setCourseID(int newID){
    courseID = newID;
}

void Class::setInstructor (Instructor new_instructor) {
	instructor = new_instructor;
}

void Class::addStudent (Student student) {
	students.push_back(student);
}

//void Class::removeStudent (int studentID) {
    //cout << "removeStudent skeleton" << endl;
//}

void Class::addTA (TA ta) {
	TAs.push_back(ta);
}
vector<TA> Class::getTAs(){
    return TAs;
}

//void Class::removeTA (int TANum) {
    //cout << "removeStudent skeleton" << endl;
//}

Instructor Class::getInstructor() {
	return instructor;
}

string Class::getClassSection(){
    return classSection;
}
void Class::setClassSection(string newSection){
    classSection = newSection;
}

Student Class::getStudent(string studentID) {
	Student studentInfoToReturn;
	if ((students.empty()) == false) {
        for (int i = 0; i < (int)students.size(); i++) {
            Student temp = students.at(i);
            if ((temp.getID()).compare(studentID) == 0) {
                studentInfoToReturn = students.at(i);
				break;
			}
		}
	}
	return studentInfoToReturn;
}

vector<Student> Class::getStudents() {
	return students;
}

void Class::setSemester (Semester new_semester) {
	semester = new_semester;
}
int Class::getSemesterID(){
    return semesterID;
}

Semester Class::getSemester() {
	return semester;
}

void Class::setClassName(string new_className) {
	className = new_className;
}

string Class::getClassName() {
	return className;
}

void Class::addActivity(string activity, double weight, double maxMark){
    DatabaseIF db;
    db.insertActivity(classID,activity,maxMark,weight);
}
void Class::deleteActivity(int activityID){
    DatabaseIF db;
    db.deleteActivity(activityID);
}
void Class::updateActivity(int activityID, int classId, string activity, double maxMark, double weight){
    DatabaseIF db;
    db.updateActivity(activityID,classId,activity,maxMark,weight);
}

//void Class::setGrade(int studentID, int activityID, int mark) {
    //cout << "setGrade stkeleton" << endl;
//}

Grade Class::getGrade (int studentID) {
    DatabaseIF db;

    Grade grade;
    grade.setStudentID(studentID);
    grade.setClassID(classID);

    vector< vector<string> > results = db.selectActivityInClass(classID);

    for(int i=0; i<(int)results.size(); i++){
        string activityId = results[i][0];
        //string classId = results[i][1];
        string activityName = results[i][2];
        string maxMark = results[i][3];
        string weight = results[i][4];


        Activity activity;
        int actID = atoi(activityId.c_str());
        int maxMarkInt = atoi(maxMark.c_str());
        double weightD = atof(weight.c_str());

        stringstream ss;
        ss << studentID;
        string studentId = ss.str();

        vector< vector<string> > gradeResults = db.selectGrade(studentId,actID);
        if(!gradeResults.empty()){
            string mark = gradeResults[0][2];
            double markInt = atof(mark.c_str());
            activity.setMark(markInt);
        }
        else{
            activity.setMark(0);
        }

        activity.setActivityID(actID);
        activity.setName(activityName);
        activity.setMaxMark(maxMarkInt);
        activity.setWeight(weightD);

        grade.addActivity(activity);
    }

    //qDebug()<<QString::fromStdString(maxMark);
    return grade;
}

void Class::setGrade(string studentID, int activityID, double mark){
    DatabaseIF db;
    db.insertGrade(studentID, activityID,mark);
}

bool Class::getLetterGradeReleased() {
    return letterGradeReleased;
}

void Class::setLetterGradeReleased(bool newLetterGradeReleased) {
    if(newLetterGradeReleased){
        db->letterGradeReleased(classID,1);
    }
    else{
        db->letterGradeReleased(classID,0);
    }
    letterGradeReleased = newLetterGradeReleased;
}

vector<double> Class::getLetterGradeRange() {
    return letterGradeRange;
}

bool Class::updateLetterGradeRangeOnDB(vector<double> newLetterGradeRange) {
    letterGradeRange = newLetterGradeRange;
    DatabaseIF accessDB;
    bool result = accessDB.updateLetterGradeRange(classID, newLetterGradeRange[0], newLetterGradeRange[1], newLetterGradeRange[2], newLetterGradeRange[3], newLetterGradeRange[4], newLetterGradeRange[5], newLetterGradeRange[6], newLetterGradeRange[7], newLetterGradeRange[8], newLetterGradeRange[9], newLetterGradeRange[10]);
    return result;
}

