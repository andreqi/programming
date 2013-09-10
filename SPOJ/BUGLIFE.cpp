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
#define MAXN 5000
vector< int > adj[ MAXN ];
int seen[ MAXN ];

int dfs( int v , int color ){
	seen[ v ] = color;
	rep( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( seen[ u ] != -1 ){
			if( seen[ u ] == color ) return false;
			continue;
		}
		if( not dfs( u , 1 - color ) ) return false;
	}
	return true;
}

bool solve(){
	int n , m;
	int u , v;
	scanf("%d%d" , &n, &m );
	rep( i , n ) adj[ i ].clear();
	rep( i , m ){
		scanf("%d%d", &u , & v );
		u-- , v--;
		adj[ u ].push_back( v );
		adj[ v ].push_back( u );
	}
	rep( i , n ) seen[ i ] = -1;
	rep( i , n ) if( seen[ i ] == -1 ){
		if( not dfs( i , 0 ) ) return true;
	}
	return false;
}

int main(){
	int test;
	scanf("%d" , & test );
	rep( tcase , test ){
		printf("Scenario #%d:\n" , tcase + 1 );
		printf("%suspicious bugs found!\n" , solve() ? "S": "No s" );
	}
	return 0;
}

