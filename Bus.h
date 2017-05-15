#pragma once

#include <iostream>
#include <vector>
#include "Shift.h"


using namespace std;

class Bus{
 private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int order, unsigned int driver, unsigned int line); //constructor
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
   void setDriverId(unsigned int driver);
   void setLineId(unsigned int line);
   void setSchedule(unsigned int i, unsigned int startTime, unsigned int endTime);
  // other methods

};
