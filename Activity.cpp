#include "Activity.h"

Activity::Activity() {
}

Activity::~Activity() {
}

string Activity::getName() {
	return name;
}

void Activity::setName(string newName) {
	name = newName;
}

double Activity::getMark() {
	return mark;
}

void Activity::setMark(double newMark) {
	mark = newMark;
}

int Activity::getMaxMark() {
	return maxMark;
}

void Activity::setActivityID(int newActivityID){
    activityID = newActivityID;
}

int Activity::getActivityID(){
    return activityID;
}

void Activity::setMaxMark(int newMaxMark) {
	maxMark = newMaxMark;
}
void Activity::setWeight(double newWeight)
{
    weight = newWeight;
}
double Activity::getWeight()
{
    return weight;
}
