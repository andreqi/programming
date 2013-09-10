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
#define MAXN 200
#define MAXKNAP 10001
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int n , id_p ;
int value[ MAXN ];
int can[ MAXKNAP + 1 ];
bool read(){
	int a , b;
	scanf("%d%d", &n , &id_p );
	if( n + id_p == 0 ) return false;
	id_p --;
	rep( i , n ){
		scanf( "%d.%d" , &a , &b );
		value[ i ] = a * 100 + b;
	}
	return true;
}

double solve(){
	if( value[ id_p ] == 0 ) return 0;
	swap( value[ 0 ] , value[ id_p ] );
	memset( can , 0 , sizeof can );
	can[ 0 ] = 1;
	rep( i , n - 1 ) for( int j = MAXKNAP - 1 ; j >= value[ i + 1 ] ; j -- ){
		can[ j ] |= can[ j - value[ i + 1 ]];
	}
	double ans = 0;
	for( int i = 0 ; i < MAXKNAP ; i ++ ) if ( can[ i ] ) {
		int denom = i + value[ 0 ];
		if( denom <= 5000 ) continue;
		ans = max( ans , ( value [ 0 ] * 100.0 ) / ( ( double ) denom ) );
	}
	return ans;
}
int main(){
	while( read() ) 
		printf( "%.02lf\n" , solve() );
	
	return 0;
}

