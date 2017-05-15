#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Bus.h"



using namespace std;

class Line {
private:
	unsigned int id_line;
	vector<string> busStopList;
	vector<int> timesList;
	unsigned int freq;
	vector<Bus> Buses;

public:
	Line();
	Line(string textLine);
	// get methods
	unsigned int getId() const;
	vector<string> getBusStops() const;
	vector<int> getTimings() const;
	unsigned int getFreq() const;
	vector<Bus> getBuses() const;
	vector<int> gettimeBetweenStops() const;

	// set methods
	void setID(unsigned int id);
	void setFreq(unsigned int freq);
	void setBusStops(vector<string> stops);
	void setTimings(vector<int> timings);

	// other methods
	unsigned int nrBuses() const; // computes the number of buses needed for one line
};
