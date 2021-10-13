#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void citire(string input);
void afisare(string output);
void floyd_warshall();

vector<vector<int>> ma;
int n;

int main(int argc, char** argv){
	citire(argv[1]);
	floyd_warshall();
	afisare(argv[2]);
}

void citire(string input){
	ifstream fin(input);
	fin >> n;
	
	ma = vector<vector<int>>(n);
	
	for(int i = 0; i < n; ++i)
		ma[i] = vector<int>(n, 0);
		
	int x, y;
	
	while(fin >> x >> y){
		ma[x][y] = 1;
	}

	fin.close();
}

void afisare(string output){
	ofstream fout(output);
	
	for(int i = 0; i < n; ++i, fout << "\n")
			for(int j = 0; j < n; ++j)
				fout << ma[i][j] << " ";

	fout.close();
}

void floyd_warshall(){
	
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				ma[i][j] = ma[i][j] + ma[i][k]*ma[k][j];
}
