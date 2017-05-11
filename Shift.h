#pragma once

#include <iostream>
#include <vector>


using namespace std;

class Shift{
 private:
  unsigned int busLineId;
  unsigned int driverId;  
  unsigned int busOrderNumber; 
  unsigned int startTime; 
  unsigned int endTime;   

 public:
  Shift(unsigned int busLineId, unsigned int driverId, unsigned int busNumber, unsigned int startTime, unsigned int endTime); //constructor
  // get methods
  unsigned int getBusLineId() const;
  unsigned int getDriverId() const;
  unsigned int getBusOrderNumber() const; // order of the bus within the bus line
  unsigned int getStartTime() const;
  unsigned int getEndTime() const;

  //  set methods
  void setBusLineId(unsigned int busLineId);
  void setDriverId(unsigned int driverId);
  void setBusOrderNumber(unsigned int busOrderNumber);
  void setStartTime(unsigned int startTime);
  void setEndTime(unsigned int endTime);

  // other methods
};
