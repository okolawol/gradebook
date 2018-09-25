#ifndef GRADE_H
#define GRADE_H
#include <vector>
#include <string>
using namespace std;
#include "Activity.h"

class Grade {
private:
	int studentID;
	int classID;
	vector<Activity> activities; //an Activity represents a quiz, mid-term, etc.
public:
    Grade();
    ~Grade();
    void setCourseID(int newClassID);
	int getStudentID();
	int getClassID();
	void setStudentID(int newStudentID);
	void setClassID(int newClassID);
	Activity getActivity (int index);
	vector<Activity> getActivities (string activityName);
    vector<Activity> getActivities ();
	void addActivity(Activity newActivity);
	void deleteActivity(int activityID);


};

#endif
