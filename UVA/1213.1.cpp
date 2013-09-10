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
int cache[ MAXN ][ PRIMEN ][ MAXK ];
vector< int > prime;
int usd[ MAXN ];

int ways( int n , int id_p , int left ){
	int & ans = cache[ n ][ id_p ][ left ];
	if( ans != -1 ) 	return ans;
	if( left == 0 ) 	return n == N ;
	if( n == N ) 		return ans = left == 0;
	if( id_p == prime.size() ) return ans = 0;
	ans = n + prime[ id_p ] > N ? 0 : ways( n + prime[ id_p ] , id_p + 1 , left - 1 ) ; 
	ans += ways( n , id_p + 1 , left );
	return ans;
}


void cribe( int top ) {
	usd[ 0 ] = usd[ 1 ] = 1;
	repn( i , 2 , top ) if( not usd[ i ] ){
		for( int j = i + i ; j < MAXN ; j += i )
			usd [ j ] = 1;
	}
	rep( i , top ) if( not usd[ i ] ) prime.push_back( i ) ;
}

int main(){
	cribe( MAXN );
	while( scanf("%d%d", &N , &K ) == 2 ){
		if( N + K == 0 ) break;
		memset( cache , -1 , sizeof cache );
		int ans = ways( 0 , 0 , K );
		printf( "%d\n" , ans );
	}
	return 0;
}

