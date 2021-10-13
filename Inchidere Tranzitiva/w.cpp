/* Alg. lui Warshall
    Complexitate: O(n^3)

    Transforma matricea de adiacenta
    in matricea lanturilor (drumurilor)
    prin adaugarea de valori true
*/
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> a;
int n;

void CitesteGraf(string input);
void Warshall();
void ScrieMatrice(string output);

int main(int argc, char** argv)
{
    CitesteGraf(argv[1]);
    Warshall();
    ScrieMatrice(argv[2]);

    return 0;
}

void Warshall()
{
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j && !a[i][j])
                    a[i][j] = a[i][k] && a[k][j];
}

void ScrieMatrice(string output)
{
	ofstream fout(output);
	
    for (int i = 0; i < n; ++i, fout << '\n')
        for (int j = 0; j < n; ++j)
            fout << a[i][j] << ' ';
    fout << "\n\n";
    
    fout.close();
}

void CitesteGraf(string input)
{
	ifstream fin(input);
	
	int x, y;
    fin >> n;
	
	a = vector<vector<int>>(n);
	
	for(int i =0; i < n; ++i)
		a[i] = vector<int>(n, 0);
    
    while (fin >> x >> y){
        a[x][y] = true;
	}
	
	fin.close();
}
