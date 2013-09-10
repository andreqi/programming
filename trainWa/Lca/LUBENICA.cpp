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
const int MAXN = 100010, TOP = 22;
struct node {
    int anc, max_e, min_e;
    void merge(node a, node b) {
        node ans;
        anc = b.anc;
        max_e = max(a.max_e, b.max_e);
        min_e = min(a.min_e, b.min_e);
    }
} table[MAXN][TOP];

int tin[MAXN], tout[MAXN], lvl[MAXN], timer;
vector <int> adj[MAXN];
vector <int> we[MAXN];

void dfs (int u, int pai) {
    tin[u] = timer++;
    repn (i, 1, TOP) {
        if (table[u][i-1].anc == -1)
            table[u][i].anc = -1;
        else {
            table[u][i].merge(
                    table[u][i-1], 
                    table[table[u][i-1].anc][i-1]);
        }
    }
    rep (i, adj[u].size()) {
        int v = adj[u][i];
        if (v == pai) continue;
        lvl[v] = lvl[u] + 1;   
        table[v][0].anc = u;
        table[v][0].max_e = we[u][i];
        table[v][0].min_e = we[u][i];
        dfs (v, u);
    }
    tout[u] = timer++;
}

bool ancestor (int u, int v) {
    if (u == -1) return true;
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (ancestor(u, v)) return u;
    if (ancestor(v, u)) return v;
    int i = TOP;
    while (i--) {
        if (ancestor(table[u][i].anc,v)){}
        else u = table[u][i].anc;
    }
    return table[u][0].anc;
}
void relax(pii &a, pii b){
    if (a.fst == -1) a = b;
    if (b.fst == -1) return;
    a.fst = min(a.fst, b.fst);
    a.snd = max(a.snd, b.snd);
}

pii process(int pai, int child){
    if (pai == child) return pii(-1,-1);
    int up = lvl[child] - lvl[pai];
    pii ans = pii(-1,-1);
    int i = 0;
    while (up) {
        if (up & 1) {
            node & e = table[child][i];
            relax(ans, pii(e.min_e, e.max_e));
            child = table[child][i].anc;
        }
        up >>= 1;
        i++;
    }
    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    rep (i, n-1) {
        int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        we[u].push_back(e);
        we[v].push_back(e);
    }
    node & e = table[0][0];
    e.anc = -1;
    lvl[0] = 0;
    timer = 0;
    dfs(0, 0);
   /* rep (i, n) {
        rep (j, 4) cout << table[i][j].anc << " "; cout << endl;
    } */
    int q;
    scanf("%d", &q);
    rep (i, q) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        int pai = lca(u, v);
       // cout << pai << endl;
        pii ans = pii(-1,-1);
        relax(ans, process(pai, u));
        relax(ans, process(pai, v));
        printf("%d %d\n", ans.fst, ans.snd);
    }
	return 0;
}

