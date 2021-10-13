
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class DS {
	using VI = vector<int>;
public:
	DS(int n) :
		n{ n }, t{ VI(n) }
	{
		for (int i = 0; i < n; ++i)
			t[i] = i;
	}

	int Find(int x)
	{
		if (x == t[x])
			return x;
		return Find(t[x]);
	}

	void Union(int r1, int r2)
	{
		t[r2] = r1;
		
	}

private:
	int n; //numarul de noduri
	VI t;
};

struct Edge {
	Edge(int a, int b, int w) :
		a{ a }, b{ b }, w{ w }
	{}

	bool operator < (const Edge& e) const
	{
		return w > e.w;
	}

	int a, b, w;
};

int n, m;            // noduri, muchii
int cmin = 0;            // costul APM
priority_queue<Edge> edges;  // retine graful ca vect de muchii
vector<Edge> apm;

void Kruskal();

void citire_graf(string input);
void afisare_graf(string output);

int main(int argc, char** argv)
{
	//citire
	
	citire_graf(argv[1]);
	
	//kruskal
	Kruskal();

	//afisare
	afisare_graf(argv[2]);
}

void Kruskal()
{
	int c1, c2;  // componentele conexe (arborii) din care fac parte nodurile a si b	

	DS ds(n);

	while(!edges.empty())
	{
		// find - O(1)
		Edge edge = edges.top();
		edges.pop();
		
		c1 = ds.Find(edge.a);
		c2 = ds.Find(edge.b);
		if (c1 != c2)
		{
			cmin += edge.w;
			apm.emplace_back(edge);

			ds.Union(c1, c2);
			if (apm.size() == size_t(n - 1))
				break;
		}
	}
}


void citire_graf(string input){
	ifstream fin(input);
	
	fin >> n >> m;
	int a, b, w; //muchia/costul
	while (fin >> a >> b >> w)
		edges.push({a, b, w});

	fin.close();
}


void afisare_graf(string output){
	
	ofstream fout(output);
	
	fout << cmin << '\n';

	int nr_m = apm.size();

	fout << nr_m << '\n';

	sort(apm.begin(), apm.end(), [](const Edge& x, const Edge& y) {
		if (x.a == y.a)
			return x.b < y.b;
		return x.a < y.a;
	});
		
	for (const Edge& edge : apm)
		fout << edge.a << ' ' << edge.b << '\n';
		
	fout.close();
}
