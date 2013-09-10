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
#define MAXN 10011

vector< int > adj[ MAXN ];
int timer;
int seen[ MAXN ], low[ MAXN ];
int pai[ MAXN ];
int ufind( int u ){ return u == pai[ u ] ? u : pai[ u ] = ufind( pai[ u ] ); }
void dis_union( int u , int v ){ pai[ ufind( u ) ] = ufind( v ); }

void dfs( int u , int from ){
	seen[ u ] = low[ u ] = timer++;
	int & lower = low[ u ];
	rep( i , adj[ u ].size() ) {
		int v = adj[ u ][ i ];
		if( v == from ) continue;
		if( seen[ v ] != -1 ){
			lower = min( lower , seen[ v ] );
		} else {
			dfs( v , u );
			lower = min( lower , low[ v ] );
			if( low[ v ] > seen[ u ] ){
				dis_union( u , v );
			}
		}
	}
} 


int main(){
	int v , e , q, a , b;
	while( scanf("%d%d%d" , &v , & e , &q ) == 3 and v + e + q ) {
		rep( i , v ) adj[ i ].clear();
		rep( i , v ) pai[ i ] = i;
		rep( i , e ){
			scanf("%d%d" , &a , & b );
			a-- , b--;
			adj[ a ].push_back( b );
			adj[ b ].push_back( a );
		}
		rep( i , v ) seen[ i ] = -1;
		timer = 0;
		rep( i , v ) if( seen[ i ] == -1 ) {
			dfs( i , -1 );
		}
		while( q-- ){
			scanf("%d%d" , &a , &b );
			a-- , b--;
			if( ufind( a ) == ufind( b ) )	puts("Y");
			else							puts("N");
		}
		printf("-\n");
	}
	return 0;
}

