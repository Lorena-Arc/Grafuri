
#include <fstream>
#include <vector>
#include <tuple>
#include <bitset>
#include <stack>
#include <string>
using namespace std;


using VI = vector<int>;
using VT = vector<tuple<int, int>>;
using IT = VT::iterator;
using VIT = vector<IT>;
using VVT = vector<VT>;

vector<bool> v;

vector<vector<tuple<int, int>>> G;   // G[x] - vector de muchii
vector<int> ce;   // ciclul eulerian
int n, m;

void CitesteGraf(string input);
void AfiseazaCiclu(string output);
bool EsteEulerian();
void DeterminaCiclu();

int main(int argc, char* argv[])
{
	string input_file = argv[1];
	string output_file = argv[2];
	
	CitesteGraf(input_file);

	if (!EsteEulerian())
	{
		ofstream fout(output_file);
		fout << "-1";
		fout.close();
	}
	else
	{
		
		DeterminaCiclu();
		AfiseazaCiclu(output_file);
	}
}

void CitesteGraf(string input)
{
	ifstream fin(input);
	fin >> n >> m;
	G = vector<vector<tuple<int, int>>>(n);
	v = vector<bool>(m, false);
	for (int i = 0, a, b; i < m; ++i)
	{
		fin >> a >> b;
		G[a].emplace_back(b, i);
		G[b].emplace_back(a, i);
	}
	fin.close();
}


void DeterminaCiclu()
{
	vector<vector<tuple<int, int>>::iterator> p(n);
	//VIT p = VIT(n);
	for (int i = 0; i < n; ++i)
		p[i] = G[i].begin();

	int x, y, e;
	stack<int> stk;
	stk.push(0);

	while (!stk.empty())
	{
		x = stk.top();
		if (p[x] == G[x].end())
		{
			ce.emplace_back(x);
			stk.pop();
		}
		else
			while (p[x] != G[x].end())
			{
				tie(y, e) = *p[x]++;
				if (v[e]) continue;
				v[e] = true;
				stk.push(y);
				break;
			}
	}
}

void AfiseazaCiclu(string output)
{
	ofstream fout(output);
	for (size_t i = 0; i < ce.size() - 1; ++i)
		fout << ce[i] << ' ';
	fout.close();
}

bool EsteEulerian()
{
	for (int x = 0; x < n; ++x)
		if (G[x].size() % 2 == 1)
			return false;
	return true;
}
