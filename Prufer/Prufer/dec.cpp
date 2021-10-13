#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int nr;
queue<int> K;
vector<int> exista;
vector<int> tati;

void citire_graf(string input);
void afisare_graf(string output);
void decodare();

int main(int argc, char* argv[]) {
	citire_graf(argv[1]);
	decodare();
	
	afisare_graf(argv[2]);
}

void citire_graf(string input){
	
	ifstream fin(input);
	fin >> nr;
	nr++;
	
	
	int x;
	exista = vector<int>(nr, 0);

	while (fin >> x)
	{
		K.push(x);
		exista[x]++;
	}
	
	fin.close();
}

void afisare_graf(string output){
	ofstream fout(output);
	
	fout << nr << '\n';
	
	for (const auto& el : tati)
		fout << el << " ";
		
	fout.close();
}

void decodare(){
	
	tati = vector<int> (nr , -1);
	
	for (int i = 0; i < nr - 1; ++i) {
		int x = K.front();
		int y = find(exista.begin(), exista.end(), 0) - exista.begin() ; // caut frunza
		
		exista[x]--;
		exista[y]++;
		
		tati[y] = x;
		K.pop();
		K.push(y);
	}
	
	}
