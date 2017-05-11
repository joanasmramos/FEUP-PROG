#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"


using namespace std;

class Company{
 private:
  string name;
  vector<Driver> drivers;
  vector<Line> lines;
 public:
  Company(string name, string driversFile, string linesFile)
  // get methods
  string getName() const;
  // set methods
  // other methods
  void distribuiServico(); // funcao que implementa a afectacao de servico
};
