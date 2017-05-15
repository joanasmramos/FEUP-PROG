#include "Line.h"


Line::Line(string textLine) {

	id_line = stoi(textLine.substr(0, textLine.find(';')));
	textLine = textLine.substr(textLine.find(';') + 2);
	freq = stoi(textLine.substr(0, textLine.find(';')));
	textLine = textLine.substr(textLine.find(';') + 2);

	while (textLine.find(',') < textLine.find(';'))
	{
		busStopList.push_back(textLine.substr(0, textLine.find(',')));
		textLine = textLine.substr(textLine.find(',') + 2);
	}
	busStopList.push_back(textLine.substr(0, textLine.find(';')));
	textLine = textLine.substr(textLine.find(';') + 2);

	for (unsigned int i = 1; i < busStopList.size(); i++)
	{
		timesList.push_back(stoi(textLine.substr(0, textLine.find(','))));
		textLine = textLine.substr(textLine.find(',') + 2);
	}
}
Line::Line() {}

////////////////
// get methods
////////////////

unsigned int Line::getId() const{
  return id_line;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}

unsigned int Line::getFreq() const {
	return freq;
}

////////////////
// set methods
////////////////

void Line::setID(unsigned int id) {
	id_line = id;
}

void Line::setFreq(unsigned int freq) {
	this->freq = freq;
}

void Line::setBusStops(vector<string> paragens) {
	busStopList = paragens;
}

void Line::setTimings(vector<int> tempos) {
	timesList = tempos;
}

////////////////
// other methods
////////////////

unsigned int Line::nrBuses() const {
	int totalTime = 0; // time that the bus takes to reach its destination and come back
	int nrbuses = 0; 
	for (unsigned int i = 0; i < timesList.size(); i++)
	{
		totalTime = totalTime + timesList.at(i);
	}
	//rigth now totalTime contains only the time to reach the destination, so we have to double it to include the time it takes to come back
	totalTime = 2 * totalTime;
	nrbuses = (int)((double)totalTime / freq + 1.0);

	return nrbuses;
}