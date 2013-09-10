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
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

vector<int> adj[200];
int dist[200];
int usd[200];

int main(){
    int test;
    int v, e , s; 
    scanf("%d", &test);
    while (test--) {
        queue<int> q;
        memset(dist, -1 , sizeof dist);
        memset(usd, 0, sizeof dist);
        scanf("%d%d%d", &v, &e, &s);
        rep(i, v) adj[i].clear();
        rep(i, e) {
            int src, dst;
            scanf("%d%d", &src, &dst);
            adj[src].push_back(dst);
            adj[dst].push_back(src);
        }
        rep(i, s){
            int secure;
            scanf("%d", &secure);
            dist[secure] = 0;
            usd[secure] = 1;
            q.push(secure);
        }
        while ( not q.empty() ) {
            int cur = q.front(); q.pop();
            rep(i, adj[cur].size()) {
                int nxt = adj[cur][i]; 
                if ( usd[nxt] ) continue;
                usd[nxt] = 1;
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        } 
        rep (i, v) printf("%d%c", dist[i], i < v-1?' ':'\n');

    }
	return 0;
}

