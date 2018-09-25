//
//  GradeBook.h
//  GradeBook
//
//  Created by Xian Yi Lei on 2013-06-24.
//  Copyright (c) 2013 xLei. All rights reserved.
//

#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <iostream>
#include <vector>
#include <string>
#include "databaseif.h"
#include "Class.h"
#include "Semester.h"
#include "Course.h"
#include "Admin.h"
#include "Student.h"
#include "TA.h"
#include "Instructor.h"

using namespace std;


class GradeBook
{
    public:
    
        GradeBook();

        bool authenticate(string username, string password);

        int addClass(string classSection, int courseId, int semesterId);
        void addUserToClass(string userID,int classID);
        void removeUserFromClass(string id, int classID);
        void updateClass(int classId, string classSection, int courseId, int semesterId);

        void editClass(Class aClass);
        void deleteClass(Class aClass);
        vector<Class> searchClass(string searchString);

        void addSemester(string year,string term);
        void deleteSemester(int semesterID);
		vector<Semester> getSemesters();

		vector<User> getUsers(int userType);
        vector<Class> getAllClasses(int semesterID);
        vector<Class> getAllClasses();
		vector<Course> getCourses(); //returns list of all courses. Use getClassName

		User getCurrentUser();
        void setCurrentUser(User user);
        void reOpenDatabaseConnection();


        vector<Class> convertDBVectorToClassVector(vector<vector<string> > selectedClass);
        vector<User> convertDBVectorToUserVector(vector<vector<string> > selectedUsers);
        vector<Course> convertDBVectorToCourseVector(vector<vector<string> > selectedCourses);
        vector<Semester> convertDBVectorToSemesterVector(vector<vector<string> > selectedSemesters);


        ~GradeBook();

    
    
    private:
		User currentUser;
        DatabaseIF *db;


  
};

#endif /* defined(__GradeBook__GradeBook__) */
