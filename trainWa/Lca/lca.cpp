#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define clr(x, y) memset(x, (y), sizeof x)
#define two(x) (1<<(x))
#define twol(x) (1LL<<(x))
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100000, TOP = 25;
int tin[MAXN], tout[MAXN], lvl[MAXN];
int timer = 0;
int anc[MAXN][TOP];
vector <int> adj[MAXN];

void dfs (int u, int pai, int u_lvl) {
    tin[u] = timer++;
    lvl[u] = u_lvl++;
    anc[u][0] = pai; 
    repn (i, 1, TOP)  anc[u][i] = anc[anc[u][i-1]][i-1];
    rep (i, adj[u].size()) {
        int v = adj[u][i];
        if (pai==v) continue;
        dfs(v, u, u_lvl + 1);
    }
    tout[u] = timer++;
}

bool ancestor (int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tin[u];
}

int lca (int u, int v) {
    if (ancestor(u, v)) return u;
    if (ancestor(v, u)) return v;
    int i = TOP;
    while (i--) {
        if (!ancestor(anc[u][i], v))
            u = anc[u][i];
    }
    return anc[u][0];
}

int main(){
	return 0;
}

