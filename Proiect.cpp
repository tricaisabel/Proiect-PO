#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "clase.h"
using namespace std;


// verifica daca tabelul exista
bool tabelul_exista(string nume_tabel, database& d) {
	for (int i=0;i<d.tabele.size();i++)
	{
		if (d.tabele[i]->afiseaza_nume_tabel() == nume_tabel) 
		{
			return true;
		}
	}
	return false;
}


// functie pentru prelucrarea comenzilor primite
bool prelucrare_comanda(vector<string> comanda, database& d) {
	// daca nu primim nicio comanda, continuam sa citim comenzi
	if (comanda.size() == 0) 
	{
		return true;
	}

	// inchide citirea de la tastatura, inchide programul
	else if (comanda[0] == "exit") {
		return false;
	}

	// comanda: CREATE TABLE <nume_tabel>
	else if (comanda[0] == "CREATE")
	{
		// trebuie sa avem cel putin 3 parametri
		if (comanda.size() >= 7)
		{
			if (comanda[1] == "TABLE") 
			{
				// verifica daca exista tabelul
				if (tabelul_exista(comanda[2], d)) 
				{
					cout << "> Tabelul cu numele " << comanda[2] << " exista!" << endl;
				}
				else 
				{
					// inseram un nou tabel daca nu exista
					//citim restul parametriilor
					vector<string> parametrii;
					for (int i = 3; i < comanda.size(); i++)
					{
						parametrii.push_back(comanda[i]);
					}
					d.Create_table(comanda[2], parametrii);
					cout << "> Tabelul " << comanda[2] << " a fost adaugat cu succes!" << endl;
				}
			}
		}
		else {
			cout << "> Comanda incompleta!\n> UTILIZARE: CREATE TABLE <nume_tabel> nume_coloana1 tip1 dimensiune1 nume_coloana2 tip 2 etc." << endl;
		}
	}

	// comanda: DROP TABLE <nume_tabel>
	else if (comanda[0] == "DROP") {
		// trebuie sa avem cel putin 3 parametri
		if (comanda.size() >= 3) {
			if (comanda[1] == "TABLE") {
				if (tabelul_exista(comanda[2], d)) 
				{
					d.Drop_table(comanda[2]);
				}
				else
				{
					cout << "> Tabelul cu numele " << comanda[2] << " nu exista!" << endl;
				}
			}
		}
		else 
		{
			cout << "> Comanda incompleta!\n> UTILIZARE: DROP TABLE <nume_tabel>" << endl;
		}
	}

	// comanda: DISPLAY TABLE <nume_tabel>
	else if (comanda[0] == "DISPLAY") 
	{
		// trebuie sa avem cel putin 3 parametri
		if (comanda.size() >= 3) 
		{
			if (comanda[1] == "TABLE")
			{
				if (tabelul_exista(comanda[2], d))
				{
					d.Display_table(comanda[2]);
				}
				else
				{
					cout << "> Tabelul cu numele " << comanda[2] << " nu exista!" << endl;
				}
			}
		}
		else 
		{
			cout << "> Comanda incompleta!\n> UTILIZARE: DISPLAY TABLE <nume_tabel>" << endl;
		}
	}

	// comanda SELECT ALL FROM <nume_tabel>
	else if (comanda[0] == "SELECT" && comanda[1] == "ALL" && comanda[2]=="FROM")
	{
		if (comanda.size() >= 4)
		{
			if (tabelul_exista(comanda[3], d))
			{
				if (comanda.size() ==8)
				{
					if (comanda[4] == "WHERE")
					{
						d.Select_All(comanda[3], comanda[5], comanda[7]);
					}
				}
				else
				{
					d.Select_All(comanda[3], "", "");
				}
			}
			else
			{
				cout << "> Tabelul cu numele " << comanda[4] << " nu exista!" << endl;
			}
		}
		else
		{
			cout << "> Comanda incompleta!\n> UTILIZARE: SELECT ALL FROM  <nume_tabel>" << endl;
		}
	}

	// comanda SELECT coloana_1 coloana_2 ... FROM <nume_tabel>
	else if (comanda[0] == "SELECT" && comanda[1]!="ALL")
	{
	if (comanda.size() >= 4)
	{
		vector<string> coloane;
		int pos = 1;
		while (comanda[pos] != "FROM")
		{
			coloane.push_back(comanda[pos]);
			pos++;
		}

		if (tabelul_exista(comanda[pos+1], d))
		{
			d.Select(comanda[pos+1],coloane);
		}
		else
		{
			cout << "> Tabelul cu numele " << comanda[pos+1] << " nu exista!" << endl;
		}
	}
	else
	{
		cout << "> Comanda incompleta!\n> UTILIZARE: SELECT coloana_1 coloana_2 ... FROM  <nume_tabel>" << endl;
	}
	}

	//comanda INSERT INTO <nume_tabela> VALUES(...)
	else if (comanda[0] == "INSERT" && comanda[1] == "INTO")
	{
		if (comanda.size() >= 4 && comanda[3]=="VALUES")
		{
			if (tabelul_exista(comanda[2], d))
			{
				vector<string> values;
				for (int i = 4; i < comanda.size(); i++)
				{
					values.push_back(comanda[i]);
				}
				d.Insert(comanda[2], values);
			}
			else
			{
				cout << "> Tabelul cu numele " << comanda[2] << " nu exista!" << endl;
			}
		}
		else
		{
			cout << "> Comanda incompleta!\n> UTILIZARE: SELECT ALL FROM  <nume_tabel>" << endl;
		}
	}

	//comanda UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare
	else if (comanda[0] == "UPDATE")
	{
		if (comanda.size() == 10 && comanda[2]=="SET" && comanda[6]=="WHERE" && comanda[4]=="=" && comanda[8]=="=" )
		{
			string nume_tabel = comanda[1];
			string coloana_where = comanda[7];
			string valoare_where = comanda[9];
			string coloana_set = comanda[3];
			string valoare_set = comanda[5];
			bool ok=d.Update(nume_tabel, coloana_where, valoare_where, coloana_set, valoare_set);
			if (ok == true)
			{
				cout << "\n> Valoarea a fost modificata" << endl;
			}
		}
		else
		{
			cout << "> Comanda incompleta!\n> UTILIZARE: UPDATE <nume_tabela> SET <nume_coloana> = valoare WHERE <nume_coloana> = <valoare>" << endl;
		}
	}

	else 
	{
		cout << "> Comanda incorecta!" << endl;
	}

	return true;
}

void citire_comenzi() 
{
	// cat timp se citeste de la tastatura
	bool seCiteste = true;
	database d;

	while (seCiteste)
	{
		string linie;
		cout << "\nIntroduceti comanda:" << endl;
		getline(cin, linie);
		istringstream iss(linie);
		// imparte linia in vector de cuvinte
		vector<string> comanda((istream_iterator<string>(iss)), istream_iterator<string>());
		seCiteste = prelucrare_comanda(comanda, d);
	}
}

void main()
{
	citire_comenzi();
}