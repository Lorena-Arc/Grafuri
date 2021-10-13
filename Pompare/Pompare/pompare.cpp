#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
#include <time.h>
using namespace std;

struct varf{
    int nr, h, e;

    bool operator <(const varf& ot) const{
        return this->h > ot.h;
    }
};

struct CmpNod
{
    bool operator()(const varf* lhs, const varf* rhs) const
    {
        return lhs->h < rhs->h;
    }
};

vector<varf> varfuri;
vector<vector<int>> ma;
priority_queue<varf*, vector<varf*>, CmpNod> q;
int V, E;
int pomp, inalt;


void initializare(int s, int t);
void pompare_preflux(int s, int t);
void pompare(int u, int v, int s, int t);
void inaltare(int u);
void citire(string input);

int main(int argc, char** argv)
{
	int t = time(NULL);
    ofstream fout(argv[2]);
	citire(argv[1]);

    pompare_preflux(0, V-1);
    fout << varfuri[V-1].e;
    cout << time(NULL) - t << '\n';
    fout.close();
}


void initializare(int s, int t){
    for(auto& v: varfuri)
    {
        v.h = 0;
        v.e = 0;
    }

    varfuri[s].h = V;

    for(int i = 0; i < V; ++i){
        varfuri[i].nr = i;
        if(ma[s][i] > 0){
            int cost = ma[s][i];
            varfuri[i].e = cost;
            ma[s][i] -= cost;
            ma[i][s] += cost;
            if(i != t && i != s)
                q.push(&varfuri[i]);
        }
    }
}


void pompare_preflux(int s, int t){
    initializare(s, t);
    int i = 0;
    while(!q.empty()){
        varf* u = q.top();
        bool pomp = false;
        for(int i = 0; i < V; ++i)
            if(ma[u->nr][i] > 0)
            {
                if(u->h == varfuri[i].h + 1)
                {
                    pomp = true;
                    pompare(u->nr, i, s, t);
                    break;
                }

            }
        if(!pomp)
            inaltare(u->nr);
        i++;
     }
     
}

void pompare(int u, int v, int s, int t){
    int pomp = min(varfuri[u].e, ma[u][v]);
    //cout << varfuri[u].e << ' ';
    ma[u][v] -= pomp;
    ma[v][u] += pomp;

    varfuri[u].e -= pomp;
    varfuri[v].e += pomp;


    if(varfuri[u].e == 0)
        q.pop();

    if(v != s && v != t && varfuri[v].e != 0)
    {
        q.push(&varfuri[v]);
    }

}

void inaltare(int u){
    int h_min = INT_MAX;
    for(int i = 0; i < V; ++i)
        if(ma[u][i] > 0)
            h_min = min(h_min, varfuri[i].h);
    varfuri[u].h = 1 + h_min;
}


void citire(string input){
	ifstream fin(input);
	
	fin >> V >> E;

    int x, y, w;

    ma = vector<vector<int>>(V);
    for(int i = 0; i < V; ++i)
        ma[i] = vector<int>(V, 0);

    varfuri = vector<varf>(V);

    while(fin >> x >> y >> w)
        ma[x][y] = w;	
        
    fin.close();
}
