#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
using namespace std;

class Activity {
private:
    string name; //e.g. mid-term, quiz, etc.
	double weight; //if 2%, then 2.0. if 10%, then 10.0. If 7.5%, then 7.5
    double mark;
    int maxMark;
    int activityID;
	//int meanMark;
public:
	Activity();
	~Activity();
    string getName();
    void setName(string newName);
    double getMark();
    void setMark (double newMark);
	int getMaxMark();
	void setMaxMark (int newMaxMark);
	int getActivityID();
    void setActivityID(int newActivityID);

    void setWeight(double newWeight);
     double getWeight();
	//int getMeanMark();
	//void setMeanMark (int newMeanMark);
};

#endif
