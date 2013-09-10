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

static const int MAXN = 10100, TOP = 20;
vector <int> adj[MAXN];
vector <int> we[MAXN];
struct LCA {
    int tin[MAXN], tout[MAXN], lvl[MAXN];
    int len[MAXN][TOP]; // sum we[i]
    int anc[MAXN][TOP];
    int timer;
    
    void build(){
        anc[0][0] = -1;
        lvl[0] = 0;
        timer = 0;
        dfs(0, 0);
    }

    void dfs (int u, int pai) {
        tin[u] = timer++;
        repn (i, 1, TOP) {
            if (anc[u][i-1] < 0) {
                anc[u][i] = -1;
            } else {
                anc[u][i] = anc[anc[u][i-1]][i-1];
                len[u][i] = len[anc[u][i-1]][i-1] + len[u][i-1];
            }
        }
        rep (i, adj[u].size()) {
            int v = adj[u][i];
            if (v == pai) continue;
            lvl[v] = lvl[u] + 1;
            anc[v][0] = u; 
            len[v][0] = we[u][i];
            dfs(v, u);
        }
        tout[u] = timer++;
    }

    int kth (int u, int v, int d) {
        if (d == 1) return u;
        d--;
        int pai = lca(u, v);
        while (pai < 0);
        int len_u = lvl[u] - lvl[pai];
        int len_v = lvl[v] - lvl[pai];
        if (len_u >= d) {
            return go_up(u, d);
        } else {
            d -= len_u;
            d = len_v - d;
            return go_up(v, d);
        }
    }

    int dist (int u, int v) {
        int pai = lca(u, v);
        return process(pai, u) + process(pai, v);
    }
    
    int go_up(int node, int up) {
        while (up < 0); 
        int i = 0;
        while (up) {
            if (up & 1) 
                node = anc[node][i];
            up >>= 1; i ++;
        }
        return node;
    }

    int process(int pai, int child) {
        if (pai == child) return 0;
        int up = lvl[child] - lvl[pai];
        int i = 0, ans = 0;
        while (up) {
            if (up & 1) {
                ans += len[child][i];
                child = anc[child][i];
            }
            i++; up >>= 1;
        }
        return ans;
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
    int ancestor (int u, int v) {
        if (u==-1) return true;
        return tin[u] <= tin[v] and tout[v] <= tout[u];
    }
} solver;

int main(){
    int test;
    char buff[100];
    scanf("%d", &test);
    while (test--) {
        int n;
        scanf("%d", &n);
        rep (i, n) adj[i].clear();
        rep (i, n) we[i].clear();
        rep (i, n - 1) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            we[u].push_back(w);
            we[v].push_back(w);
        }
        solver.build();
        while (scanf("%s", buff) and buff[1] != 'O') {
            char c = buff[1];
            int u, v, d, ans;
            scanf("%d%d", &u, &v);
            u--, v--;
            if ( c == 'T' ) {
                scanf("%d", &d);
                ans = solver.kth(u, v, d) + 1;
            }
            else ans = solver.dist(u, v);
            printf("%d\n", ans);
        }    
        printf("\n");
    }
	return 0;
}

