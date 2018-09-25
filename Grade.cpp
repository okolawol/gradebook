
#include "Grade.h"

Grade::Grade() {
}

Grade::~Grade() {
}

int Grade::getStudentID() {
	return studentID;
}

int Grade::getClassID() {
	return classID;
}

void Grade::setStudentID (int newStudentID) {
	studentID = newStudentID;
}

void Grade::setClassID (int newClassID) {
	classID = newClassID;
}

Activity Grade::getActivity (int index) {
	Activity toBeReturned;
    if (index < (int)(activities.size())) {
		toBeReturned = activities[index];
	}
    return toBeReturned;
}

vector<Activity> Grade::getActivities (string activityName) {
	vector<Activity> toBeReturned;
    for (int i = 0; i < (int)activities.size(); i++) {
		if (activityName.compare(activities[i].getName())) {
			toBeReturned.push_back(activities[i]);
		}
	}
	return toBeReturned;
}
vector<Activity> Grade::getActivities(){
    return activities;
}

void Grade::addActivity(Activity newActivity) {
	activities.push_back(newActivity);
}


void Grade::deleteActivity (int activityID) {
    vector<Activity>::iterator i;
    for (i = activities.begin(); i != activities.end(); ++i) {
        if ((*i).getActivityID() == activityID) {
			activities.erase(i);
			break;
		}
	}
}

