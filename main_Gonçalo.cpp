/*LABORATÓRIO DE SISTEMAS OPERATIVOS - PARTE 1 DO PROJETO DE PROG 2016/2017 */

/*   P R O J E T O   1   */

// LINHAS ->  ID, FREQUENCIA, LISTA DE PARAGENS, LISTA TEMPOS VIAGEM
// MOTORISTAS -> NOME, ID_MOTORISTA, N_HORAS_TURNO, N_HORAS_SEMANAIS, N_HORAS_DESCANSO

#include <iostream> // I/O reasoning
#include <vector> //For use of vectors
#include <string> //For use of strings
#include <fstream> //Manipulation of files
#include <limits> //Invalid inputs
#include <iomanip> //setfill, setw, ...

using namespace std;

//PROTOTYPING
void MenuPrincipal();
void InvalidInputMenu();
void InvalidInputFicheiro();
void ErrorErrorError(int &i);
void MenuGravarFicheiro();
void HorariosParagens();
void HorariosLinhas();
void GESTLINHA();
void GESTCOND();
void Informacoes();
void AdicionarLinha();
void RemoverLinha();
void AlterarLinhaMenu();
void AdicionarCondutor();
void RemoverCondutor();
void AlterarCondutorMenu();
void VerLinhasExistentes();
void VerPercursosExistentes();
void VerCondutoresExistentes();
void LinhasParagens();
void CalcularTempoParagens();
void streamsLinhasECondutores();
void abertura_condutores();
void abertura_linhas();
void SaveFicheiroLinhas();
void SaveFicheiroCondutores();
int RetIDCondutores(int id);
int RetIDLinhas(int id);
int VerificarIDLinhas(int id);
int VerificarIDCondutores(int id);
int Commas(string stringe);

//STRUCTS AND THEIR CORRESPONDING VECTORS
struct Condutor {
	string Nome;
	int ID_Motorista;
	int NHoras_Turno;
	int NHoras_Semanais;
	int NHoras_Descanso;

};
struct Linha {
	int ID;   //or string ID, each at the own user's choice.
	int Freq;
	vector <string>  Paragens;
	vector <int> tempoEntreViagem;
};

//VECTORS
vector <Linha> Linhas;
vector <Condutor> Condutores;

//FICHEIROS
void abertura_condutores()
{
	string nome_f, line;
	ifstream f_condutores;
	Condutor c1;

	cout << "Introduza o nome do ficheiro de condutores: ";
	cin >> nome_f;
	f_condutores.open(nome_f);

	while (f_condutores.fail())
	{
		cout << "ERRO: nao abriu o ficheiro de condutores" << endl;
		cout << "Introduza de novo o ficheiro de condutores: ";
		cin >> nome_f;
		f_condutores.open(nome_f);
	}

	while (!f_condutores.eof())
	{
		getline(f_condutores, line);
		c1.ID_Motorista = stoi(line.substr(0, line.find(';')));
		line = line.substr(line.find(';') + 2);
		c1.Nome = line.substr(0, line.find(';') - 1);
		line = line.substr(line.find(';') + 2);
		c1.NHoras_Turno = stoi(line.substr(0, line.find(';')));
		line = line.substr(line.find(';') + 2);
		c1.NHoras_Semanais = stoi(line.substr(0, line.find(';')));
		line = line.substr(line.find(';') + 2);
		c1.NHoras_Descanso = stoi(line);

		Condutores.push_back(c1);
	}

	f_condutores.close();
}
void abertura_linhas()
{
	Linha l1;
	string nome_f, line;
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
void SaveFicheiroCondutores() {
	string FicheiroCondutor;
	"========================================================================================================\n";
	cout << "Insira o nome do ficheiro de condutores que pretende gravar: \n";
	cin >> FicheiroCondutor;

	ofstream FicheiroCondutores;

	FicheiroCondutores.open(FicheiroCondutor);

	for (unsigned int i = 0; i < Condutores.size(); i++)
	{
		FicheiroCondutores << Condutores.at(i).ID_Motorista << " ; " << Condutores.at(i).Nome << " ; " << Condutores.at(i).NHoras_Turno << " ; " << Condutores.at(i).NHoras_Semanais << " ; " << Condutores.at(i).NHoras_Descanso << endl;
	}
	FicheiroCondutores.close();
	cout << "\n\nFicheiro gravado! Retornando ao Menu Principal...\n";
	"=======================================================================================================\n\n";
	MenuPrincipal();
}
void SaveFicheiroLinhas() {
	string FicheiroLinha;
	"========================================================================================================\n";
	cout << "Insira o nome do ficheiro de linhas que pretende gravar: \n";
	cin >> FicheiroLinha;

	ofstream FicheiroLinhas;

	FicheiroLinhas.open(FicheiroLinha);

	for (unsigned int i = 0; i < Linhas.size(); i++)
	{
		FicheiroLinhas << Linhas.at(i).ID << " ; " << Linhas.at(i).Freq << " ; ";
		for (unsigned int j = 0; j < Linhas.at(i).Paragens.size(); j++)
		{
			if (j == Linhas.at(i).Paragens.size() - 1)
			{
				FicheiroLinhas << Linhas.at(i).Paragens.at(j) << "; ";
			}
			else {
				FicheiroLinhas << Linhas.at(i).Paragens.at(j) << ", ";
			}
		}
		for (unsigned int k = 0; k < Linhas.at(i).tempoEntreViagem.size(); k++)
		{
			if (k == Linhas.at(i).tempoEntreViagem.size() - 1)
			{
				FicheiroLinhas << Linhas.at(i).tempoEntreViagem.at(k) << "";
			}

			else {
				FicheiroLinhas << Linhas.at(i).tempoEntreViagem.at(k) << ", ";
			}

		}
		FicheiroLinhas << endl;
	}
	FicheiroLinhas.close();
	cout << "\n\nFicheiro gravado! Retornando ao Menu Principal...\n";
	"========================================================================================================\n\n";
	MenuPrincipal();
}

//FUNÇÕES DE RECEÇÃO DE INFORMAÇÃO QUE FOI DADA POR INPUT PELO UTILIZADOR (LINHAS - CONDUTORES)
void streamsLinhasECondutores() {
	//criar um vetor temporário, que irá ler a informação do ficheiro pretendido, e depositá-lo em formato de string
	vector<string> input;
	cin.clear();
	input.clear();
	cout << "========================================================================================================";
	cout << "\n  Bem - Vindo ao programa Escalonamento de Condutores, da Empresa de Transportes Semprarrolar.\n";
	cout << "   ___ ___ __ __ ___ ___ ___ ___ ___ ___ _   ___ ___ " << endl;
	cout << "  / __| __|  \\  | . | . | . | . | . | . | | | . | . \\   TM" << endl;
	cout << "  \\__ | _>|     |  _|   |   |   |   | | | |_|   |   /" << endl;
	cout << "  <___|___|_|_|_|_| |_\\_|_|_|_\\_|_\\_`___|___|_|_|_\\_\\ " << endl;
	cout << "========================================================================================================\n\n";

	abertura_condutores();
	abertura_linhas();
}

//FUNÇÕES DE TRATAMENTO DE HORÁRIOS
//PARAGENS
void HorariosParagens() {
	int id;
	int flag = 0;
	int indice;
	int horas = 13;
	int minutos = 0;
	int input = -1;
	while (true) {
		cout <<"========================================================================================================\n";
		cout << "Introduza o ID da linha que deseja: ";
		cin >> id;

		if (cin.fail()) { //SE NÃO FOR INT
			cout << endl << "Numero Inválido." << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			for (unsigned int i = 0; i < Linhas.size(); i++) {
				if (Linhas.at(i).ID == id) {
					flag = 1; // YAY!
					indice = i;
				}
			}
			if (flag == 1) {
				break;
			}
			else {
				cout << "Não inseriu um ID correto!" << endl;
			}
		}
	}

	cout << "========================================================================================================\n";

	int opcao;
	for (unsigned int i = 0; i < Linhas.at(indice).Paragens.size(); i++) {
		cout << i << " - " << Linhas.at(indice).Paragens.at(i) << endl;
	}
	while (true) {
		cout << "Introduza a paragem que deseja:\n";
		cin >> opcao;
		if (cin.fail() || (opcao >= Linhas.at(indice).Paragens.size()) || (opcao < 0)) {
			cout << endl << "Invalido!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			break;
		}
	}

	for (unsigned int i = 0; i < opcao; i++) {
		minutos = minutos + Linhas.at(indice).tempoEntreViagem.at(i);
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1; //I mean...
		}
	}
	cout << "HORARIO DESEJADO: (HORAS || ID da LINHA)\n";
	cout << "========================================================================================================\n";
	cout << horas << ":" << setfill('0') << setw(2);
	cout << minutos << "   " << Linhas.at(indice).ID << endl;
	cout << "========================================================================================================\n";
	for (unsigned int i = 0; i < 10; i++) {
		minutos = minutos + Linhas.at(indice).Freq;
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1;
		}
		cout <<"========================================================================================================\n";
		cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Linhas.at(indice).ID << endl;
		cout <<"========================================================================================================\n";
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
	system("pause");
}
void HorariosLinhas() {
	int id = 0;
	int flag = 0;
	int indice = 0;
	int input = -1;
	int horas = 13;
	int minutos = 0;
	while (true) {
		cout << "Introduza o ID da linha que deseja: ";
		cin >> id;

		if (cin.fail()) {
			cout << endl << "Inválido!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			
			for (int i = 0; i < Linhas.size(); i++) {
				if (Linhas.at(i).ID == id) {
					flag = 1;
					indice = i;//YAYX2
				}
			}
			if (flag == 1) {
				break;
			}
			else {
				cout << "Não inseriu um ID correto!" << endl;
			}
		}
	}
	cout << "HORARIO DESEJADO: (HORAS || PARAGENS)\n";
	cout << "========================================================================================================\n";
	cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Linhas.at(indice).Paragens.at(0) << endl;
	cout << "========================================================================================================\n";

	for (int n = 1; n < Linhas.at(indice).Paragens.size(); n++) {
		minutos = minutos + Linhas.at(indice).tempoEntreViagem.at(n - 1);
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1;
		}
		cout << "========================================================================================================\n";
		cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Linhas.at(indice).Paragens.at(n) << endl;
		cout << "========================================================================================================\n";
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
};

//FUNÇÕES DE TRATAMENTO DE INFORMAÇÃO QUE FOI DADA POR INPUT PELO UTILIZADOR (LINHAS - CONDUTORES)
//ADICIONAR
void AdicionarCondutor() {
	string Nome;
	Condutor tempCondutor;

	cout << "========================================================================================================\n";
	cout << "Indique o ID do motorista a adicionar: " << endl;
	cin >> tempCondutor.ID_Motorista;
	ErrorErrorError(tempCondutor.ID_Motorista);

	cout << "Indique o nome do motorista:  " << endl;
	cin.ignore(1000, '\n');
	getline(cin, tempCondutor.Nome);

	cout << "Indique o numero de horas do turno do motorista:\n";
	cin >> tempCondutor.NHoras_Turno;
	ErrorErrorError(tempCondutor.NHoras_Turno);

	cout << "Indique o numero de horas semanais do motorista:\n";
	cin >> tempCondutor.NHoras_Semanais;
	ErrorErrorError(tempCondutor.NHoras_Semanais);

	cout << "Indique o numero de horas de descanso do motorista:\n";
	cin >> tempCondutor.NHoras_Descanso;
	ErrorErrorError(tempCondutor.NHoras_Descanso);

	cout << "========================================================================================================\n";
	Condutores.push_back(tempCondutor);
	cout << "Condutor adicionado! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();

}
void AdicionarLinha() {
	int input = 0;
	Linha tempLinha;
	string tempParagem;
	string tempTempoParagens;
	cout << "========================================================================================================\n";
	cout << "Indique o ID da linha a adicionar: " << endl;
	cin >> tempLinha.ID;
	ErrorErrorError(tempLinha.ID);

	cout << "Indique a Frequencia de circulacao do autocarro: " << endl;
	cin >> tempLinha.Freq;
	ErrorErrorError(tempLinha.Freq);

	cout << "Indique as paragens a sua linha inclui, separadas por virgula apenas (p.ex: Rato,Odivelas). \n";
	//ADD de Paragens with getline
	cin.ignore(1000, '\n');
	getline(cin, tempParagem);

	int contagem = Commas(tempParagem);

	for (int i = 0; i < contagem; i++) {

		tempLinha.Paragens.push_back(tempParagem.substr(0, tempParagem.find(",")));
		tempParagem = tempParagem.substr(tempParagem.find(",") + 1);
		//cout << tempLinha.Paragens[i] << endl;
	}
	tempLinha.Paragens.push_back(tempParagem.substr(1, tempParagem.size() - 1));
	//cout << "tempparagens finalissimo:" << tempParagem << endl;// Confirmação que está a correr tudo como planeado.

	cout << "Indique os tempos entre cada uma das paragens, separadas por virgula apenas(20,10,25). \n";
	getline(cin, tempTempoParagens);

	contagem = Commas(tempTempoParagens);

	for (int i = 0; i < contagem; i++) {

		tempLinha.tempoEntreViagem.push_back(stoi(tempTempoParagens.substr(0, tempTempoParagens.find(","))));
		tempTempoParagens = tempTempoParagens.substr(tempTempoParagens.find(",") + 1);
		cout << tempLinha.tempoEntreViagem[i] << endl;
	}
	tempLinha.tempoEntreViagem.push_back(stoi(tempTempoParagens.substr(1, tempTempoParagens.size() - 1)));
	Linhas.push_back(tempLinha);

	cout << "========================================================================================================\n";
	cout << "Linha adicionada! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();

}

//REMOVER
void RemoverCondutor() {
	int input = 0;
	Condutor tempCondutor;

	cout << "========================================================================================================\n";
	cout << "Indique o ID do motorista que pretende eliminar: ";
	cin >> tempCondutor.ID_Motorista;
	ErrorErrorError(tempCondutor.ID_Motorista);

	while (VerificarIDCondutores(tempCondutor.ID_Motorista) == -1) {
		cin >> tempCondutor.ID_Motorista;
		VerificarIDCondutores(tempCondutor.ID_Motorista);
	}
	//REMOÇÃO
	Condutores.erase(Condutores.begin() + VerificarIDCondutores(tempCondutor.ID_Motorista));
	cout << "========================================================================================================\n";
	cout << "Motorista removido! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();
}
void RemoverLinha() {
	int input = 0;
	Linha tempLinha;

	cout << "========================================================================================================\n";
	cout << "Indique o ID da linha que pretende eliminar: ";
	cin >> tempLinha.ID;
	ErrorErrorError(tempLinha.ID);

	while (VerificarIDLinhas(tempLinha.ID) == -1) {
		cin >> tempLinha.ID;
		VerificarIDLinhas(tempLinha.ID);
	}
	//REMOÇÃO
	Linhas.erase(Linhas.begin() + VerificarIDLinhas(tempLinha.ID));
	cout << "========================================================================================================\n";
	cout << "Linha removida! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();
}

//EDITAR
void AlterarCondutorMenu() {
	string Nome;
	int options;
	int ID_Motorista;
	int NHoras_Turno;
	int NHoras_Semanais;
	int NHoras_Descanso;
	int contagem;
	int tempid;
	Condutor tempCondutor;
	options = -1;
	ID_Motorista = -2;
	NHoras_Turno = -1;
	NHoras_Semanais = -1;
	NHoras_Descanso = -1;
	contagem = -1;
	tempid = 0;


	cout << "========================================================================================================\n";
	cout << "Indique o elemento que pretende alterar na sua linha: \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) ID do motorista. \n";
	cout << "2) Nome do motorista\n";
	cout << "3) Numero de horas de turno\n";
	cout << "4) Numero de horas semanais\n";
	cout << "5) Numero de horas de descanso\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n";

	while (!cin.fail())
	{
		cin >> options;
		switch (options) {
		case 0:
			cout << "\n========================================================================================================\n";
			cout << "Alteracao cancelada! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DO ID DO MOTORISTA
		case 1:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
			} while (VerificarIDCondutores(tempid) == -1);
			tempCondutor.ID_Motorista = tempid;
			cout << "Insira o numero desejado para o novo ID:\n";
			cin >> ID_Motorista;
			ErrorErrorError(ID_Motorista);

			Condutores.at(RetIDCondutores(tempCondutor.ID_Motorista)).ID_Motorista = ID_Motorista;
			"\n========================================================================================================\n";
			cout << "ID alterado! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DO NOME DO MOTORISTA
		case 2:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que pretende alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDCondutores(tempid);
			} while (VerificarIDCondutores(tempid) == -1);
			tempCondutor.ID_Motorista = tempid;
			cout << "Insira o nome do motorista: \n";

			cin.ignore(1000, '\n');
			getline(cin, Nome);

			Condutores.at(RetIDCondutores(tempCondutor.ID_Motorista)).Nome = Nome;
			"\n========================================================================================================\n";
			cout << "Nome alterado! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DO NUMERO DE HORAS NO SEU TURNO
		case 3:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDCondutores(tempid);
			} while (VerificarIDCondutores(tempid) == -1);
			tempCondutor.ID_Motorista = tempid;
			cout << "Insira o numero desejado de horas do turno correspondente:\n ";
			cin >> NHoras_Turno;
			ErrorErrorError(NHoras_Turno);

			Condutores.at(RetIDCondutores(tempCondutor.ID_Motorista)).NHoras_Turno = NHoras_Turno;
			"\n========================================================================================================\n";
			cout << "Horas do turno alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DO NUMERO DE HORAS SEMANAIS
		case 4:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDCondutores(tempid);
			} while (VerificarIDCondutores(tempid) == -1);
			tempCondutor.ID_Motorista = tempid;
			cout << "Insira o numero desejado de horas semanais do motorista:\n ";
			cin >> NHoras_Semanais;
			ErrorErrorError(NHoras_Semanais);

			Condutores.at(RetIDCondutores(tempCondutor.ID_Motorista)).NHoras_Semanais = NHoras_Semanais;
			"\n========================================================================================================\n";
			cout << "Horas semanais alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DO NUMERO DE HORAS DE DESCANSO
		case 5:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n ";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDCondutores(tempid);
			} while (VerificarIDCondutores(tempid) == -1);
			tempCondutor.ID_Motorista = tempid;
			cout << "Insira o numero desejado de horas de descanso do motorista: ";
			cin >> NHoras_Descanso;
			ErrorErrorError(NHoras_Descanso);

			Condutores.at(RetIDCondutores(tempCondutor.ID_Motorista)).NHoras_Descanso = NHoras_Descanso;
			"\n========================================================================================================\n";
			cout << "Horas de descanso alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

		default:
			InvalidInputMenu();
			break;
		}
	}
}
void AlterarLinhaMenu() {
	int options;
	int id;
	int freq;
	int nparagens;
	int ntempos;
	int contagem;
	int tempid = 0;
	string tempParagem;
	string tempTempoParagens;
	Linha tempLinha;
	id = 0;
	freq = 0;
	nparagens = 0;
	ntempos = 0;
	options = 0;
	contagem = 0;
	"========================================================================================================\n";
	cout << "Indique o elemento que pretende alterar na sua linha: \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) ID \n";
	cout << "2) Frequencia de Circulacao de Autocarros\n";
	cout << "3) Paragens\n";
	cout << "4) Tempos entre Viagens\n";
	cout << "0) Menu Principal\n";
	"========================================================================================================\n";
	while (!cin.fail())
	{
		cin >> options;
		switch (options) {
		case 0:
		{cout << "\n========================================================================================================\n";
		cout << "Alteracao cancelada! Retornando ao Menu Principal...\n";
		cout << "========================================================================================================\n";
		MenuPrincipal();
		break;
		}
		//ALTERAÇÃO DO ID
		case 1:
		{
			cout << "========================================================================================================\n";
			cout << "Insira o ID da linha que pretende alterar:\n ";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDLinhas(tempid);
			} while (VerificarIDLinhas(tempid) == -1);
			cout << "Insira o numero desejado para o novo ID:\n";
			cin >> id;
			ErrorErrorError(id);

			Linhas.at(RetIDLinhas(tempLinha.ID)).ID = id;
			cout << "\n========================================================================================================\n";
			cout << "ID alterado! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;
		}
		//ALTERAÇÃO DA FREQUENCIA DE CIRCULACAO
		case 2:
			cout << "========================================================================================================\n";
			cout << "Insira o ID da linha que pretende alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDLinhas(tempid);
			} while (VerificarIDLinhas(tempid) == -1);
			cout << "Insira o numero para a nova frequencia de circulacao: ";
			cin >> freq;
			ErrorErrorError(freq);

			Linhas.at(RetIDLinhas(tempLinha.ID)).Freq = freq;
			cout << "\n========================================================================================================\n";
			cout << "Frequencia de circulacao alterada! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERAÇÃO DAS PARAGENS
		case 3:
		{
			cout << "========================================================================================================\n";
			cout << "Insira o ID da linha que pretende alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDLinhas(tempid);
			} while (VerificarIDLinhas(tempid) == -1);
			cout << "Insira as paragens que vao alterar a linha, separadas por uma virgula apenas. No fim, acabar com uma virgula!! (p.ex: Paranhos,Hospital Sao Joao,):\n";

			cin.ignore(1000000, '\n');
			getline(cin, tempParagem);

			int contagem = Commas(tempParagem);

			int numeroI = RetIDLinhas(tempid);

			Linhas.at(numeroI).Paragens.clear();
			for (int i = 0; i < contagem; i++) {

				Linhas.at(numeroI).Paragens.push_back(tempParagem.substr(0, tempParagem.find(",")));
				tempParagem = tempParagem.substr(tempParagem.find(",") + 1);
				//cout << tempLinha.Paragens[i] << endl;
			}

			//	cout << "tempparagens finalissimo:" << tempParagem << endl;// Confirmação que está a correr tudo como planeado.
			cout << "\n========================================================================================================\n";
			cout << "Paragens alteradas! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;
		}

		case 4:
		{
			cout << "========================================================================================================\n";
			cout << "Insira o ID da linha que pretende alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				VerificarIDLinhas(tempid);
			} while (VerificarIDLinhas(tempid) == -1);

			cout << "Indique os tempos entre cada uma das paragens, separadas por virgula apenas. No fim, acabar com uma virgula! (p.ex: 20,10,25,). \n";
			cin.ignore(1000000, '\n');
			getline(cin, tempTempoParagens);

			contagem = Commas(tempTempoParagens);

			int numeroI = RetIDLinhas(tempid);

			Linhas.at(numeroI).tempoEntreViagem.clear();

			for (int i = 0; i < contagem; i++) {

				Linhas.at(numeroI).tempoEntreViagem.push_back(stoi(tempTempoParagens.substr(0, tempTempoParagens.find(","))));
				tempTempoParagens = tempTempoParagens.substr(tempTempoParagens.find(",") + 1);
				//cout << tempLinha.tempoEntreViagem[i] << endl;

			}

			cout << "\n========================================================================================================\n";
			cout << "Tempos entre viagens alterados! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;
		}
		default:
			InvalidInputMenu();
			break;
		}
		}
	}

//CALCULA A DISTANCIA ENTRE 2 PARAGENS
void CalcularTempoParagens() {
	int exit;
	exit = -1;
	string parg1, parg2;
	cout << "========================================================================================================\n";
	cout << "Introduza a primeira paragem que deseja: " << endl;
	cin >> parg1;
	cout << "Introduza a segunda paragem que deseja" << endl;
	cin >> parg2;

	for (unsigned int i = 0; i < Linhas.size(); i++)
	{
		int par1 = 0;
		int par2 = 0;
		for (unsigned int j = 0; j < Linhas.at(i).Paragens.size(); j++)
		{
			if (Linhas.at(i).Paragens.at(j) == parg1)
			{
				par1 = j;
			}

			if (Linhas.at(i).Paragens.at(j) == parg2)
			{
				par2 = j;
			}
		}
		if (par1 != -1 && par2 != -1) //Linha.at(i) tem as DUAS paragens
		{

			if (par1 > par2)
			{
				cout << "========================================================================================================\n";
				cout << "SENTIDO: " << Linhas.at(i).Paragens.at(0); //Unidireccional
			}

			else
			{
				cout << "========================================================================================================\n";
				cout << "SENTIDO: " << Linhas.at(i).Paragens.at(Linhas.at(i).Paragens.size() - 1); //Volta

			}
			int tempo = 0;
			for (int k = (par1 > par2 ? par2 : par1); k < (par1 < par2 ? par2 : par1); k++) // iterar do par mais pequeno ao maior, k sendo a posicao no vetor tempo
			{
				tempo += Linhas.at(i).tempoEntreViagem.at(k);
			}

			cout << endl;
			cout << "TEMPO DA VIAGEM:  " << tempo << " MINUTOS";
			cout << "\n\n========================================================================================================\n";
			cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
			cin >> exit;
			ErrorErrorError(exit);
			MenuPrincipal();
			cout << "========================================================================================================\n\n";
		}
	}
}

//FUNÇÕES DE TRATAMENTO DAS INFORMAÇÕES (HORARIOS, LINHAS, PERCURSOS)
//PERMITE VER A LINHA EXATAMENTE COMO ESTÁ NO FICHEIRO
void VerPercursosExistentes() {
	int exit;
	exit = -1;

	cout << "========================================================================================================";
	cout << "\nPERCURSOS EXISTENTES: \n\n";
	for (unsigned int i = 0; i < Linhas.size(); i++) {

		for (unsigned int f = 0; f < Linhas.at(i).Paragens.size(); f++) {

			cout << "||ID - " << Linhas.at(i).ID << "|| ";

			cout << Linhas.at(i).Paragens.at(f);

			cout << ";\n";
		}
		cout << "========================================================================================================\n";
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;
	ErrorErrorError(exit);
	MenuPrincipal();
}
void VerLinhasExistentes() {
	int exit;
	exit = -1;

	cout << "LINHAS EXISTENTES: \n\n";
	for (unsigned int i = 0; i < Linhas.size(); i++) {
		cout << "||NR - " << (i + 1) << "|| " << Linhas.at(i).ID << " ; " << Linhas.at(i).Freq << " ; ";
		for (unsigned int j = 0; j < Linhas.at(i).Paragens.size(); j++) {
			cout << Linhas.at(i).Paragens[j];
			if ((j + 1) < Linhas.at(i).Paragens.size()) {
				cout << ", ";
			}
		}
		cout << "; ";
		for (unsigned int j = 0; j < Linhas.at(i).tempoEntreViagem.size(); j++) {
			cout << Linhas.at(i).tempoEntreViagem[j];
			if ((j + 1) < Linhas.at(i).tempoEntreViagem.size())
				cout << ", ";
		}
		cout << endl;
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;

	MenuPrincipal();
}
void VerCondutoresExistentes() {
	int exit;
	exit = -1;

	cout << "|| # || Condutores EXISTENTES || Horas Diarias || Horas Semamanais || Horas Descanso \n\n";

	for (unsigned int i = 0; i < Condutores.size(); i++) {
		cout << "||NR - " << (i + 1) << "|| " << Condutores.at(i).Nome << "\t  " << Condutores.at(i).NHoras_Turno << "\t\t     " << Condutores.at(i).NHoras_Semanais << "\t\t        " << Condutores.at(i).NHoras_Descanso << endl;
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;

	MenuPrincipal();
}
void LinhasParagens()
{
	bool existe = false;
	string paragem;
	int input;
	cout << "========================================================================================================";
	cout << "\nPara saber que linhas passam numa determinada paragem, insira o seu nome (da paragem): " << endl;
	cin.ignore(1000, '\n');
	getline(cin, paragem);

	while (!existe) {

		for (unsigned int i = 0; i < Linhas.size(); i++) {

			for (unsigned int f = 0; f < Linhas.at(i).Paragens.size(); f++) {

				if (paragem == Linhas.at(i).Paragens.at(f)) {
					cout << "Lista de linhas que passam por esta paragem: " << endl;
					cout << Linhas.at(i).ID << endl;
					existe = true;
				}
			}
		}
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
}

//VERIFICAÇÃO DO INDEX DO VETOR
int RetIDLinhas(int id) {
	for (unsigned int i = 0; i < Linhas.size(); i++) {
		if (Linhas.at(i).ID == id) {
			return i;
		}
	}
	return -1;
}
int RetIDCondutores(int id) {
	for (unsigned int i = 0; i < Condutores.size(); i++) {
		if (Condutores.at(i).ID_Motorista == id) {
			return i;
		}
	}
	return -1;
}

//MENUS MENUS MENUS
//FUNÇÃO RESPONSÁVEL POR LIDAR COM INPUTS INVÁLIDOS NO MENU PRINCIPAL/RESTANTES MENUS DA EMPRESA SEMPRARROLAR
void ErrorErrorError(int &i) {
	while (cin.fail()) {
		cout << "Introduziu uma resposta errada, introduza novamente. ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> i;
	}
}
void InvalidInputMenu() {
	if (cin.fail())
	{
		cout << "\nIntroduziu uma resposta invalida. Por favor, tente de novo. \n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		MenuPrincipal();
	}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		MenuPrincipal();
	}
}
void InvalidInputFicheiro()
{
	cout << "\nIntroduziu uma resposta invalida. Por favor, tente de novo. \n\n";
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		streamsLinhasECondutores();
	}
	else
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		streamsLinhasECondutores();
	}
}
int VerificarIDLinhas(int id) {
	int flag = 0;
	int newid;
	for (unsigned int i = 0; i < Linhas.size(); i++) {
		if (Linhas.at(i).ID == id) {
			flag = 1;
			newid = i;
		}
	}
	if (flag == 1) {
		return newid;
	}
	else {
		cout << "Introduziu um ID incorreto, por favor tente novamente.";
		return -1;
	}
}
int VerificarIDCondutores(int id) {
	int flag = 0;
	int newid;
	for (unsigned int i = 0; i < Condutores.size(); i++) {
		if (Condutores.at(i).ID_Motorista == id) {
			flag = 1;
			newid = i;
		}
	}
	if (flag == 1) {
		return newid;
	}
	else {
		cout << "Introduziu um ID incorreto, por favor tente novamente.";
		return -1;
	}
}

//MENU
//FUNÇÃO RESPOSÁVEL PARA ORGANIZAÇÃO DE HORÁRIOS
void InfHorario() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nHORARIOS\n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Linhas\n";
	cout << "2) Paragens\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;

		switch (options) {

		case 0:
			MenuPrincipal();
			break;

		case 1:
			HorariosLinhas();
			break;

		case 2:
			HorariosParagens();
			break;
		}
	}
}

//MENU
//Função para informação de Linha e Condutores
void Informacoes() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nINFORMACOES\n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Horarios\n";
	cout << "2) Linhas\n";
	cout << "3) Percursos\n";
	cout << "4) Condutores\n";
	cout << "5) Linhas em Paragens\n";
	cout << "6) Calcular tempo entre Paragens\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;

		switch (options) {

		case 0:
			MenuPrincipal();
			break;

		case 1:
			InfHorario();
			break;

		case 2:
			VerLinhasExistentes();
			break;

		case 3:
			VerPercursosExistentes();
			break;

		case 4:
			VerCondutoresExistentes();
			break;

		case 5:
			LinhasParagens();
			break;
			//in case of wrong input

		case 6:
			CalcularTempoParagens();
			break;

		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Função para geração de Linhas
void GESTLINHA() {
	int options;
	options = -1;;
	cout << "========================================================================================================";
	cout << "\nGESTAO DE LINHAS \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Adicionar Linhas\n";
	cout << "2) Remover Linhas\n";
	cout << "3) Alterar Linhas\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			AdicionarLinha();
			break;
		case 2:
			RemoverLinha();
			break;
		case 3:
			AlterarLinhaMenu();
			break;

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Função para geração de Condutores
void GESTCOND() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nGESTAO DE CONDUTORES \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Adicionar Condutores \n";
	cout << "2) Remover Condutores\n";
	cout << "3) Alterar Condutores\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	//cenas cenas cena
	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			AdicionarCondutor();
		case 2:
			RemoverCondutor();
		case 3:
			AlterarCondutorMenu();

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Função para gravar ficheiros
void MenuGravarFicheiro() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nGRAVAR FICHEIROS \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Gravar ficheiro de condutores\n";
	cout << "2) Gravar ficheiro de linhas\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";

	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			SaveFicheiroCondutores();
		case 2:
			SaveFicheiroLinhas();
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Função para Menu Principal
void MenuPrincipal() {
	vector<string> input;
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << " \nBem-Vindo ao Menu Principal do programa Escalonamento de Condutores, da Empresa de Transportes Semprarrolar.\n";
	cout << " Por favor escolha um numero como opcao. \n";
	cout << " 1) Gestao de Linhas.\n";
	cout << " 2) Gestao de Condutores.                                __________________\n";
	cout << " 3) Informacoes.                                        |            TM  D \\\n";
	cout << " 4) Gravar Ficheiro                                     |SEMPRARROLAR||    |\n";
	cout << " 0) Terminar programa.                             ooo0O|_ (o) ______|| (o)/\n";
	cout << "========================================================================================================\n\n";


	while (!cin.fail())
	{
		cin >> options;
		switch (options) {
		case 0:
			cout << "=============================================================\n";
			cout << "\nTerminando programa, aguarde...\n\n";
			cout << "=============================================================";
			cout << "\nObrigado pela sua colaboracao, volte em breve!\n\n\n";
			cout << " ___ ___ __ __ ___ ___ ___ ___ ___ ___ _   ___ ___ " << endl;
			cout << "/ __| __|  \\  | . | . | . | . | . | . | | | . | . \\   TM" << endl;
			cout << "\\__ | _>|     |  _|   |   |   |   | | | |_|   |   /" << endl;
			cout << "<___|___|_|_|_|_| |_\\_|_|_|_\\_|_\\_`___|___|_|_|_\\_\\ " << endl;
			cout << "=============================================================";
			cout << "\n\n";
			exit(0);
		case 1:
			GESTLINHA();
			break;
		case 2:
			GESTCOND();
			break;
		case 3:
			Informacoes();
			break;
		case 4:
			MenuGravarFicheiro();
			break;
		default:
			InvalidInputMenu();
			break;
		}
	}
}


//OUTRAS FUNÇÕES
int Commas(string stringe) {
	char checkCharacter = ',';
	int count = 0;

	for (unsigned int i = 0; i < stringe.size(); i++)
	{
		if (stringe[i] == checkCharacter)
		{
			++count;
		}
	}

	return count;
}

//MAIN
int main() {
	streamsLinhasECondutores();

	MenuPrincipal();

	system("PAUSE");
	return 0;
}