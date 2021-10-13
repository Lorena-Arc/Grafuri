#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<int>> d;
int n;

const int inf = 0x3f3f3f3f;

void citeste(string input);
void warshall();
void afiseaza(string output);

int main(int argc, char** argv)
{
    citeste(argv[1]);
    warshall();
    afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
	
    fin >> n;
    d = vector<vector<int>>(n);
    
    for (int i = 0; i < n; ++i)
    {
        d[i] = vector<int>(n, inf);
        d[i][i] = 0;
    }

    int x, y, w;
    while (fin >> x >> y >> w)
    {
        d[x][y] = w;
        d[y][x] = w;
    }
    
	fin.close();
}

void warshall()
{
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void afiseaza(string output)
{
	ofstream fout(output);
    for (int i = 0; i < n; ++i, fout << '\n')
        for (int j = 0; j < n; ++j)
            fout << d[i][j] << ' ';
            
    fout.close();
}
