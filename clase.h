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
	string get()
	{
		return val_txt;
	}
	void set(string x)
	{
		val_txt = x;
	}
	friend ostream& operator<<(ostream& out, valoare_text v);
};

ostream& operator<<(ostream& out, valoare_text v)
{
	out << v;
	return out;
}

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
	string get()
	{
		return to_string(val_int);
	}
	void set(string x)
	{
		val_int = stoi(x);
	}
	friend ostream& operator<<(ostream& out, valoare_int v);
};

ostream& operator<<(ostream& out, valoare_int v)
{
	out << v;
	return out;
}

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

	string get()
	{
		return to_string(val_float);
	}
	void set(string x)
	{
		val_float = stof(x);
	}
	friend ostream& operator<<(ostream& out, valoare_float v);
};

ostream& operator<<(ostream& out, valoare_float v)
{
	out << v;
	return out;
}

class coloana
{
protected:
	vector<valoare*> valori;
	string nume;
	string tip;
	static string val_implicita;
	int dimensiune;
public:
	coloana()
	{
		nume = "";
		tip = "";
		dimensiune = 0;
	}
	coloana(string nume, string tip, int dimensiune, string implicita)
	{
		this->nume = nume;
		this->tip = tip;
		this->dimensiune = dimensiune;
		val_implicita = implicita;
	}

	void setColoana(string nume, string tip, int dimensiune, string implicita)
	{
		this->nume = nume;
		this->tip = tip;
		this->dimensiune = dimensiune;
		val_implicita = implicita;
	}
	void adaugare_valoare(int x)
	{
		valori.push_back(new valoare_int(x));
	}
	void adaugare_implicita(string tip)
	{
		if (tip == "integer")
		{
			valori.push_back(new valoare_int(stoi(val_implicita)));
		}
		else if (tip == "float")
		{
			valori.push_back(new valoare_float(stof(val_implicita)));
		}
		else if (tip == "text")
		{
			valori.push_back(new valoare_text(val_implicita));
		}
	}
	void adaugare_valoare(float x)
	{
		valori.push_back(new valoare_float(x));
	}
	void adaugare_valoare(string x)
	{
		valori.push_back(new valoare_text(x));
	}
	void afisare_valori()
	{
		for (int i = 0; i < valori.size(); i++)
		{
			valori[i]->afiseaza();
			cout << endl;
		}
	}
	void afisare_coloana()
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
	vector<valoare*> getValori()
	{
		return valori;
	}
};
string coloana::val_implicita = "";

class tabel
{
protected:
	vector<coloana*> coloane;
	string nume_tabel;
public:
	tabel()
	{
		nume_tabel = "";
	}
	tabel(string nume)
	{
		this->nume_tabel = nume;
	}
	tabel(string nume_tabel, vector<string> s)
	{
		string nume, tip, val_implicita;
		int dimensiune;
		this->nume_tabel = nume_tabel;
		coloana c;
		for (int i = 0; i < s.size(); i = i + 4)
		{
			nume = s[i];
			tip = s[i + 1];
			dimensiune = stoi(s[i + 2]);
			val_implicita = s[i + 3];
			coloane.push_back(new coloana(nume, tip, dimensiune, val_implicita));
		}
	}
	void adaugare_coloana(coloana& c)
	{
		coloane.push_back(&c);
	}
	void display_table()
	{

	}
	void afisare_valori_coloana(string nume)
	{
		cout << "Datele din coloana " << nume << endl;
		cout << "------------------------------------\n";
		for (int i = 0; i < coloane.size(); i++)
		{
			if (coloane[i]->getNumeC() == nume)
			{
				coloane[i]->afisare_valori();
			}
		}
		cout << endl;
	}
	void afisare_tabel(string nume_coloana = "", string valoare_coloana = "")
	{
		cout << endl;
		cout << "Datele din tabelul " << nume_tabel << endl;
		cout << "------------------------------------\n";
		for (int k = 0; k < coloane.size(); k++)
		{
			cout << getColoane()[k]->getNumeC() << "\t";
		}
		cout << endl;
		cout << "------------------------------------\n";
		for (int i = 0; i < coloane[0]->getValori().size(); i++)//pentru cate valori se repeta
		{
			if (nume_coloana != "" && valoare_coloana != "")
			{
				where(nume_coloana, valoare_coloana);
			}
			else
			{
				for (int k = 0; k < coloane.size(); k++)//pentru numarul coloanei
				{
					coloane[k]->getValori()[i]->afiseaza();
					cout << "\t";
				}
				cout << endl;
			}
		}
	}
	void afisare_tabel(vector<string> s, string nume_coloana = "", string valoare_coloana = "")
	{
		cout << endl;
		cout << "Datele din tabelul " << nume_tabel << endl;
		cout << "------------------------------------\n";
		for (int k = 0; k < coloane.size(); k++)
		{
			if (count(s.begin(), s.end(), getColoane()[k]->getNumeC()) != 0)//verifica daca o coloana se afla in lista de coloane de afisat
			{
				cout << getColoane()[k]->getNumeC() << "\t";
			}
		}
		cout << endl;
		cout << "------------------------------------\n";
		for (int i = 0; i < coloane[0]->getValori().size(); i++)//pentru cate valori se repeta
		{
			if (nume_coloana != "" && valoare_coloana != "")
			{
				where(nume_coloana, valoare_coloana);
			}
			else
			{
				for (int k = 0; k < coloane.size(); k++)//pentru numarul coloanei
				{
					if (count(s.begin(), s.end(), getColoane()[k]->getNumeC()) != 0)
					{
						coloane[k]->getValori()[i]->afiseaza();
						cout << "\t";
					}
				}
				cout << endl;
			}

		}
	}
	vector<coloana*> getColoane()
	{
		return coloane;
	}
	string getNumeT()
	{
		return nume_tabel;
	}
	string afiseaza_nume_tabel() {
		return this->nume_tabel;
	}
	void where(string nume_coloana, string valoare_coloana)
	{
		for (int i = 0; i < coloane.size(); i++)
		{
			if (coloane[i]->getNumeC() == nume_coloana)
			{
				for (int j = 0; j < coloane[i]->getValori().size(); j++)
				{
					if (coloane[i]->getValori()[j]->get() == valoare_coloana)
					{
						for (int k = 0; k < coloane.size(); k++)
						{
							coloane[k]->getValori()[j]->afiseaza();
							cout << " ";
						}
					}
				}
			}
		}
	}
	void setNumeT(string nume)
	{
		nume_tabel = nume;
	}
};

class database
{
public:
	vector<tabel*> tabele;
public:

	void Create_table(string nume_tabel, vector<string> s)
	{
		tabele.push_back(new tabel(nume_tabel, s));
	}

	void Display_table(string nume)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume)
			{
				for (int j = 0; j < tabele[i]->getColoane().size(); j++)
				{
					tabele[i]->getColoane()[j]->afisare_coloana();
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
				for (int j = 0; j < tabele[i]->getColoane().size(); j++)
				{
					if (tabele[i]->getColoane()[j]->getTip() == "int")
					{
						int val = stoi(s[j]);
						tabele[i]->getColoane()[j]->adaugare_valoare(val);
					}
					else if (tabele[i]->getColoane()[j]->getTip() == "float")
					{
						float val = stof(s[j]);
						tabele[i]->getColoane()[j]->adaugare_valoare(val);
					}
					else if (tabele[i]->getColoane()[j]->getTip() == "text")
					{
						tabele[i]->getColoane()[j]->adaugare_valoare(s[j]);
					}
				}
			}
		}
	}

	void Select_All(string nume, string nume_coloana, string valoare_coloana)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume)
			{
				tabele[i]->afisare_tabel(nume_coloana, valoare_coloana);
			}
		}
	}

	void Select(string nume, vector<string> s)
	{
		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume)
			{
				tabele[i]->afisare_tabel(s);
			}
		}
	}

	void Drop_table(string nume_tabel)
	{

		for (int i = 0; i < tabele.size(); i++)
		{
			if (tabele[i]->getNumeT() == nume_tabel)
			{
				tabele[i]->getColoane().clear();
				tabele[i]->setNumeT("");
			}
		}
		cout << "> Tabelul cu numele " << nume_tabel << " a fost eliminat cu succes!" << endl;
	}

	bool Update(string nume_tabel, string coloana_where, string val_where, string coloana_set, string val_set)
	{
		for (int a = 0; a < tabele.size(); a++)
		{
			if (tabele[a]->getNumeT() == nume_tabel)
			{
				for (int i = 0; i < tabele[i]->getColoane().size(); i++)
				{
					if (tabele[i]->getColoane()[i]->getNumeC() == coloana_where)
					{
						for (int j = 0; j < tabele[i]->getColoane()[i]->getValori().size(); j++)
						{
							if (tabele[i]->getColoane()[i]->getValori()[j]->get() == val_where)
							{
								for (int k = 0; k < tabele[i]->getColoane().size(); k++)
								{
									if (tabele[i]->getColoane()[k]->getNumeC() == coloana_set)
									{
										tabele[i]->getColoane()[k]->getValori()[j]->set(val_set);
										return true;
									}
								}
								return false;
							}
						}
					}
				}
			}
		}
	}
};


