#include "Driver.h"
#include "Company.h"


Driver::Driver(string line){
	id = stoi(line.substr(0, line.find(';')));
	line = line.substr(line.find(';') + 2);
	name = line.substr(0, line.find(';') - 1);
	line = line.substr(line.find(';') + 2);
	maxHours = stoi(line.substr(0, line.find(';')));
	line = line.substr(line.find(';') + 2);
	maxWeekWorkingTime = stoi(line.substr(0, line.find(';')));
	line = line.substr(line.find(';') + 2);
	minRestTime = stoi(line);
}
Driver::Driver() {}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

//////////////
// set methods
//////////////

void Driver::setId(unsigned int id) {
	this->id = id;
}

void Driver::setName(string name) {
	this->name = name;
}

void Driver::setMaxHours(unsigned int maxHours) {
	this->maxHours = maxHours;
}

void Driver::setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime) {
	this->maxWeekWorkingTime = maxWeekWorkingTime;
}

void Driver::setMinRestTime(unsigned int minRestTime) {
	this->minRestTime = minRestTime;
}

//////////////
// other methods
//////////////
