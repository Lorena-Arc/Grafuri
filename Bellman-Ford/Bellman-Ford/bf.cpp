
/// Afiseaza costul drumului de la un nod s la celelate noduri
/// Merge cu costuri negative
/// Complexitate O(E*V)

#include <fstream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
#include <iostream>
#include <string>

using namespace std;

const int Inf = 0x3f3f3f3f;

struct Pair {
    int node, dist;
    bool operator < (const Pair& p) const
    {
        return dist > p.dist;
    }
};

using VP = vector<Pair>; // vector de pair
using VVP = vector<VP>;
using VI = vector<int>; // vector de int

bool bellman_ford();
void citire(string input);
void afisare(string output);

vector<vector<Pair>>G;
vector<int> d;
int n, e, s;


int main(int argc, char** argv)
{


	citire(argv[1]);
	
    bool ok = bellman_ford();

    if (ok)
        afisare(argv[2]);
    
}



bool bellman_ford()
{
    d = vector<int>(n, Inf); //initializare
    d[s] = 0;

    for(int i = 1; i <= n - 1; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < G[j].size(); ++k)
            {
                int u = j;
                int v = G[j][k].node;
                int w = G[j][k].dist;

                if (d[v] > d[u] + w)
                    d[v] = d[u] + w;
            }

    for (int j = 0; j < n; ++j)
        for(int k = 0; k < G[j].size(); ++k)
        {
            int u = j;
            int v = G[j][k].node;
            int w = G[j][k].dist;

            if (d[v] > d[u] + w)
                return false;
        }

    return true;
}

void citire(string input){
	
	ifstream fin(input);
	
	int x, y, w;

    fin >> n >> e >> s;

    G = vector<vector<Pair>>(n);

    while (fin >> x >> y >> w){
        G[x].push_back({ y, w });
	}
		
	fin.close();
}

void afisare(string output){
	
	ofstream fout(output);
	
	for (int i = 0; i < n; ++i)
        if (d[i] == Inf)
            fout << "Inf" << ' ';
        else
            fout << d[i] << ' ';
            
    fout.close();
}
