#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
#include <algorithm>
using namespace std;

const int Inf = 0x3f3f3f3f;


struct Pair {
	int node, dist;
	bool operator < (const Pair& p) const
	{
		return p.dist < dist;
	}
};

using VP = vector<Pair>;
using VVP = vector<VP>;
using VI = vector<int>;
using VVI = vector<VI>;


bool jh;
int n, e;
vector<int> h;  // d[x] = dist minima de la sursa la nodul x
vector<vector<Pair>> G; // vector de vector de pairs
vector<int> d;
vector<int> costuri_cicluri; 
vector<vector<int>> parinti;
vector<vector<int>> cicluri;

void Dijkstra(int n, int s, VI& d, VI&p); // x - nod sursa, d - referinta la lista de distante
void citire_graf(string input);
void afisare_graf(string output);
void afisare_ciclu(int i);

int main(int argc, char* argv[])
{
	
	citire_graf(argv[1]);

	for (int i = 0; i < n; ++i)
		Dijkstra(n, i, d, parinti[i]);
	
	afisare_graf(argv[2]);

}



void Dijkstra(int n, int s, VI& d, VI& P)
{
	d = VI(n, Inf);
	priority_queue<Pair> Q; // primul el e mereu cel mai mic

	//d[s] = 0;
	Q.push({ s, 0 }); // pui sursa in coada

	int u, y, w, dist;
	P = vector<int>(n);

	while (!Q.empty()) // cat timp coada nu e vida
	{
		u = Q.top().node;
		dist = Q.top().dist;
		Q.pop();
		//luam cel mai mic si il stergem apoi

		if (dist > d[u]) // daca distanta actuala e mai mare decat cea din lista, nu ne pasa
			continue;

		//pt fiecare element de pe linia lui u
		for (auto& p : G[u])
		{
			y = p.node;
			w = p.dist;
			
			if(u == s){
				if(d[y] > w){
					d[y] = w;
					P[y] = u;
					Q.push({y, d[y]});
				}
			}
			else if (d[y] > d[u] + w) // Practic Relax-ul
			{
				d[y] = d[u] + w;
				P[y] = u;
				Q.push({ y, d[y] });
			}
		}
	}
	costuri_cicluri.push_back(d[s]);
}

void citire_graf(string input){
		

	ifstream fin(input);
	
	int x, y, w;
	
	fin >> n >> e; // varfuri, muchii, sursa

	G = vector<vector<Pair>>(n + 1);
	d = vector<int>(n);

	parinti = vector<vector<int>>(n);

	while (fin >> x >> y >> w)
		G[x].push_back({ y, w }); // Lista de adiacenta de pair uri
	
	fin.close();
}

void afisare_graf(string output){
	ofstream fout(output);
	
	
	int min_c = *min_element(costuri_cicluri.begin(), costuri_cicluri.end());
	
	
	for(size_t i = 0; i < costuri_cicluri.size(); ++i)
	{	
		if(costuri_cicluri[i] == min_c)
		afisare_ciclu(i);
	}
	
	for(auto& v: cicluri){
		reverse(v.begin(), v.end());
		
		for(auto i: v)
			fout << i << ' ';
			
		fout << '\n';
		
	}
				
	fout.close();
}

void afisare_ciclu(int i){
		
	int p = parinti[i][i];	
		
	vector<int> v;
	cicluri.push_back(v);
	
	int x = cicluri.size() -1;
	
	while(true){
		cicluri[x].push_back(p);
		
		if(p == i){
			break;
		}
		
		p = parinti[i][p];
		
		
	}
}

