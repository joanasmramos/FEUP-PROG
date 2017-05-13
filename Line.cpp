#include "Line.h"


Line::Line(string textLine){

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

unsigned int id_l;
vector<string> busStopList;
vector<int> timesList;
unsigned int freq;

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