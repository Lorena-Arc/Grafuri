///LISTA DE ADIACENTA
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct Nod {
    string culoare;
    int parinte;
    int f; //timpul final
};

using V = vector<int>;
using VV = vector<V>;

const int inf = 0x3f3f3f3f;

int n;// numarul de varfuri
vector<vector<int>> G;//graful = lista de adiacenta
vector<vector<int>> padure;
vector<Nod> lista_n;
int contor;
int timp;

void citeste(string input);
void DFS();
void DFS_VISIT(int s);
void afisare(string output);

int main(int argc, char** argv)
{
    citeste(argv[1]); //graf neorientat
    
    DFS();
    
    afisare(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
    fin >> n;
    
    G = vector<vector<int>>(n);

    int x, y;
    while (fin >> x >> y)
    {

        G[x].push_back(y);
        G[y].push_back(x);
    }
    
    fin.close();

}

void DFS()
{   
    lista_n = vector<Nod>(n, {"alb", -1, -1});
	
    for (int i = 0; i < n; ++i)
        if (lista_n[i].culoare == "alb")
        {
			padure.push_back(vector<int>());
            padure[contor].push_back(i);
            
            DFS_VISIT(i);
            contor++;
        }
      
}

void DFS_VISIT(int s)
{
	timp++;
    lista_n[s].culoare = "gri";
    for (const auto& v : G[s])
        if (lista_n[v].culoare == "alb")
        {
            lista_n[v].parinte = s;
            padure[contor].push_back(v);
            DFS_VISIT(v);
        }
    lista_n[s].culoare = "negru";
	timp++;
	lista_n[s].f = timp;
}


void afisare(string output){
	ofstream fout(output);
	
	for(auto&i: padure)
	{
		for(auto& j: i)
			fout << j << " ";
			
		fout << "\n";
	
	}
	fout.close();
}
