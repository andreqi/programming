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
#define for_each(it, c) for(__typeof((c).begin()) it=(c).begin() ;it!=(c).end();++it)
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
const int MAXN = 1000000;
int vis[MAXN], q[MAXN], level[MAXN]; 
int pai[MAXN], size[MAXN], label[MAXN];
int first[MAXN];
vector <int> adj[MAXN]; // representacion del grafo
vector <int> path[MAXN]; // caminos heavy arrechos
vector <int> head; // "cabezas" de los caminos heavy arrechos
void bfs (int root) {
    int h = 0, t = 0;
    q[t++] = root;
    level[root] = 0;
    vis[root] = true;
    pai[root] = -1;
    // BFS y guardar orden del bfs en q, calcular level y pai
    while (h < t) {
        int u = q[h++];
        for_each(e, adj[u]){
            int v = *e;
            if (vis[v]) continue;
            pai[v] = u;
            q[t++] = v;
            level[v] = level[u] + 1;
            vis[v] = true;
        }
    }
    // recorrer el bfs al revez y calcular la cantidad de nodos en el
    // sub arbol
    for (int i = h - 1; i >=0; i--) {
        int u = q[i];
        size[u] = 1;
        for_each(e, adj[u]) if (pai[*e] == u) {
            size[u] += size[*e];
        }
    }
    // marcar los caminos como heavy-arrecho o light
    clr(label, -1);
    rep(i, MAXN) path[i].clear();
    int name = -1;
    //rep (i, h) cout << q[i] << " "; cout << endl;
    rep (i, h) {
        int u = q[i];
        if (label[u] >= 0) continue;
        head.push_back(u);
        name++;
        int next;
        do {
            label[u] = name;
            first[u] = q[i];
            path[name].push_back(u);
            next = -1; 
            for_each(e, adj[u]) if (pai[*e] == u) {
                if (next==-1 or size[next] < size[*e])
                    next = *e;
            }
            u = next;
        } while (next != -1);
        // process segment_tree o bit
    }
}

int lca (int u, int v) {
    while (label[u] != label[v]) {
        if (level[first[u]] > level[first[v]])
            u = pai[first[u]];
        else 
            v = pai[first[v]];
    }
    if (level[u] < level[v]) return u;
    return v;
}
int main(){
    int u, v;
    int n;
    cin >> n;
    while (n--){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> x(10,10);
    //for_each(e, x) cout << " " << *e << endl;
    bfs(0);
    rep (i, head.size()){
        int e = head[i];
        cout << e << endl;
        rep (j, path[i].size()) {
            cout << " -> " << path[i][j];
        }
        cout << endl;
    }
    cout << "asda>" << endl;
    while (cin >> u >> v) {
        cout << lca(u, v) << endl;
    }
	return 0;
}

