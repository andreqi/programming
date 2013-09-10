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
#define MAXN 3000
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

vector< int > adj[ MAXN ];
int seen[ MAXN ] , in_stack[ MAXN ];
int low[ MAXN ];
stack< int > comp;
int timer = 0 , nscc = 0;

void read( int n , int m ){
	rep( i , n ) adj[ i ].clear();
	rep( i , m ){
		int u , v , t;
		scanf("%d%d%d" , & u , &v , &t );
		u-- , v--;
		adj[ u ].push_back( v ); 
		if( t == 2 ){ adj[ v ].push_back( u ); }
	}
}

int dfs( int v ) {
	low[ v ] = seen[ v ] = timer ++;
	int & low_v = low[ v ];
	in_stack[ v ] = 1;
	comp.push( v );
	rep ( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( seen[ u ] == -1 ){
			low_v = min( low_v , dfs( u ) );
		} else if( in_stack[ u ] ){
			low_v = min( low_v , seen[ u ] );
		}
	}
	if( low_v == seen[ v ] ){
		nscc++; int x;
		do{
			x = comp.top() , comp.pop();
			in_stack[ x ] = 0;
		} while( x != v );
	}
	return low_v;
}

void solve( int n ) {
	memset( seen , -1 , sizeof seen );
	memset( in_stack , 0 , sizeof in_stack );
	memset( low , -1 , sizeof seen );
	timer = 0;
	nscc = 0;
	rep ( i , n ) if( seen[ i ] == -1 ) {
		dfs( i ) ;
	}
	printf("%d\n" , nscc == 1 );
}

int main(){
	int n , m;
	while( scanf("%d%d" , &n , &m ) == 2 and n + m ) {
		read( n , m );
		solve( n );
	}
	return 0;
}

