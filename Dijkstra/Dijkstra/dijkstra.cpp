/// Afiseaza drumul minim dintre un nod s si toate celelalte noduri
/// Foloseste costuri
/// Foloseste o lista de adiacenta

#include <fstream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
#include <iostream>
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
using VVP = vector<VP>; // vector de vector de pair // matrice de pair
using VI = vector<int>; // vector de int

//s nod sursa
//n numarul de varfuri
//referinta la un vector de vector de pair 
//d referinta la o lista de distante
void Dijkstra();
void citire(string input);
void afisare(string output);

vector<vector<Pair>> G;
vector<int> d;
int n, s;

int main(int argc, char** argv)
{
	citire(argv[1]);

    Dijkstra();

    afisare(argv[2]);
   
}

void Dijkstra()
{
    d = vector<int>(n, Inf);
    priority_queue<Pair> Q;

    d[s] = 0;
    Q.push({ s, 0 });

    int y, w, dist, u;
    while (!Q.empty())
    {
        u = Q.top().node;
        dist = Q.top().dist;
        Q.pop();
        if (dist <= d[u])
        {
            for (auto& p : G[u])
            {
                y = p.node;
                w = p.dist;
                if (d[y] > d[u] + w)
                {
                    d[y] = d[u] + w;
                    Q.push({ y, d[y] });
                }
            }
        }
    }
}

void citire(string input){
	ifstream fin(input);
	
	int e, x, y, w;

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
