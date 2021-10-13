#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <list>
#include <stack>
using namespace std;

struct Nod {
    string culoare;
    int nr;
    int parinte;
    int f; //timpul final
};

struct Pair {
    int node, dist;
    bool operator < (const Pair& p) const
    {
        return dist > p.dist;
    }
};

vector<vector<Pair>> G;
vector<Nod> lista_n;
stack<int> lista_inlantuita;
vector<int> d;

const int Inf = 0x3f3f3f3f;
int n, s;
int timp;

void citeste(string input);
void DFS();
void DFS_VISIT(int s);
void afisare(string output);
void sortare_topologica();
void drum_minim_dag();

int main(int argc, char** argv){
	citeste(argv[1]);
	
	drum_minim_dag();
	afisare(argv[2]);
		
}

void DFS()
{   
	for(int i = 0; i < n; ++i)
		lista_n.push_back({"alb", i, -1, -1});
	
    for (int i = 0; i < n; ++i)
        if (lista_n[i].culoare == "alb")
            DFS_VISIT(i);
      
}

void DFS_VISIT(int s)
{
	timp++;
    lista_n[s].culoare = "gri";
    for (const auto& v : G[s])
        if (lista_n[v.node].culoare == "alb")
        {
            lista_n[v.node].parinte = s;
            DFS_VISIT(v.node);
        }
    lista_n[s].culoare = "negru";
    lista_inlantuita.push(s);
	timp++;
	lista_n[s].f = timp;
}

void citeste(string input)
{
	ifstream fin(input);
    fin >> n >> s;
    
    G = vector<vector<Pair>>(n);

    int x, y, w;
    while (fin >> x >> y >> w)
        G[x].push_back({y, w});
    
    fin.close();

}

void sortare_topologica(){
	DFS();
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

void drum_minim_dag(){
	sortare_topologica();
	
	d = vector<int>(n, Inf);
	d[s] = 0;
	
	
	while(!lista_inlantuita.empty()){
		int v = lista_inlantuita.top();
		lista_inlantuita.pop();
		
		for (auto& p : G[v])
            {
                int y = p.node;
                int w = p.dist;
                if (d[y] > d[v] + w)
                    d[y] = d[v] + w;
            }
	}
	
}
