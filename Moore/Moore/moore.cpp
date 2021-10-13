/// Afiseaza cele mai scurte drumuri de la nodul s la toate celelalte
/// Merge pe grafuri orientate/neorientate
/// Nu merge pt grafuri cu costuri!!!
/// Foloseste lista de adiacenta

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

ifstream fin("fisier.in");

using V = vector<int>;
using VV = vector<V>;
const int inf = 0x3f3f3f3f;

void citeste(string input);
void Moore(int s);
void afisare(int s, string output);

int n;
vector<vector<int>> G;
vector<int> L;
vector<int> P;

int main(int argc, char** argv)
{
    citeste(argv[1]);
    Moore(0);
    afisare(0, argv[2]);


    fin.close();

}

void citeste(string input)
{
	ifstream fin(input);
	
    fin >> n;
    G = vector<vector<int>>(n);

    int x, y;

    while (fin >> x >> y)
    {
        G[x].push_back(y);
       // G[y].push_back(x);
    }
    
    fin.close();
}

void Moore(int s)
{
	L = vector<int>(n, inf); //lungimea drumurilor
    P = vector<int>(n, -1); //parintii
    
    L[s] = 0;
    
    queue<int> Q;
    Q.push(s);

    int x;

    while (!Q.empty())
    {
        x = Q.front();
        Q.pop();
        for (const auto& y : G[x])
        {
            if (L[y] == inf)
            {
                P[y] = x;
                L[y] = L[x] + 1;
                Q.push(y);
            }
        }
    }
}

void afisare(int s, string output)
{
	ofstream fout(output);
	
    for (int i = 0; i < n; ++i)
    {
        cout << i << ": ";
        int j = L[i];
        if (j == inf)
            cout << "Nu exista drum" << '\n';
        else
        {
            cout << i << ' ';
            int k = i;
            while (j)
            {
                cout << P[k] << ' ';
                k = P[k];
                j--;
            }
            cout << '\n';
        }
    }
    
    fout.close();
}
