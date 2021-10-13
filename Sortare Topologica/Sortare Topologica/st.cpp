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

vector<vector<int>> G;
vector<Nod> lista_n;
stack<int> lista_inlantuita;

int n;
int timp;

void citeste(string input);
void DFS();
void DFS_VISIT(int s);
void afisare(string output);
void sortare_topologica();

int main(int argc, char** argv){
	citeste(argv[1]);
	
	sortare_topologica();
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
        if (lista_n[v].culoare == "alb")
        {
            lista_n[v].parinte = s;
            DFS_VISIT(v);
        }
    lista_n[s].culoare = "negru";
    lista_inlantuita.push(s);
	timp++;
	lista_n[s].f = timp;
}

void citeste(string input)
{
	ifstream fin(input);
    fin >> n;
    
    G = vector<vector<int>>(n);

    int x, y;
    while (fin >> x >> y)
        G[x].push_back(y);
    
    fin.close();

}

void sortare_topologica(){
	DFS();
}


void afisare(string output){
	ofstream fout(output);
	while(!lista_inlantuita.empty()){
			fout << lista_inlantuita.top() << " ";
			lista_inlantuita.pop();
	}
	fout.close();
}
