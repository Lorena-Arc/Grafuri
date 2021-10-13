///	PE LISTA DE ADIACENTA
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct Nod {
    string culoare;
    int nr;
    int parinte;
    int distanta;
};

using V = vector<int>;
using VV = vector<V>;

const int inf = 0x3f3f3f3f;

void citeste(string input);
void BFS(int s);
void afisare(int s, string output);

VV G;//graful = lista de adiacenta
int n;// numarul de varfuri
vector<Nod> lista_n;


int main(int argc, char** argv)
{

    citeste(argv[1]); //graf neorientat
    BFS(0);
    afisare(0, argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
    
    fin >> n;
    G = VV(n);

    int x, y;
    while (fin >> x >> y)
    {

        G[x].push_back(y);
        G[y].push_back(x);
    }
	
	fin.close();
}

void BFS(int s)
{
	//initializare
    lista_n = vector<Nod>(n);

    for (int i = 0; i < n; ++i)
    {
        lista_n[i].culoare = "alb";
        lista_n[i].nr = i;
        lista_n[i].distanta = inf;
        lista_n[i].parinte = -1;
    }
    
    lista_n[s].culoare = "gri";
    cout << s << ' ';

    queue<int> Q; //coada
    Q.push(s);

    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (auto& v: G[u])
        {
            if (lista_n[v].culoare == "alb")
            {
                lista_n[v].culoare = "gri";
                lista_n[v].distanta = lista_n[u].distanta + 1;
                lista_n[v].parinte = u;
                Q.push(v);
            }
        }
        lista_n[u].culoare = "negru";
    }
}

void afisare(int s, string output){
	
	ofstream fout(output);
	
	priority_queue<int, vector<int>, greater<int>> pq;
	
	pq.push(s);
	
	for(int i = 0; i < n; ++i)
		if(lista_n[i].parinte != -1)
			pq.push(i);
	
	while(!pq.empty())
	{
		fout << pq.top() << " ";
		pq.pop();
	}
	
	fout.close();
}
