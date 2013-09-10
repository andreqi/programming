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
#define neg(x) ( (x) ^ 1 )
#define MAXN 1000
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

vector< int > adj[ MAXN ];
vector< int > dag[ MAXN ];
vector< int > e_scc[ MAXN ];

void add( int u , int v ){
	adj[ neg( u ) ].push_back( v );
	adj[ neg( v ) ].push_back( u );
}

int to_id( int i , char  str ){
	return i * 2 + ( str == 'w' );
}

void separado( int u , int v ){
	add( 2 * u , 2 * v );
	add( neg( 2 * u ) , neg( 2 * v ) );
}

void juntos( int u , int v ){
	add( 2 * u , neg( 2 * v ) );
	add( neg( 2 * u ) , 2 * v );
}

void clear(){
	rep( i , MAXN ) adj[ i ].clear();
	rep( i , MAXN ) e_scc[ i ].clear();
}

int in_stack[ MAXN ] , seen[ MAXN ] , low[ MAXN ] ;
int timer = 0;
int n_scc , scc[ MAXN ] ;
stack< int > stk;

int dfs( int x ){
	seen[ x ] = low[ x ] = timer++;
	in_stack[ x ] = true; stk.push( x );
	int & lowp = low[ x ];
	rep( i , adj[ x ].size() ){
		int v = adj[ x ][ i ];
		if( seen[ v ] == -1 ) 	 lowp = min( lowp , dfs( v ) );
		else if( in_stack[ v ] ) lowp = min( lowp , seen[ v ] ) ;
	}
	if( lowp == seen[ x ] ){
		int y = x;
		do {
			in_stack[ y ] = false;
			scc[ y ] = n_scc;
			e_scc[ n_scc ].push_back( y );
			y = stk.top(); stk.pop();
		} while( y != x ); 
		n_scc++;
	}
	return lowp;
}

bool solvable( int n ){
	rep( i , MAXN ) seen[ i ] = -1;
	timer = n_scc = 0;
	rep( i , 4 * n ) if( seen[ i ] == -1 ) { 
		dfs( i );
	}
	string tk = "hw";
	rep( i , n ){
		rep( j , 2 ){
			int x = to_id( i , tk[ j ] );
			if( scc[ 2 * x ] == scc[ neg( 2 * x ) ] )	
			return false;
		}
	}
}
int val[ MAXN ];
int order[ MAXN ];
void topsort( int v ){
	seen[ v ] = true;
	rep( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( seen[ u ] ) continue;
		topsort( u );
	}
	order[ timer-- ] = v;
}

int main(){
	int n , m;
	int a , b ;
	char b1[ 3 ] , b2[ 3 ];
	int x = to_id( 0 , 'w' );
	while( scanf("%d%d", &n , &m ) == 2 and n + m ){
		clear();
		separado( x , to_id( 0 , 'h' ) );
		rep( i , m ){ 
			scanf("%d%s %d%s", &a , b1 , &b , b2 ); 
			int u = to_id( a , b1[ 0 ] ) , v = to_id( b , b2[ 0 ] );
			separado( u , v );
		}
		if( solvable( n ) ){
			rep( i , n_scc ) dag[ i ].clear();
			rep( u , 4 * n ){
				rep( i , adj[ u ].size() ){
					int v = adj[ u ][ i ] ;
					if( scc[ u ] == scc[ v ] ) continue;
					dag[ scc[ u ] ].push_back( scc[ v ] );
				}
			}
			rep( i , n_scc ) seen[ i ] = 0;
			timer = n_scc - 1 ;
			rep( i , n_scc ) if( seen[ i ] == 0 ) {
				topsort( i );
			}
			rep( i , n_scc ) low[ i ] = -1;
			rep( i , MAXN ) val[ i ] = true;
			rep( i , n_scc ) if( low[ i ] == -1 ){
				low[ i ] = false;
				rep( j , e_scc[ i ].size() ){
					low[ scc[ neg( e_scc[ i ][ j ] ) ] ] = true;
					val[ e_scc[ i ][ j ] / 2 ] = e_scc[ i ][ j ] & 1 ;
				}
			}
		}
		else printf("bad luck\n");
	}
	return 0;
}

