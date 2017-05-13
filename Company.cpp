#include "Company.h"
#include "Line.h"
#include "Driver.h"


Empresa::Company(string name, string driversFile, string linesFile) {
	this->name = name;

	//Drivers file

		string name_f, lined;
		ifstream drivers_f;
		vector <Driver> Drivers;

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
			getline(drivers_f, lined);
			Driver driver1(lined);
			Drivers.push_back(driver1);
		}

		drivers_f.close();


		//Lines Files
		string name_f, linel;
		ifstream lines_f;
		vector <Line> Lines;

		cout << "Introduza o nome do ficheiro de linhas: ";
		cin >> name_f;
		lines_f.open(name_f);

		while (lines_f.fail())
		{
			cout << "ERRO: nao abriu o ficheiro de linhas" << endl;
			cout << "Introduza de novo o ficheiro de linhas: ";
			cin >> name_f;
			lines_f.open(name_f);
		}

		while (!lines_f.eof())
		{
			getline(lines_f, linel);
			Line Line1(linel);
			Lines.push_back(linel);
		}

		f_linhas.close();
		
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
