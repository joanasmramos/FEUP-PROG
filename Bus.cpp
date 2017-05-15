#include "Bus.h"


Bus::Bus(unsigned int order, unsigned int driver, unsigned int line){
	orderInLine = order;
	driverId = driver;
	lineId = line;
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{
  return orderInLine;
}

unsigned int Bus::getDriverId() const{
  return driverId;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}

unsigned int orderInLine;
unsigned int driverId;
unsigned int lineId;
vector<Shift> schedule;
//////////////////////////////
// set methods
/////////////////////////////
void Bus::setDriverId(unsigned int driver) {
	driverId = driver;
}

void Bus::setLineId(unsigned int line) {
	lineId = line;
}

void Bus::setSchedule(unsigned int i, unsigned int startTime, unsigned int endTime) {
	schedule.at(i).setBusLineId(lineId);
	schedule.at(i).setBusOrderNumber(orderInLine);
	schedule.at(i).setStartTime(startTime);
	schedule.at(i).setEndTime(endTime);
}

////////////////////////////
// other methods
///////////////////////////
