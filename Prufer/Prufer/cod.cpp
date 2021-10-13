#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Nod {
	int tata, nr_fii;
};

struct frunza {
	int nod;
	bool operator <(const frunza& ot) const{
		return nod > ot.nod;
	}
};


int n, radacina = -1;
vector <Nod> g;
priority_queue<frunza> frunze;
vector<int> prufer;

void citire_graf(string input);
void afisare_prufer(string output);
void codare_prufer();

int main(int argc, char* argv[]) {
	ofstream fout(argv[2]);

	citire_graf(argv[1]);

	codare_prufer();
	
	afisare_prufer(argv[2]);
	
}


void citire_graf(string input){
	ifstream fin(input);
	
	fin >> n;

	g = vector<Nod>(n);
	
	for (int i = 0; i < n; ++i) 
	{
		int tata;
		fin >> tata;
		g[i].tata = tata;
		if (tata != -1)
			g[tata].nr_fii++;
		else
			radacina =  i;
	}
	
	fin.close();
}

void codare_prufer(){
	
	for (int i = 0; i < n; ++i)
		if (g[i].nr_fii == 0)
			frunze.emplace(frunza{ i });
			 
	
	while (!frunze.empty() && frunze.top().nod != radacina)
	{
		frunza fr = frunze.top();
		frunze.pop();
		
		prufer.push_back(g[fr.nod].tata);
		
		g[g[fr.nod].tata].nr_fii--;
		
		if (g[g[fr.nod].tata].nr_fii == 0)
			frunze.emplace(frunza{ g[fr.nod].tata });
		
	}
}

void afisare_prufer(string output){
	
	ofstream fout(output);
	
	fout << prufer.size() << "\n";
	
	for (auto& el : prufer)
		fout << el << " ";
		
	fout.close();
}
