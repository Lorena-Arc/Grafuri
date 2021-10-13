#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct varf{
    int nod, grad;
    
    bool operator < (const varf& ot) const{
        if(grad ==ot.grad)
            return nod < ot.nod;
        return this->grad <= ot.grad;
    }
};

vector<vector<int>> G;
vector<bool> culori;
vector<int> colorare;
priority_queue<varf> q;
int V, E;


void citire_graf(string input);
void afisare_graf(string output);
void colorez_cu_numere();

int main(int argc, char** argv){
	
	citire_graf(argv[1]);
	
	if(E == (V*(V - 1))/2)
	{
		ofstream fout(argv[2]);
		fout << V << "\n";
		for (int i = 0; i < V; ++i)
			fout << i << " ";
		fout.close();
		return 0;
	}
	
	colorez_cu_numere();
	
	afisare_graf(argv[2]);
	
	return 0;
}


void citire_graf(string input){
	ifstream fin(input);
	
	fin >> V >> E;
	
	G = vector<vector<int>>(V);
	colorare = vector<int> (V, -1);
	culori = vector<bool>(V, false);
	
	int x, y;
	while(fin >> x >> y){
		G[x].push_back(y);
		G[y].push_back(x);
	}
		
	
	fin.close();
}

void afisare_graf(string output){
	ofstream fout(output);
	auto it = max_element(colorare.begin(), colorare.end());
	fout << *it + 1 << "\n";
	
	for(auto& col: colorare)
		fout << col << " ";
	fout << "\n";
	 
	fout.close();
}

void colorez_cu_numere(){
	
	for(int i = 0; i < V; ++i)
		q.push({i, (int)G[i].size()});
		
	
	int v = q.top().nod;
	q.pop();
	colorare[v] = 0;
	
	while(!q.empty()){
		
		
		
		v = q.top().nod;

		q.pop();
		
		
		for(const auto& nod: G[v])
		{
			if(colorare[nod] != -1)
				culori[colorare[nod]] = true;
		}
		
		for(int i = 0; i < V; ++i)
		{
			if(culori[i] == false){
				colorare[v] = i;
				break;
			}
		}
		
		for(int i = 0; i < V; ++i)
			culori[i] = false;
	}
	
}
