#include "Company.h"
#include "Line.h"
#include "Driver.h"


Empresa::Company(string name, string driversFile, string linesFile) {
	this->name = name;

	vector <driver> Drivers;
	//drivers file
		string name_f, line;
		ifstream drivers_f;
		vector <driver> Drivers;

		cout << "Introduza o nome do ficheiro de condutores: ";
		cin >> name_f;
		drivers_f.open(name_f);

		while (drivers_f.fail())
		{
			cout << "ERRO: nao abriu o ficheiro de condutores" << endl;
			cout << "Introduza de novo o ficheiro de condutores: ";
			cin >> name_f;
			drivers_f.open(name_f);
		}

		while (!drivers_f.eof())
		{
			getline(drivers_f, line);
			Driver 1driver(line);
			Drivers.push_back(1driver);
		}

		drivers_f.close();
}

////////////////////////////////
// get methods
///////////////////////////////
string Company::getName() const{
  return name;
}

//////////////////////////////
// set methods
/////////////////////////////

////////////////////////////
// other methods
///////////////////////////
void Company::distribuiServico(){
}
