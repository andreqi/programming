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

#define MAXN 100011

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef vector< int > vi;

vi adj[ MAXN ];
int begin[ MAXN ] , end[ MAXN ] ;
int seen[ MAXN ] , timer = 0; 
int pai[ MAXN ] , lvl[ MAXN ];
int id[ MAXN ]; // nodos ordenados por ( lvl , begin )

int cmp_solver( int a , int b ){
	if( lvl[ a ] != lvl[ b ] ) return lvl[ a ] < lvl[ b ];
	return begin[ a ] < begin[ b ];
}
struct lca_solver {	// para sacar el padre a distancia d en O( log n )
	int dp[ MAXN ][ 30 ];
	void init( int n ){ // n : nro de nodos 
		rep ( i , n ) dp[ i ][ 0 ] = pai[ i ]; 
		for( int i = 1 ; ( 1 << i ) <= n ; i ++ ){
			rep( u , n ){
				int v = dp[ u ][ i - 1 ];
				if( v == -1 ) continue;
				dp[ u ][ i ] = dp[ v ][ i - 1 ];
			}
		}
	}
	int kth( int x , int k ){ // x : nodo , k: altura del padre
		if( lvl[ x ] < k ) return -1;
		for( int i = 28 ; i >= 0 and k ; i-- ) if( k >= ( 1 << i ) ){
			k -= ( 1 << i );
			x = dp[ x ][ i ];
		} 
		return x;
	}
} lca;

// preprocesamiento en O(n) para luego hacer sort 
// ( tambien se podria hacer bfs pero bueh ) 
void dfs( int v , int lvl_v ){
	lvl[ v ] = lvl_v; begin[ v ] = timer++;
	seen[ v ] = 1;
	rep( i, adj[ v ].size() ){
		dfs( adj[ v ][ i ] , lvl_v + 1 ) ;
	}
	end[ v ] = timer++;
}

int l_bound( pii target , int n ) {
	int lo = 0 , hi = n - 1;
	while( lo < hi ){
		int mid = ( lo + hi ) / 2;
		pii mid_val = pii( lvl[ id[ mid ] ] , begin[ id[ mid ] ] );
		if( mid_val < target )	lo = mid + 1;
		else					hi = mid;
	}
	return lo;
}
int u_bound( pii target , int n ){
	int lo = 0 , hi = n - 1;
	while( lo < hi ){
		int mid = ( lo + hi + 1 ) / 2;
		pii mid_val = pii( lvl[ id[ mid ] ] , begin[ id[ mid ] ] );
		if( mid_val >= target )	hi = mid - 1; 
		else					lo = mid;
	}
	return hi;
}

int main(){
	int n;
	cin >> n;
	rep( i , n ){
		int padre; cin >> padre;
		pai[ i ] = padre - 1;
		if( !padre ) continue;
		adj[ padre - 1 ].push_back( i );
	}
	rep( i , n ) id[ i ] = i;
	rep( i , n ) if( !seen[ i ] ){
		dfs( i , 0 );
	} 
	sort( id , id + n , cmp_solver ) ;
	lca.init( n );
	int q;
	cin >> q;
	while( q-- ){
		int x , d;
		cin >> x >> d;
		x--;
		int padre = lca.kth( x , d );
		if( padre == -1 ) cout << 0 ;
		else{
			// sacar lower y upper de ( d + lvl[ pai ] , begin[ pai ] ) ( d + lvl[ pai ] , end[ pai ] )
			int b = l_bound( pii( lvl[ padre ] + d , begin[ padre ] ) , n );
			int e = u_bound( pii( lvl[ padre ] + d , end[ padre ] ) , n );
			cout << e - b ;
		}
		if( q ) cout << " ";
	}
	cout << endl;

	return 0;
}

