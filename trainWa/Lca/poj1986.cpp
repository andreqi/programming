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
int dis[MAXN][TOP];
vector <int> adj[MAXN];
vector <int> we[MAXN];

void dfs (int u, int pai, int u_lvl, int wei) {
    tin[u] = timer++;
    lvl[u] = u_lvl;
    anc[u][0] = pai; 
    dis[u][0] = wei; 
    repn (i, 1, TOP){
        if (anc[u][i-1] == -1) anc[u][i] = -1;
        else {
            anc[u][i] = anc[anc[u][i-1]][i-1];
            dis[u][i] = dis[anc[u][i-1]][i-1] + dis[u][i-1];
        }
    }
    rep (i, adj[u].size()) {
        int v = adj[u][i];
        if (pai == v) continue;
        dfs(v, u, u_lvl + 1, we[u][i]);
    }
    tout[u] = timer++;
}

bool ancestor (int u, int v) {
    if (u==-1) return true;
    return tin[u] <= tin[v] and tout[v] <= tout[u];
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

int process(int pai, int child) {
    if (pai == child) return 0;
    int go_up = lvl[child] - lvl[pai];
    int i = 0, ans = 0;
    while (go_up) {
        if (go_up % 2){
            ans += dis[child][i];
            child = anc[child][i];
        }
        go_up >>= 1;
        i++;
    }
    return ans;
}

int main(){
    char s[10];
    int n, e;
    scanf("%d%d", &n, &e);
    rep (i, e) { 
        int u, v, d;
        scanf("%d%d%d%s", &u, &v, &d, s);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        we[u].push_back(d);
        we[v].push_back(d);
    }
    dfs(0, -1, 0, 0);
    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        int pai = lca(u, v);
        printf("%d\n", process(pai, u) + process(pai, v));
    }
	return 0;
}

