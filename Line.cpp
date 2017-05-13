#include "Line.h"


Line::Line(string textLIne){

  // INITIALISATION CODE GOES IN HERE
 
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