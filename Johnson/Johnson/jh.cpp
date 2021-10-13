#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
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
vector<vector<int>> d;


bool BF(int n, int s, VI& d);
void Dijkstra(int n, int s, VI& d); // x - nod sursa, d - referinta la lista de distante
bool Johnson(int n, VI& h, VVI& d);
void citire_graf(string input);
void afisare_graf(string output);


int main(int argc, char* argv[])
{
	
	citire_graf(argv[1]);

	if (jh)
	{
		bool ok = Johnson(n, h, d);
			if (ok)
			{
				afisare_graf(argv[2]);

			}
			else{
				ofstream fout(argv[2]);
				fout << -1;
				fout.close();
			}
	}
	else {

		for (int i = 0; i < n; ++i)
			Dijkstra(n, i, d[i]);

		afisare_graf(argv[2]);

	}
	

}

bool BF(int n,  int s, VI& d)
{
	//initializare
	d = VI(n, Inf);
	d[s] = 0;

	//Pas2
	int u, v, w;

	for (int i = 1; i <= n - 1; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < G[j].size(); ++k) {
				u = j;
				v = G[j][k].node;
				w = G[j][k].dist;

				if (d[v] > d[u] + w)
					d[v] = d[u] + w;
			}

		}
	}

	//Pas 3
	for (int j = 0; j < n; ++j) {
		for (int k = 0; k < G[j].size(); ++k) {
			u = j;
			v = G[j][k].node;
			w = G[j][k].dist;

			if (d[v] > d[u] + w)
				return false;
		}

	}

	return true;

}

void Dijkstra(int n, int s, VI& d)
{
	d = VI(n, Inf);
	priority_queue<Pair> Q; // primul el e mereu cel mai mic

	d[s] = 0;
	Q.push({ s, 0 }); // pui sursa in coada

	int u, y, w, dist;

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
			if (d[y] > d[u] + w) // Practic Relax-ul
			{
				d[y] = d[u] + w;
				Q.push({ y, d[y] });
			}
		}
	}
}

bool Johnson(int n, VI& h, VVI& d)
{

	cout << n << '\n';
	for (int i = 0; i < n; ++i)
		G[n].push_back({ i, 0 });

	if (!BF(n + 1, n, h))
		return false;


	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < G[i].size(); ++j) {
			G[i][j].dist += h[i] - h[G[i][j].node];
			cout << i << " " << G[i][j].node << " " << G[i][j].dist << "\n";
		}
	}

	for (int i = 0; i < n; ++i)
	{
		Dijkstra(n, i, d[i]);
		for (int j = 0; j < n; ++j) 
			d[i][j] = d[i][j] - h[i] + h[j];
			
	}
	return true;
}

void citire_graf(string input){
	ifstream fin(input);
	
	int x, y, w;
	
	fin >> n >> e; // varfuri, muchii, sursa

	G = vector<vector<Pair>>(n + 1);
	d = vector<vector<int>>(n);

	while (fin >> x >> y >> w)
	{
		G[x].push_back({ y, w }); // Lista de adiacenta de pair uri
		if (w < 0)
			jh = true;
	}
	fin.close();
}

void afisare_graf(string output){
	ofstream fout(output);
	
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < G[i].size(); ++j)
			fout << i << " " << G[i][j].node << " " << G[i][j].dist << "\n";
		}

	for (int i = 0; i < n; ++i, fout << "\n")
		for (int j = 0; j < n; ++j)
			if (d[i][j] < Inf - 1000)
				fout << d[i][j] << " ";
			else
				fout << "INF ";
				
	fout.close();
}

