
/* Determinarea componentelor Tare-Conexe
 * pr un Graf Orientat
 * Algoritmul lui Kosaraju
 * O(n + m) (de 2 ori) - time Complexity
 * O(m) de 2 ori       - Memory Complexity 
 */ 
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
using namespace std;

using VI  = vector<int>;
using VVI = vector<VI>;
using VB  = vector<bool>;

vector<vector<int>> G, GT;  // graful, graful transpus
vector<bool> v;       // marcam nodurile vizitate

stack<int> stk; // retine nodurile la parcurgerea Df
                // in ordinea terminarii lor
                
vector<int> c;           // comp tare conexa curenta

vector<vector<int>> ctc;        // retine ca vectori toate comp tare conexe  

int n, m;            // noduri, arce

void CitesteGraf(string input);
void Kosaraju();     // det comp tare conexe
void Df(int x);
void DfT(int x);     // parcurgere pe graful Transpus
void AfiseazaCompTareConexe(string output);


int main(int argc, char** argv)
{
	CitesteGraf(argv[1]);
	Kosaraju();
	AfiseazaCompTareConexe(argv[2]);
}  

void CitesteGraf(string input)
{
	ifstream fin(input);
	
	fin >> n >> m;
	G = GT = vector<vector<int>>(n);
	v = vector<bool>(n);
	
	int x, y;
	while(fin >> x >> y){
		
		G[x].emplace_back(y);
		GT[y].emplace_back(x);
	}
	
	fin.close();
}

void Kosaraju()
{
	for (int x = 0; x < n; ++x)
		if (!v[x])
			Df(x);
	
	v.assign(n, false);
	
	int x;
	while (!stk.empty())
	{
		x = stk.top(); stk.pop();
		if (v[x]) continue;
		c.clear();
		DfT(x);
		ctc.emplace_back(c);
	}
}

void Df(int x)
{
	v[x] = true;
	for (const auto& y : G[x])
	{
		if (v[y]) continue;
		Df(y);
	}
	stk.push(x);
}

void DfT(int x)     // parcurgere pe graful Transpus
{
	v[x] = true;
	c.emplace_back(x);
	
	for (const auto& y : GT[x])
	{
		if (v[y]) continue;
		DfT(y);
	} 
}

void AfiseazaCompTareConexe(string output)
{
	ofstream fout(output);
	
	fout << ctc.size() << '\n';
	
	for (const auto& comp : ctc)
	{
		for (const auto& x : comp)
			fout << x << ' ';
		fout << '\n';
	}
	
	fout.close();
}
