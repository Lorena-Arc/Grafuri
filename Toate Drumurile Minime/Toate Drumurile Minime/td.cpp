
/// Afiseaza cele mai scurte drumuri de la nodul s la toate celelalte
/// Merge pe grafuri orientate/neorientate
/// Nu merge pt grafuri cu costuri!!!
/// Foloseste lista de adiacenta

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

ifstream fin("fisier.in");

using V = vector<int>;
using VV = vector<V>;
const int inf = 0x3f3f3f3f;

void citeste(string input);
void Moore(int s);
void afisare(string output);
void gasire_drumuri(int u);

int n, s, t;
vector<vector<int>> G;
vector<int> L;
vector<vector<int>> P;
vector<vector<int>> Drumuri;
vector<int> path;

int main(int argc, char** argv)
{
    citeste(argv[1]);
    Moore(s);
    gasire_drumuri(t);
 
    afisare( argv[2]);

    fin.close();

}

void citeste(string input)
{
	ifstream fin(input);
	
    fin >> n;
    fin >> s >> t;
    G = vector<vector<int>>(n);

	int x, y;

    while (fin >> x >> y)
    {
        G[x].push_back(y);
       // G[y].push_back(x);
    }
   
    fin.close();
}

void Moore(int s)
{
	L = vector<int>(n, inf); //lungimea drumurilor
    P = vector<vector<int>>(n); //parintii
    
    L[s] = 0;
    
	queue<int> Q;
    Q.push(s);

	P[s].push_back(-1);

    int x;
    while (!Q.empty())
    {
        x = Q.front();
        Q.pop();
        for (const auto& y : G[x])
        {
            if (L[y] > L[x] + 1)
            {
                L[y] = L[x] + 1;
                Q.push(y);
                P[y].clear();
                P[y].push_back(x);
            }
            else if(L[y] == L[x] + 1)
				P[y].push_back(x);
        }
    }
    

}

void afisare(string output)
{
	ofstream fout(output);
	
	
	for(const auto& v: Drumuri){
		for(int u: v)
			fout << u << ' ';
		fout << '\n';
	}
   
    fout.close();
}

void gasire_drumuri(int u){
	
	
	if(u == -1){
		Drumuri.push_back(path);
		return;
		
	}
	
	for(const auto& par: P[u]){
		path.push_back(u);
		gasire_drumuri(par);
		path.pop_back();	
	}
	  
	
}
