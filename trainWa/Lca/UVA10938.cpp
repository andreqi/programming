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

const int MAXN = 5010, TOP = 14;
vector <int> adj[MAXN];

struct LCA {
    int timer;
    int lvl[MAXN], anc[MAXN][TOP];
    int tin[MAXN], tout[MAXN];
    void build() {
        lvl[0] = 0;
        anc[0][0] = -1;
        timer = 0;
        dfs(0, 0);
    }
    void dfs (int u, int pai) {
        tin[u] = timer++;
        repn (i, 1, TOP) {
            if (anc[u][i-1] < 0) anc[u][i] = -1;
            else anc[u][i] = anc[anc[u][i-1]][i-1];
        }
        rep (i, adj[u].size()) {
            int v = adj[u][i];
            if (v == pai) continue;
            lvl[v] = lvl[u] + 1;
            anc[v][0] = u;
            dfs(v, u);
        }
        tout[u] = timer++;
    }
    bool ancestor (int u, int v) {
        if (u == -1) return true;
        return tin[u] <= tin[v] and tout[v] <= tout[u];
    }
    int lca (int u, int v) {
        if (ancestor(u, v)) return u;
        if (ancestor(v, u)) return v;
        int i = TOP;
        while (i--) {
            if (ancestor(anc[u][i], v)) {}
            else u = anc[u][i];
        }
        return anc[u][0];
    }
    int kth (int u, int v, int d) {
        if (d == 0) return u;
        int pai = lca(u, v);
        int lu = lvl[u] - lvl[pai];
        int lv = lvl[v] - lvl[pai];
        if (lu >= d) return go_up(u, d);
        else         return go_up(v, lv + lu - d);
    }
    int go_up (int u, int up){
        int i = 0;
        while (up) {
            if ( up & 1 ) u = anc[u][i];
            i++; up >>= 1;
        }
        return u;
    } 
} solver;

int main(){
    int n;
    while (scanf("%d", &n) and n) {
        rep (i, n) adj[i].clear();
        rep (i, n-1){
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int q;
        scanf("%d", &q);
        solver.build();
        while (q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            int lca = solver.lca(u, v);
            int len = solver.lvl[u] + solver.lvl[v] - 2 * solver.lvl[lca];
            if (len % 2) {
                int a = solver.kth(u, v, len/2) + 1;
                int b = solver.kth(u, v, (len+1)/2) + 1;
                printf("The fleas jump forever between %d and %d.\n", min(a, b), max(a, b));
            } else {
                printf("The fleas meet at %d.\n", solver.kth(u, v, len/2) + 1);
            }
        }
    }
	return 0;
}

