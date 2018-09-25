//
//  GradeBook.cpp
//  GradeBook
//
//  Created by Xian Yi Lei on 2013-06-24.
//  Copyright (c) 2013 xLei. All rights reserved.
//

#include "GradeBook.h"
#include "QtDebug"
GradeBook::GradeBook()
{
    db = new DatabaseIF();
}


User GradeBook::getCurrentUser()
{
	return currentUser;
}


bool GradeBook::authenticate(string username, string password)
{
    vector< vector<string> > checkResults = db->selectUser(username, password);
	vector< vector<string> > temp;

    if(! checkResults.empty())
    {

        if(checkResults.size() == 1)// change result into User class
        {

            string id = checkResults[0][0];
            string firstName = checkResults[0][1];
            string lastName = checkResults[0][2];
            string email = checkResults[0][3];
            string userType = checkResults[0][4];


			Account userAccount = Account(username, password);

            User loginUser;


            if(userType.compare("admin") == 0)
			{

                Admin adminUser;
                loginUser = adminUser;
                loginUser.setUserType("admin");

			}
            else if(userType.compare("instructor") == 0)
			{

                Instructor instUser;
				
                temp = db->selectUser(INSTRUCTOR, id);
				string office = temp[0][5];
				string department = temp[0][6];

                instUser.setOffice(office);
                instUser.setDepartment(department);

                loginUser = instUser;
                loginUser.setUserType("instructor");
			}
            else if(userType.compare("ta") == 0)
			{
                TA taUser;

                temp = db->selectUser(T_A_, id);
				string office = temp[0][5];

                taUser.setOffice(office);

                loginUser = taUser;
                loginUser.setUserType("ta");

			}
            else // if (userType.compare("student") == 0)
			{
                Student studUser;

                temp = db->selectUser(STUDENT, id);
				string department = temp[0][5];
				string major = temp[0][6];

                studUser.setDepartment(department);
                studUser.setMajor(major);

                loginUser = studUser;
                loginUser.setUserType(userType);
			}

            loginUser.setFirstName(firstName);
            loginUser.setLastName(lastName);
            loginUser.setEmail(email);
            loginUser.setID(id);
			loginUser.setAccount(userAccount);


			currentUser = loginUser;

			return true;

        }

		else
		{
			return false;
        }


    }
    else{
      return false;
    }
    
}

void GradeBook::setCurrentUser(User user){
    currentUser = user;
}
void GradeBook::deleteClass(Class aClass){
    db->deleteClass(aClass.getClassID());
}



vector<Course> GradeBook::getCourses()
{
    vector<vector<string>> selectedResults = db->selectCourse();
    int sizeOfCourse = selectedResults.size();
    vector<Course> results;

    for(int i = 0; i < sizeOfCourse; i ++)
    {
        string courseIDs = selectedResults[i][0];
        int courseID = atoi(courseIDs.c_str());
        string courseName = selectedResults[i][1];

        Course temp = Course(courseID, courseName);

        results.push_back(temp);
    }

    return results;
}

void GradeBook::reOpenDatabaseConnection(){
    db = new DatabaseIF();
}

vector<User> GradeBook::getUsers(int userType){
    vector<User> temp;
    vector< vector<string> > checkResults;

    if(userType == 1){
         checkResults = db->selectUser(INSTRUCTOR);
    }
    else if(userType == 2){
        checkResults = db->selectUser(T_A_);
    }
    else if(userType == 3){
        checkResults = db->selectUser(STUDENT);
    }

    for(int i=0; i < (int)checkResults.size(); i++){
        string id = checkResults[i][0];
        string firstName = checkResults[i][1];
        string lastName = checkResults[i][2];
        string email = checkResults[i][3];
        string userType = checkResults[i][4];

        User user;
        user.setID(id);
        user.setFirstName(firstName);
        user.setLastName(lastName);
        user.setEmail(email);
        user.setUserType(userType);

        temp.push_back(user);
    }

    return temp;
}

int GradeBook::addClass(string classSection, int courseId, int semesterId){
    return db->insertClass(classSection, courseId, semesterId);
}
void GradeBook::addUserToClass(string userID, int classID){
    db->insertClassInformation(userID, classID,"NULL");
}
void GradeBook::removeUserFromClass(string id, int classID){
    db->deleteClassInformation(id,classID);
}

void GradeBook::updateClass(int classId, string classSection, int courseId, int semesterId){
    db->updateClass(classId,classSection,courseId,semesterId);
}

vector<Class> GradeBook::getAllClasses(){
    vector<Class> temp;

    vector< vector<string> > results;

    results = db->selectClass();

    temp = convertDBVectorToClassVector(results);

    return temp;

}

vector<Class> GradeBook::searchClass(string searchString){

    vector<Class> temp;

    vector< vector<string> > results;

    results = db->selectClassByCourseName(searchString);

    temp = convertDBVectorToClassVector(results);

    return temp;

}
vector<Class> GradeBook::getAllClasses(int semesterID){
    vector<Class> temp;

    vector< vector<string> > results;

    results = db->selectClassInSemester(semesterID);

    temp = convertDBVectorToClassVector(results);

    return temp;
}

vector<Class> GradeBook::convertDBVectorToClassVector(vector<vector<string> > selectedClass){
    vector<Class> temp;

    vector< vector<string> > results = selectedClass;
    vector< vector<string> > classInfo;
    vector< vector<string> > userInfo;
    vector< vector<string> > courseInfo;

    for(int i=0; i< (int)results.size();i++){
        string classID = results[i][0];
        string classSection = results[i][1];
        string courseID = results[i][2];
        string semesterID = results[i][3];
        string letterGradeReleased = results[i][4];


        int classIdInt = atoi(classID.c_str());
        int courseIDInt = atoi(courseID.c_str());
        int semesterIDInt = atoi(semesterID.c_str());
        int lGR = atoi(letterGradeReleased.c_str());


        Class tempClass(classIdInt,classSection,courseIDInt,semesterIDInt,db);
        if(lGR == 0){
            tempClass.setLetterGradeReleased(false);
        }
        else{
            tempClass.setLetterGradeReleased(true);
        }

        courseInfo = db->selectCourse(courseIDInt);
        string courseName = courseInfo[0][1];
        tempClass.setClassName(courseName);

        classInfo = db->selectClassInformation(classIdInt);

        for(int j = 0; j< (int)classInfo.size(); j++){
            string userID = classInfo[j][0];
            userInfo = db->selectUser(userID);

            string id = userInfo[0][0];
            string firstName = userInfo[0][1];
            string lastName = userInfo[0][2];
            string email = userInfo[0][3];
            string usertype = userInfo[0][4];

            if(usertype.compare("instructor")==0){
                Instructor instr;
                instr.setID(id);
                instr.setFirstName(firstName);
                instr.setLastName(lastName);
                instr.setEmail(email);
                instr.setUserType(usertype);

                tempClass.setInstructor(instr);
            }
            else if(usertype.compare("ta")==0){
                TA ta;
                ta.setID(id);
                ta.setFirstName(firstName);
                ta.setLastName(lastName);
                ta.setEmail(email);
                ta.setUserType(usertype);

                tempClass.addTA(ta);
            }
            else{
                Student student;
                student.setID(id);
                student.setFirstName(firstName);
                student.setLastName(lastName);
                student.setEmail(email);
                student.setUserType(usertype);

                tempClass.addStudent(student);
            }
        }
        //qDebug()<<QString::fromStdString(tempClass.getClassName());
        temp.push_back(tempClass);
    }

    return temp;
}

void GradeBook::addSemester(string year, string term){
    db->insertSemester(year,term);
}
void GradeBook::deleteSemester(int semesterID){
    db->deleteSemester(semesterID);
}

vector<Semester> GradeBook::getSemesters(){
    vector<Semester> temp;
    vector<vector<string>> results;

    results = db->selectSemester();
    for(int i=0; i< (int)results.size(); i++){
        string semesterID = results[i][0];
        string year = results[i][1];
        string term = results[i][2];

        int semID = atoi(semesterID.c_str());
        int yearInt = atoi(year.c_str());

        Semester semester;
        semester.setSemesterID(semID);
        semester.setYear(yearInt);
        semester.setTerm(term);

        temp.push_back(semester);

    }
    return temp;

}


GradeBook::~GradeBook()
{
    delete db;
}

