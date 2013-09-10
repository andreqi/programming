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

#define MAXN 30001 

char brkts[ MAXN + 1 ];
struct seg_tree {
	int mini[ MAXN * 4 ], sum[ MAXN * 4 ];
	void build( int ini , int fin , int id = 1 ){
		if( ini == fin ) {
			mini[ id ] = sum[ id ] = ( ( brkts[ ini ] == '(') ? 1 : -1 ) ;  
			return;
		}
		int mid = ( ini + fin ) / 2;
		build( ini , mid , id * 2 );
		build( mid + 1 , fin , id * 2 + 1 );
		sum[ id ] = sum[ id * 2 ] + sum[ id * 2 + 1 ];
		mini[ id ] = min( mini[ id * 2 ] , mini[ id * 2 + 1 ] + sum[ id * 2 ] );
	}

	void update( int n , int b , int e , int id = 1 ){
		if( n > e ) return ;
		if( n < b ) return ;
		if( b == e ){
			mini[ id ] = sum[ id ] = -sum[ id ];
			return;
		}
		int mid = ( b + e ) / 2 ;
		update( n , b , mid , id * 2 );
		update( n , mid + 1 , e , id * 2 + 1 );
		sum[ id ] = sum[ id * 2 ] + sum[ id * 2 + 1 ];
		mini[ id ] = min( mini[ id * 2 ] , mini[ id * 2 + 1 ] + sum[ id * 2 ] );
	}
	bool valid(){
		return mini[ 1 ] >= 0 and sum[ 1 ] == 0;
	}
} stree;

int main(){
	int n  , m ;
	int tcase = 1;
	while( scanf("%d\n" , &n ) == 1 ){
		gets( brkts );
		scanf("%d" , & m );
		stree.build( 0 , n - 1 );
		printf("Test %d:\n" , tcase++ );
		while ( m-- ){
			int op; scanf( "%d" , & op );
			if( op ){
				stree.update( op - 1 , 0 , n - 1 );
			} else
				printf( stree.valid() ? "YES\n" : "NO\n") ;
		}
	}
	return 0;
}

