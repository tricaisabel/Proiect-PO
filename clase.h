#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class valoare
{
public:
	virtual void afiseaza() = 0;
	virtual string get() = 0;
	virtual void set(string x) = 0;
};

class valoare_text : public valoare
{
public:
	string val_txt;
	string val_imp_txt;
public:
	valoare_text()
	{
		val_txt = "";
		val_imp_txt = "";
	}
	valoare_text(string val)
	{
		val_txt = val;
	}
	void set_valoare(string val)
	{
		val_txt = val;
	}
	void afiseaza() override
	{
		cout << val_txt;
	}
	string get() override
	{
		return val_txt;
	}
	void set(string x) override
	{
		val_txt = x;
	}
};

class valoare_int : public valoare
{
private:
	int val_int;
	int val_imp_int;
public:
	valoare_int()
	{
		val_int = 0;
		val_imp_int = 0;
	}
	valoare_int(int val)
	{
		val_int = val;
	}
	void set_valoare(string val)
	{
		val_int = stoi(val);
	}
	void afiseaza() override
	{
		cout << val_int;
	}
	string get() override
	{
		return to_string(val_int);
	}
	void set(string x) override
	{
		val_int = stoi(x);
	}
};

class valoare_float : public valoare
{
private:
	float val_float;
	float val_imp_float;
public:
	valoare_float()
	{
		val_float = 0;
		val_imp_float = 0;
	}
	valoare_float(float val)
	{
		val_float = val;
	}
	void set_valoare(string val)
	{
		val_float = stof(val);
	}
	void afiseaza() override
	{
		cout << val_float;
	}

	string get() override
	{
		return to_string(val_float);
	}
	void set(string x) override
	{
		val_float = stof(x);
	}
};

class coloana
{
protected:
	int index;
	string nume;
	string tip;
	static string val_implicita;
	int dimensiune;
	static int nr_coloane;
public:
	coloana(string nume = "", string tip = "", int dimensiune = 0, string implicita = "")
	{
		this->nume = nume;
		this->tip = tip;
		this->dimensiune = dimensiune;
		val_implicita = implicita;
		nr_coloane++;
		index = nr_coloane;
	}

	void display_coloana()
	{
		cout << "Nume coloana: " << nume << endl;
		cout << "Tip coloana: " << tip << endl;
		cout << "Dimensiune: " << dimensiune << endl;
		cout << "Valoare implicita: " << val_implicita << endl;
		cout << endl;

	}
	string getTip()
	{
		return tip;
	}
	string getNumeC()
	{
		return nume;
	}
	int getIndex()
	{
		return index;
	}
};
string coloana::val_implicita = "";
int coloana::nr_coloane = -1;

bool in_lista(vector<string> lista, string coloana)
{
	bool ok = false;
	for (int i = 0; i < lista.size(); i++)
		if (lista[i] == coloana) ok = true;
	return ok;
}

class tabel
{
protected:
	string nume_tabel;
	vector<vector<valoare*>> inreg;
	vector<coloana*> coloane;
public:
	tabel(vector<string> s, string nume_tabel = "")
	{
		string nume, tip, val_implicita;
		int dimensiune;
		this->nume_tabel = nume_tabel;
		for (int i = 0; i < s.size(); i = i + 4)
		{
			nume = s[i];
			tip = s[i + 1];
			dimensiune = stoi(s[i + 2]);
			val_implicita = s[i + 3];
			coloane.push_back(new coloana(nume, tip, dimensiune, val_implicita));
		}
		for (int i = 0; i < s.size() / 4; i++)
		{
			vector<valoare*> v;
			inreg.push_back(v);
		}
	}
	void adaugare_inregistrare(vector<string> valori)
	{
		if (valori.size() != coloane.size())
		{
			cout << "\nNu sunt introduse valori pentru toate coloanele!\n";
		}
		else
		{
			for (int i = 0; i < coloane.size(); i++)
			{
				if (coloane[i]->getTip() == "integer")
				{
					inreg[i].push_back(new valoare_int(stoi(valori[i])));
				}
				if (coloane[i]->getTip() == "float")
				{
					inreg[i].push_back(new valoare_float(stof(valori[i])));
				}
				if (coloane[i]->getTip() == "text")
				{
					inreg[i].push_back(new valoare_text(valori[i]));
				}
			}
		}
	}
	friend ostream& operator<<(ostream& out, tabel t);


	void afisare_coloane(vector<string> coloana_select, string coloana_where, string valoare_where)
	{
		vector<string>::iterator it;
		for (int i = 0; i < coloane.size(); i++)
		{
			it = find(coloana_select.begin(), coloana_select.end(), coloane[i]->getNumeC());
			if (it != coloana_select.end())
			{
				cout << coloane[i]->getNumeC() << "\t";
			}
		}
		cout << "\n";
		bool it2;
		for (int i = 0; i < inreg[0].size(); i++)
		{

			for (int j = 0; j < inreg.size(); j++)
			{
				it2 = in_lista(coloana_select, coloane[j]->getNumeC());
				if (coloane[j]->getNumeC() == coloana_where && inreg[j][i]->get() != valoare_where && coloana_where != "" && valoare_where != "")
				{
					break;
				}
				if (it2)
				{
					cout << "|";
					inreg[j][i]->afiseaza();
					cout << "\t";
				}
			}
			if (it2) cout << "\n";
		}
	}

	void update_linie(int i, string coloana_set, string valoare_set)
	{
		for (int j = 0; j < inreg.size(); j++)
		{
			if (coloane[j]->getNumeC() == coloana_set)
			{
				inreg[j][i]->set(valoare_set);
			}
		}
	}

	void delete_coloana(int coloana_delete)
	{
		for (int i = 0; i < inreg.size(); ++i)
		{
			if (inreg[i].size() > coloana_delete)
			{
				inreg[i].erase(inreg[i].begin() + coloana_delete);
			}
		}
	}

	vector<coloana*> Coloane()
	{
		return coloane;
	}

	vector<vector<valoare*>> Inregistrari()
	{
		return inreg;
	}

	string getNumeT()
	{
		return nume_tabel;
	}

	vector<string> Nume_coloane()
	{
		vector<string> s;
		for (int i = 0; i < coloane.size(); i++)
		{
			s.push_back(coloane[i]->getNumeC());
		}
		return s;
	}
};
ostream& operator<<(ostream& out, tabel t)
{
	for (int i = 0; i < t.coloane.size(); i++)
	{
		out << t.coloane[i]->getNumeC() << "\t";
	}
	cout << "\n";
	for (int i = 0; i < t.coloane.size(); i++)
	{
		for (int j = 0; j < t.inreg[i].size(); j++)
		{
			cout << "|";
			t.inreg[j][i]->afiseaza();
			cout << "\t";
		}
		cout << "\n";
	}
	return out;
}

class database
{
public:
	vector<tabel*> tabele;
public:

	void Create_table(string nume_tabel, vector<string> s)
	{
		tabele.push_back(new tabel(s, nume_tabel));
	}

	void Display_table(string nume)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume)
			{
				for (int j = 0; j < tabele[i]->Coloane().size(); j++)
				{
					tabele[i]->Coloane()[j]->display_coloana();
					cout << endl;
				}
			}
		}
	}

	void Insert(string nume, vector<string> s)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume)
			{
				tabele[i]->adaugare_inregistrare(s);
			}
		}
	}

	void Select(string nume_tabel)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->afisare_coloane(tabele[i]->Nume_coloane(), "", "");
			}
		}
	}

	void Select(string nume_tabel, vector<string> s)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->afisare_coloane(s, "", "");
			}
		}
	}

	void Select(string nume_tabel, vector<string> s, string coloana_where, string valoare_where)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->afisare_coloane(s, coloana_where, valoare_where);
			}
		}
	}

	void Select(string nume_tabel, string coloana_where, string valoare_where)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->afisare_coloane(tabele[i]->Nume_coloane(), coloana_where, valoare_where);
			}
		}
	}

	void Drop_table(string nume_tabel)
	{

		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->Coloane().clear();
				tabele[i]->Inregistrari().clear();
			}
		}
		cout << "> Tabelul cu numele " << nume_tabel << " a fost eliminat cu succes!" << endl;
	}

	void Update(string nume_tabel, string coloana_where, string valoare_where, string coloana_set, string valoare_set)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				for (int j = 0; j < tabele[i]->Inregistrari()[0].size(); j++)
				{
					for (int k = 0; k < tabele[i]->Inregistrari().size(); k++)
					{
						if (tabele[i]->Coloane()[k]->getNumeC() == coloana_where && tabele[i]->Inregistrari()[k][j]->get() == valoare_where)
						{
							tabele[i]->update_linie(j, coloana_set, valoare_set);
						}
					}
				}
			}
		}
	}

	void Delete(string nume_tabel, string coloana_where, string valoare_where)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				for (int j = 0; j < tabele[i]->Inregistrari()[0].size(); j++)
				{
					for (int k = 0; k < tabele[i]->Inregistrari().size(); k++)
					{
						if (tabele[i]->Coloane()[k]->getNumeC() == coloana_where && tabele[i]->Inregistrari()[k][j]->get() == valoare_where)
						{
							tabele[i]->delete_coloana(j);
						}
					}
				}
			}
		}
	}
};


/*int main()
{
	vector<string> parametrii = { "Nume","text","15","noname","Salariu","float","10","1000.5","Varsta","integer","3","18" };
	tabel t(parametrii, "Angajati");
	vector<string> valori = { "Maria","6500.7","19" };
	t.adaugare_inregistrare(valori);
	valori = { "Maria","4500.7","21" };
	t.adaugare_inregistrare(valori);
	valori = { "Costel","1200.8","23" };
	t.adaugare_inregistrare(valori);
	valori = { "Teodor","4300.8","29" };
	t.adaugare_inregistrare(valori);

	vector<string> coloane = { "Varsta","Salariu" };
	//t.afisare_coloane(t.Nume_coloane(), "", "");

	database d;
	d.Create_table("Angajati", parametrii);
	d.Display_table("Angajati");

	d.Insert("Angajati", valori);
	valori = { "Maria","4500.7","21" };
	d.Insert("Angajati", valori);
	valori = { "Costel","1200.8","23" };
	d.Insert("Angajati", valori);
	valori = { "Maria","9200.8","83" };
	d.Insert("Angajati", valori);

	d.Select("Angajati", coloane, "Nume", "Maria");
	d.Update("Angajati", "Nume", "Maria", "Salariu", "9000");
	d.Select("Angajati");
	d.Delete("Angajati", "Nume", "Maria");
	d.Select("Angajati");

}*/
