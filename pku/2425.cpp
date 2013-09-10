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
#define MAXN 1011

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

vector< int > adj[ MAXN ];
int usd[ MAXN ];
int g[ MAXN ] , tsort[ MAXN ];
int v;
int timer;

void dfs( int node ){
	usd[ node ] = 1;
	rep( i , adj[ node ].size() ) if( !usd[ adj[ node ][ i ] ] ){
		dfs( adj[ node ][ i ] );
	}
	tsort[ timer++ ] = node;
}

void topsort(){
	timer = 0 ;
	memset( usd , 0 , sizeof usd );
	rep( i , v ) if( not usd [ i ] ) dfs( i );
}

bool read(){
	if( scanf("%d" , &v ) != 1 ) return false;
	rep( i , v ) {
		int len ; scanf("%d" , &len );
		adj[ i ].resize( len );
		rep( j , len ) scanf( "%d" , & adj[ i ][ j ] );
	}
	return true;
}

void compute_grundy(){
	topsort();
	rep( i , v ) {
		memset( usd , 0 , sizeof usd );
		int src = tsort[ i ];
		rep( j , adj[ src ].size() ) usd[ g[ adj[ src ][ j ] ] ] = 1; 
		int grundy = 0; 
		while( usd[ grundy ] ) grundy++;
		g[ src ] = grundy;
	}
}

void solve(){
	compute_grundy();
	int len;
	while( scanf("%d" , &len ) && len ){
		int win = 0;
		rep( i , len ) {
			int pos ; scanf( "%d" , & pos );
			win ^= g[ pos ];
		}
		if( win ) 	printf("WIN\n");
		else		printf("LOSE\n");
	}
}

int main(){
	while( read() ){
		solve();
	}
	return 0;
}

