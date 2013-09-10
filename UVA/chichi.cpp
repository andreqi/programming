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
#define mod 1000000000
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
#define MAXN 1010

int64 sum( int64 a , int64 b = 0LL ){
	return ( a % mod + b % mod + mod ) % mod;
}

int64 mult( int64 a , int64 b ){
	return sum( sum( a ) * sum( b ) ); 
}

int64 c[ MAXN ];
int64 f[ MAXN ][ MAXN ];
int64 g[ MAXN ][ MAXN ];

int64 w( int left , int open ){
	if( open < 0 or left < 0 ) return 0LL; 
	if( left == 0 ) return 1LL;
	//if( left < open ) return 0LL;
	int64 & ans = g[ left ][ open ];
	if( ans != -1LL ) return ans;
	ans = sum( w( left - 1 , open + 1 ) , w( left , open - 1 ) );
	return ans;
}

int main(){
	
	c[ 0 ] = 1;
	rep( i , MAXN ) rep ( j , i ) 
		c[ i ] = sum( c[ i ] , mult( c[ j ] , c[ i - 1 - j ] ) );
	memset( g , -1 , sizeof f );
	f[ 0 ][ 0 ] = 1;
	repn( i , 1 ,  MAXN )	for( int j = MAXN - 2 ; j >= 0 ; j-- ) {
		f[ i ][ j ] = sum( f[ i ][ j ] , 
			 ( j and i ) ? f[ i - 1 ][ j - 1 ] : 0 ) ;
		f[ i ][ j ] = sum( f[ i ][ j ] , f[ i ][ j + 1 ] );
	}
	//rep ( i , 10 ) cout << w( i , 0 ) << endl;
	int n , x , y;
	while( cin >> n >> x >> y ){
		x--, y--;
		int64 ans = 0;
		rep( i , x + 1 ) rep ( j , n - y ) {
			// i : cuantas abiertas 
			// j : cuantas despues de cerrado x 
			int left = n - ( x + 1 + j );
			//cout << j << " " << left << " " << n << endl; 
			//ans = sum ( ans , mult ( c[ left  ] , mult( w( x , i ) , w ( j , i ) ) ) ) ;
			ans = sum( ans , mult ( c[ left ] , mult ( f[ x ][ i ] , w( j , i ) ) ) );
		}
		cout << ans << endl;
	}
	return 0;
}

