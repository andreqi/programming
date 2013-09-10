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

#define MAXN 10001
#define MXLG 15
vector< int > adj[ MAXN ];
vector< int > wei[ MAXN ];
int bpadre[ MAXN ][ MXLG ];
int bmaxed[ MAXN ][ MXLG ];
int lvl[ MAXN ];
pii edge[ MAXN ];
int n;

void clear(){
	rep( i , MAXN ) adj[ i ].clear();
	rep( i , MAXN ) wei[ i ].clear();
	memset( bpadre , -1 , sizeof bpadre );
}

void dfs( int u , int p = -1 , int e = -1 , int l = 0 ){
	bpadre[ u ][ 0 ] = p;
	bmaxed[ u ][ 0 ] = e;
	lvl[ u ] = l;
	rep( i , adj[ u ].size() ){
		int v = adj[ u ][ i ];
		if( v == p ) continue;
		int w = wei[ u ][ i ];
		dfs( v , u , w , l + 1 );
	}
}

void sparse(){
	repn( pot , 1 , MXLG ){
		rep( node , n ){
			int pai = bpadre[ node ][ pot - 1 ];
			if( pai == -1 ) continue;
			bpadre[ node ][ pot ] = bpadre[ pai ][ pot - 1 ];
			bmaxed[ node ][ pot ] = max( bmaxed[ node ][ pot - 1 ] , 
										 bmaxed[ pai ][ pot - 1 ] );
		}
	}
}

void update( int & fstV , int & acumV , int val  ){
	if( fstV or acumV < val ){
		fstV = 0;
		acumV = val;
	}
}

int query( int u , int v ){
	if( lvl[ u ] > lvl[ v ] ) swap( u , v );
	//cout << u << " " << v << endl;
	int fstV= true , fstU = true ;
	int dif = lvl[ v ] - lvl[ u ];
	int acumV = 0 ; int acumU = 0;
	//cout << dif << endl;
	for( int pot = MXLG - 1 ; pot >= 0 ; pot-- ){
		if( ( 1 << pot ) & dif ){
			int w = bmaxed[ v ][ pot ];
			v = bpadre[ v ][ pot ];
			//cout << u << " "  << v << pot  << endl;
			if( fstV or acumV < w ){
				fstV = 0 , acumV = w;
			}
		}
	}
	if( u == v ) return acumV;
	for( int pot = MXLG - 1 ; pot >= -1 ; pot-- ){
		if( pot == -1 or bpadre[ v ][ pot ] != bpadre[ u ][ pot ] ){
			int npot = max( pot , 0 );
			update( fstV , acumV , bmaxed[ v ][ npot ] );
			update( fstU , acumU , bmaxed[ u ][ npot ] );
			v = bpadre[ v ][ npot ];
			u = bpadre[ u ][ npot ];
		}
	}
//	cout << u << " " << v << endl;
	while( u != v );
	return max( acumV , acumU );
}

void update( int id , int cost ){
	int u = edge[ id ].fst , v = edge[ id ].snd; 
	if( bpadre[ u ][ 0 ] != v ) swap( u , v ); 
	bmaxed[ u ][ 0 ] = cost;
	int pot = 1;
	while( true ){
		int pai = bpadre[ u ][ pot - 1 ];
		if( pai == -1 ) break;
		bmaxed[ u ][ pot ] = max( bmaxed[ u ][ pot - 1 ] , bmaxed[ pai ][ pot - 1 ] );
		pot++;
	}
}

int main(){
	int test;
	char order[ 100 ];
	scanf("%d" , & test );
	while( test-- ){
		clear();
		scanf( "%d" , &n );
		rep( i , n -1 ){
			int u , v , c;
			scanf( "%d%d%d", &u , &v , &c );
			u-- , v--;
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
			wei[ u ].push_back( c );
			wei[ v ].push_back( c ); 
			edge[ i ] = pii( u , v );
		}
		dfs( 0 );
		sparse();

		while( scanf("%s", order ) == 1 and order[ 0 ] != 'D' ){
			int a , b ; scanf("%d%d" , &a , &b );
			if( order[ 0 ] == 'Q' ){
				printf("%d\n" , query( a - 1 , b - 1 ) );
			}
			else{ 
				update( a - 1 , b );
			}
		}
		if( test ) printf("\n");
	}
	return 0;
}

