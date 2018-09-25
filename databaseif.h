#ifndef DATABASEIF_H
#define DATABASEIF_H

#include <QtSql>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
//NOTE: query.exec handles all kinds of SQL query
//Takes argument string by string, but does not need + to connect them

//Tables:
//Account: id, userName, password
//          (id TEXT PRIMARY KEY, userName TEXT UNIQUE, password TEXT)
//          userName is same as our computing ID
//User: id, firstName, lastName, email, type
//      (id TEXT PRIMARY KEY, firstName TEXT NOT NULL, lastName TEXT NOT NULL, email TEXT, type TEXT)
//      "type" defines student, ta or instructor
//Admin: id
//      (id TEXT PRIMARY KEY)
//Instructor: id, office, department
//      (id TEXT PRIMARY KEY, office TEXT, department TEXT)
//TA: id, office
//      (id TEXT PRIMARY KEY, office TEXT)
//Student: id, department, major
//      (id TEXT PRIMARY, department TEXT, major TEXT)
//Semester: semesterId, year, term
//      (semesterId INTEGER PRIMARY KEY, year TEXT, term TEXT)
//Course: courseId, courseName
//      (courseId INTEGER PRIMARY KEY, courseName TEXT UNIQUE)
//Class:  classId, classSection, courseId, semesterId, letterGradeReleased
//      (classId INTEGER PRIMARY KEY, classSection TEXT, courseId INTEGER, semesterId INTEGER, letterGradeReleased BIT DEFAULT 0, UNIQUE(classSection, courseId, semesterId))
//      classSection D100, D200, for multiple section class, also for tutorial
//ClassInformation: id, classId, letterGrade
//      (id TEXT, classId INTEGER, letterGrade TEXT, PRIMARY KEY(id, classId))
//Activity: activityId, classId, activity, maxMark, weight
//      (activityId INTEGER PRIMARY KEY, classId INTEGER, activity TEXT, maxMark DOUBLE, weight DOUBLE, UNIQUE(classId, activity))
//Grade: id, activityId, mark
//      (id TEXT, activityId INTEGER, mark DOUBLE, PRIMARY KEY(id, activityId))
//LetterGradeRange: classId, scale1, scale2, scale3, scale4, scale5, scale6, scale7, scale8, scale9, scale10, scale11
//      (classId INTEGER PRIMARY KEY, scale1 DOUBLE, scale2 DOUBLE, scale3 DOUBLE, scale4 DOUBLE, scale5 DOUBLE, scale6 DOUBLE, scale7 DOUBLE, scale8 DOUBLE, scale9 DOUBLE, scale10 DOUBLE, scale11 DOUBLE)

enum userType {ADMIN, INSTRUCTOR, T_A_, STUDENT};
class DatabaseIF
{
public:
    DatabaseIF();
    virtual ~DatabaseIF();

    //wildcard query function for debug
    vector< vector<string> > applyQuery(string);

    //selectAccount(string id)
    vector< vector<string> > selectAccount();  //get Account table
    vector< vector<string> > selectAccount(string); //search by id

    //select user, argument: [type][id], returns empty vector if invalid argument or no result
    vector< vector<string> > selectUser();  //get User table
    vector< vector<string> > selectUser(userType);
    vector< vector<string> > selectUser(string);    //search by id
    //special select for login page, argument: userName, password
    //************CAUTION: Althogh only one tuple should be returned, for consistent, it still return 2D vector********
    vector< vector<string> > selectUser(string, string);
    //select by type and id, return detail information
    vector< vector<string> > selectUser(userType, string);

    //insertSemester(string year, string term)
    int insertSemester(string, string);    //return semesterId
    //selectSemester(int semesterId)
    vector< vector<string> > selectSemester();  //get Semester table
    vector< vector<string> > selectSemester(int);   //search by id
    //updateSemester(int semesterId, string year, string term);
    bool updateSemester(int, string, string);
    //deleteSemester(int semesterId)
    //deleteSemesterTrigger will delete corresponding tuples in Class table
    bool deleteSemester(int);

    //selectCourse(int courseId)
    //selectCourse(string courseName)
    vector< vector<string> > selectCourse();  //get Course table
    vector< vector<string> > selectCourse(int);   //search by courseId
    vector< vector<string> > selectCourse(string);  //search by courseName

    //insertClass(string classSection, int courseId, int semesterId)
    int insertClass(string, int, int);
    //selectClass(int classId)
    vector< vector<string> > selectClass();  //get Class table
    vector< vector<string> > selectClass(int);  //search by classId
    vector< vector<string> > selectClassInSemester(int);  //search by semesterId
    vector< vector<string> > selectClassByCourseName(string);  //search by courseName
    vector< vector<string> > selectClassWithLetterGradeRange(int);  //search by classId and return LetterGradeRange at the end
    //updateClass(int classId, string classSection, int courseId, int semesterId)
    bool updateClass(int, string, int, int);
    //letterGradeReleased(int classId, int letterGradeReleased)
    bool letterGradeReleased(int, int);
    //deleteClass(int classId)
    //deleteClassTrigger will deleter corresponding tuples in ClassInformation and Activity table
    //trigger also delete letterGradeRange
    bool deleteClass(int);

    //insertClassInformation(string id, int classId, string letterGrade);
    int insertClassInformation(string, int, string);
    //selectClassInformation(string id);
    //selectClassInformation(int classId);
    //selectClassInformation(string id, int classId);
    vector< vector<string> > selectClassInformation();   //get ClassInformation table
    vector< vector<string> > selectClassInformation(string); //search by student id
    vector< vector<string> > selectClassInformation(int);    //search by classId
    vector< vector<string> > selectClassInformation(string, int);    //search by student id and classId
    //updateClassInformation(string id, int classId, string letterGrade);
    bool updateClassInformation(string, int, string);
    //deleteClassInformation(string id, int classId)
    //deleteClassInformationTrigger will delete tuples in Grade table
    bool deleteClassInformation(string, int);

    //insertActivity(int classId, string activity, double maxMark, double weight)
    int insertActivity(int, string, double, double);
    //selectActivity(int activityId);
    vector< vector<string> > selectActivity();  //get Activity table
    vector< vector<string> > selectActivity(int);   //search by activityId
    //selectActivityInClass(int classId);   return activities in a class
    vector< vector<string> > selectActivityInClass(int);   //search by classId
    //updateActivity(int activityId, int classId, string activity, double maxMark, double weight)
    //activityId is used to find the tuple, and it should not be modified
    bool updateActivity(int, int, string, double, double);
    //deleteActivity(int activityId)
    //deleteActivityTrigger will delete corresponding tuples in Grade table
    bool deleteActivity(int);

    //insertGrade(string id, int activityId, double mark)
    //has a sub routine to handle new tuple is already there, updateGrade will be called
    //return rowid if new tuple can be inserted, rutrn -1 if update does not change data,
    //return 0 if there is a update
    int insertGrade(string, int, double);   //mark < 0 will be stored as NULL in db
    //selectGrade(string id);
    //selectGrade(int activityId);
    //selectGrade(string id, int activityId)
    vector< vector<string> > selectGrade(); //get grade table
    vector< vector<string> > selectGrade(string);   //search by student id
    vector< vector<string> > selectGrade(int);  //search by activityId
    vector< vector<string> > selectGrade(string, int);  //search by student id and activityId
    //updateGrade(string id, int activityId, double mark);
    //id and activityId is used to find the tuple, and they should not be modified
    bool updateGrade(string, int, double);
    //deleteGrade(string id, int activityId)
    //no trigger
    bool deleteGrade(string, int);

    //insertLetterGradeRange(int classId, double, double, double, double, double, double, double, double, double, double, double);
    int insertLetterGradeRange(int, double, double, double, double, double, double, double, double, double, double, double);
    //selectLetterGradeRange(int classId)
    vector< vector<string> > selectLetterGradeRange(); //get letterGradeRange table
    vector< vector<string> > selectLetterGradeRange(int);  //search by classId
    //updateLetterGradeRange(int classId, double, double, double, double, double, double, double, double, double, double, double);
    bool updateLetterGradeRange(int, double, double, double, double, double, double, double, double, double, double, double);
    //deleteLetterGradeRange(int classId)
    //no trigger
    bool deleteLetterGradeRange(int);

private:
    QSqlDatabase db;
    bool openDB();
    void checkTable();  //Initialize table at first launch
    int insert(QSqlQuery &, QStringList &); //local method for insertion's general part 
    void select(QSqlQuery &, vector< vector<string> > &);    //local method for selection's general part
    inline void buildSelectUser(userType &, QString &);
    inline void buildSelectAccount(QString &);
    inline void buildSelectSemester(QString &);
    inline void buildSelectCourse(QString &);
    inline void buildSelectClass(QString &);
    inline void buildSelectClassInformation(QString &);
    inline void buildSelectActivity(QString &);
    inline void buildSelectGrade(QString &);
    inline void buildSelectLetterGradeRange(QString &);

    bool createAccountTable();
    bool createUserTable();
    bool createAdminTable();
    bool createInstructorTable();
    bool createTATable();
    bool createStudentTable();
    bool createSemesterTable();
    bool createCourseTable();
    bool createClassTable();
    bool createClassInformationTable();
    bool createActivityTable();
    bool createApplicationTable();
    bool createGradeTable();
    bool createLetterGradeRangeTable();

    //single string for attributes, return id
    //E.g., User: id, name, gpa
    //attributes = "NULL Jimmy 2.8"
    int insertAccount(string);
    int insertUser(string);
    int insertAdmin(string);
    int insertInstructor(string);
    int insertTA(string);
    int insertStudent(string);
    //insertCourse(string courseName)
    int insertCourse(string); //return courseId
    //insertAccount(string id, string userName, string password)
    int insertAccount(string, string, string);

    //triggers
    void deleteSemesterTrigger();
    void deleteClassTrigger();
    void deleteClassInformationTrigger();
    void deleteActivityTrigger();
};

#endif // DATABASEIF_H
