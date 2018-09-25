#include <iostream>
#include "TA.h"
#include "Admin.h"



TA::TA(){
}

void TA::setOffice(string new_office)
{
	office = new_office;
}

string TA::getOffice()
{
	return office;
}
