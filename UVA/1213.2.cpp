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
#define MAXN 1124
#define PRIMEN 190
#define MAXK 15
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int N , K ;
int dp[ MAXN ][ MAXK ][ 2 ];
vector< int > prime;
int usd[ MAXN ];

void cribe( int top ) {
	usd[ 0 ] = usd[ 1 ] = 1;
	repn( i , 2 , top ) if( not usd[ i ] ){
		for( int j = i + i ; j < MAXN ; j += i )
			usd [ j ] = 1;
	}
	rep( i , top ) if( not usd[ i ] ) prime.push_back( i ) ;
}

int iterative(){
	memset( dp , 0 , sizeof dp );
	int prev = prime.size() ;
	dp[ N ][ 0 ][ prev & 1  ] = 1;
	for( int i = prev - 1 ; i >= 0 ; i-- ){
		int cur = i & 1 , last = 1 - ( i & 1 );
		rep( n , N + 1 ) rep( left , K + 1 ){
			dp[ n ][ left ][ cur ] = dp[ n ][ left ][ last ];
			if( left != 0 and n + prime[ i ] <= N )
				dp[ n ][ left ][ cur ] += dp[ n + prime[ i ] ][ left - 1 ][ last ];
		}
	}
	return dp[ 0 ][ K ][ 0 ];
}

int main(){
	cribe( MAXN );
	while( scanf("%d%d", &N , &K ) == 2 ){
		if( N + K == 0 ) break;
		int ans = iterative();
		printf( "%d\n" , ans );
	}
	return 0;
}

