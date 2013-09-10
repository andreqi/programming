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

int n, m; 
int usd[200][200];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
pii b, e;

bool dfs(pii cur){
    if ( cur == e ) return true;
    usd[cur.fst][cur.snd] = 1;
    rep(i, 4) {
        int nx = cur.fst + dx[i];
        int ny = cur.snd + dy[i];
        if ( nx < 0 or ny < 0 or nx >= n or ny >= m ) continue;
        if ( usd[nx][ny] ) continue;
        if ( dfs( pii(nx, ny) ) ) return true;
    }
    return false;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%d%d", &n, &m);
        memset(usd, 0, sizeof usd);
        rep(i, n) rep(j, m) scanf("%d", usd[i] + j);
        scanf("%d%d", &b.fst, &b.snd);
        scanf("%d%d", &e.fst, &e.snd);
        printf("%s\n",dfs(b)?"YES":"NO");
    }
	return 0;
}

