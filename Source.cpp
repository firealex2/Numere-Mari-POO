#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class NumarIntregMare {

	vector <int> cifre; //v[0] = 0 daca e numar negativ sau 1 daca e pozitiv

	friend istream& operator >> (istream&, NumarIntregMare&);
	friend ostream& operator << (ostream&, NumarIntregMare&);
	friend NumarIntregMare& operator + (NumarIntregMare&, NumarIntregMare&);
	friend NumarIntregMare& operator - (NumarIntregMare&, NumarIntregMare&);
	friend NumarIntregMare& operator * (NumarIntregMare&, NumarIntregMare&);
	friend NumarIntregMare& maxim_nr_mari(NumarIntregMare&, NumarIntregMare&);

};


NumarIntregMare& maxim_nr_mari(NumarIntregMare& a, NumarIntregMare& b) {

	if (a.cifre.size() < b.cifre.size())
		return b;
	else if (a.cifre.size() > b.cifre.size()) return a;

	for (int i = 1;i < b.cifre.size();i++)
	{
		if (a.cifre[i] > b.cifre[i])
			return a;
		else return b;
	}

	return a;
}

istream& operator >> (istream& in, NumarIntregMare& numar_mare)
{
	string numar_citit;
	in >> numar_citit;

	int start;

	if (numar_citit[0] == '-')
	{
		start = 1;
		numar_mare.cifre.push_back(0);
	}
	else
	{
		start = 0;
		numar_mare.cifre.push_back(1);
	}

	for (int i = numar_citit.length() - 1; i >= start; i--)
		numar_mare.cifre.push_back(numar_citit[i] - '0');

	return in;
}

ostream& operator << (ostream& out, NumarIntregMare& numar_mare)
{
	if (numar_mare.cifre[0] == 0)
		out << '-';

	for (int i = numar_mare.cifre.size() - 1; i >= 1; i--)
		out << numar_mare.cifre[i];

	return out;
}

NumarIntregMare& operator + (NumarIntregMare& numar1, NumarIntregMare& numar2)
{
	NumarIntregMare suma;

	int suma_partiala = 0;
	int semn = 1;

	if (numar1.cifre[0] == 0 && numar2.cifre[0] == 0)
		semn = 0;
	else if (numar1.cifre[0] == 0)
	{
		numar1.cifre[0] = 1;
		return numar2 - numar1;
	}
	else if (numar2.cifre[0] == 0)
	{
		numar2.cifre[0] = 1;
		return numar1 - numar2;
	}


	suma.cifre.push_back(semn);

	int i = 1, j = 1;

	while (i < numar1.cifre.size() || j < numar2.cifre.size())
	{
		int cifra1 = 0, cifra2 = 0;

		if (i < numar1.cifre.size())
			cifra1 = numar1.cifre[i];

		if (j < numar2.cifre.size())
			cifra2 = numar2.cifre[j];

		suma_partiala += cifra1 + cifra2;

		suma.cifre.push_back(suma_partiala % 10);
		suma_partiala /= 10;

		i++;
		j++;

	}

	if (suma_partiala != 0)
		suma.cifre.push_back(suma_partiala);

	numar1 = suma;

	return numar1;
}

NumarIntregMare& operator - (NumarIntregMare& numar1, NumarIntregMare& numar2)
{

	NumarIntregMare scadere;
	int semn = 1, scadere_partiala = 0;
	NumarIntregMare nr_aux;

	if (numar1.cifre[0] == 0 && numar2.cifre[0] == 0)
	{
		numar1.cifre[0] = 1;
		numar2.cifre[0] = 1;

		return numar2 - numar1;
	}

	if (numar1.cifre[0] == 0 && numar2.cifre[0] == 1)
	{
		numar1.cifre[0] = numar2.cifre[0] = 0;
		return numar1 + numar2;
	}

	if (numar1.cifre[0] == 1 && numar2.cifre[0] == 0)
	{
		numar1.cifre[0] = 1;
		numar2.cifre[0] = 1;

		return numar1 + numar2;
	}

	if (numar1.cifre == numar2.cifre)
	{
		vector<int> zero(2, 0);
		zero[0] = 1;
		numar1.cifre = zero;

		return numar1;
	}

	

	scadere = maxim_nr_mari(numar1, numar2);

	if (scadere.cifre == numar1.cifre)
		nr_aux = numar2;
	else {
		nr_aux = numar1;
		semn = 0;
	}

	int i = 1, tip = 0;
	while (i < nr_aux.cifre.size())
	{
		int cifra1, cifra2;

		if (tip)
			scadere_partiala = 1;
		else scadere_partiala = 0;
		
		tip = 0;

		if (i < nr_aux.cifre.size())
		{
			cifra1 = scadere.cifre[i];
			cifra2 = nr_aux.cifre[i];
		}

		scadere_partiala = cifra1 - cifra2 - scadere_partiala;

		if (scadere_partiala < 0)
		{
			scadere_partiala = 10 + scadere_partiala;
			tip = 1;
		}

		scadere.cifre[i] = scadere_partiala;
		i++;
	}

	scadere.cifre[0] = semn;

	while (tip)
	{
		scadere.cifre[i]--;
		if (scadere.cifre[i] < 0)
			scadere.cifre[i] = 10 + scadere.cifre[i];
		else tip = 0;
		i++;
	}


	i = scadere.cifre.size() - 1;
	while (scadere.cifre[i] == 0)
	{
		scadere.cifre.pop_back();
		i--;
	}

	numar1 = scadere;

	return numar1;
}

NumarIntregMare& operator * (NumarIntregMare& numar1, NumarIntregMare& numar2)
{
	NumarIntregMare produs;
	int semn = 1, produs_partial = 0;
	produs.cifre = vector<int>(2, 0);

	semn = numar1.cifre[0] * numar2.cifre[0];

	produs.cifre[0] = 1;

	int i = 1, j = 1;
	while (i < numar1.cifre.size())
	{
		int cifra1 = numar1.cifre[i];
		j = 1;
		NumarIntregMare produs_aux;
		produs_aux.cifre.push_back(1);
		produs_partial = 0;

		for (int k = 1;k < i;k++)
			produs_aux.cifre.push_back(0);

		while (j < numar2.cifre.size())
		{
			int cifra2 = numar2.cifre[j];
			produs_partial += cifra1*cifra2;
			produs_aux.cifre.push_back(produs_partial % 10);
			produs_partial /= 10;
			j++;
		}

		if (produs_partial != 0)
			produs_aux.cifre.push_back(produs_partial);

		produs = produs + produs_aux;

		i++;
	}


	produs.cifre[0] = semn;
	numar1 = produs;

	return numar1;
}

int main()
{
	NumarIntregMare numar1, numar2, numar3;
	
	cout << "Introduceti doua numere mari: \n";

	cin >> numar1 >> numar2;

	numar3 = numar1 + numar2;
	cout << "Suma numerelor: " << numar3 << "\n";
	numar3 = numar1 - numar2 - numar2;
	cout << "Diferenta numerelor: " << numar3 << "\n";
	numar3 = (numar1 + numar2) * numar2;
	cout << "Produsul numerelor: " << numar3 << "\n";

	
	return 0;
}