#include "Company.h"
#include "Line.h"
#include "Driver.h"
#include <fstream>


Company::Company(string name, string driversFile, string linesFile) {
	this->name = name;

}

////////////////////////////////
// get methods
///////////////////////////////
string Company::getName() const {
	return name;
}

//////////////////////////////
// set methods
/////////////////////////////


////////////////////////////
// other methods
///////////////////////////
void Company::distribuiServico() {
}
