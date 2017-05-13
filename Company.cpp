#include "Company.h"
#include "Line.h"
#include "Driver.h"


Empresa::Company(string name, string driversFile, string linesFile) {
	this->name = name;

	//Drivers file

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
			Driver driver1(line);
			Drivers.push_back(driver1);
		}

		drivers_f.close();


		//Lines Files
		vector <line> Lines;
		string nome, line;
		ifstream f_linhas;

		cout << "Introduza o nome do ficheiro de linhas: ";
		cin >> nome_f;
		f_linhas.open(nome_f);

		while (f_linhas.fail())
		{
			cout << "ERRO: nao abriu o ficheiro de linhas" << endl;
			cout << "Introduza de novo o ficheiro de linhas: ";
			cin >> nome_f;
			f_linhas.open(nome_f);
		}

		while (!f_linhas.eof())
		{
			Linha l1;

			getline(f_linhas, line);

			l1.ID = stoi(line.substr(0, line.find(';')));
			line = line.substr(line.find(';') + 2);
			l1.Freq = stoi(line.substr(0, line.find(';')));
			line = line.substr(line.find(';') + 2);

			while (line.find(',') < line.find(';'))
			{
				l1.Paragens.push_back(line.substr(0, line.find(',')));
				line = line.substr(line.find(',') + 2);
			}
			l1.Paragens.push_back(line.substr(0, line.find(';')));
			line = line.substr(line.find(';') + 2);

			for (unsigned int i = 1; i < l1.Paragens.size(); i++)
			{
				l1.tempoEntreViagem.push_back(stoi(line.substr(0, line.find(','))));
				line = line.substr(line.find(',') + 2);
			}

			Linhas.push_back(l1);
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
