#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <queue>

using namespace std;
class Nod {
public:
	string denumire;
	Nod* fiu_drept = nullptr;
	Nod* fiu_stang = nullptr;
	int frecventa = 0;
};

struct CmpNod
{
	bool operator()(const Nod* lhs, const Nod* rhs) const
	{
		if (lhs->frecventa == rhs->frecventa)
			return lhs->denumire > rhs->denumire;
		return lhs->frecventa > rhs->frecventa;
	}
};

void calc_alfabet(Nod* n, string cod, map<char, string>& a);
void codare_Huffman();
void afiseaza(string output);

priority_queue<Nod*, vector<Nod*>, CmpNod> myMap;
map<char, int> frecventa_caractere;
map<char, string> alfabet;
string text;

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);

	getline(fin, text);
	codare_Huffman();
	afiseaza(argv[2]);


	fin.close();
	return 0;
}

void calc_alfabet(Nod* n, string cod, map<char, string>& a)
{
	if (n->fiu_stang != nullptr)
		calc_alfabet(n->fiu_stang, cod + "0", a);

	if (n->fiu_drept != nullptr)
		calc_alfabet(n->fiu_drept, cod + "1", a);

	if (n->denumire.size() == 1)
		a[n->denumire.at(0)] = cod;
	delete n;
}

void codare_Huffman()
{

	for (char x : text)
		frecventa_caractere[x]++;			//calculez pt fiecare caracter din lista frecventa.

	for (auto x : frecventa_caractere)
	{
		Nod* n = new Nod;
		n->frecventa = x.second;
		n->denumire = x.first;
		myMap.push({ n });			//introduc in arbore (frecventa, caracter).
	}

	while(myMap.size() > 1)
	{

		Nod* x = myMap.top();
		myMap.pop();
		
		Nod* y = myMap.top();
		myMap.pop();

		Nod* z = new Nod;
		z->frecventa = x->frecventa + y->frecventa;
		z->denumire = x->denumire + y->denumire;
		z->fiu_stang = x;
		z->fiu_drept = y;
		myMap.push(z);
	}

	auto z = myMap.top();
	calc_alfabet(z, "", alfabet);
}

void afiseaza(string output)
{
	ofstream fout(output);
	for (const auto& x : alfabet)
	{
		fout << x.first << " cu codul " << x.second << "\n";
	}

	fout << alfabet.size() << "\n";
	for (const auto& x : alfabet)
	{
		auto it = frecventa_caractere.find(x.first);
		int fr = it->second;
		fout << x.first << " " << fr << "\n";
	}

	for (const auto& x : text)
		fout << alfabet[x] << " ";

	fout.close();
}
