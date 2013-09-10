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
#define MOD 1000000007LL
#define MAXN 360002
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int S , P;
int angle[ MAXN ];
int d[ MAXN ];		// restas consecutivas
bool read(){
	scanf( "%d%d" , &S, &P );
	if( S + P == -2 ) return false;
	rep( i , P )	scanf( "%d" , angle + i ) ;
	return true;
}

void preprocess(){
	d[ 0 ] = angle[ 0 ] + 360000 - angle[ P - 1 ];
	repn( i , 1 , P ) d[ i ] = angle[ i ] - angle[ i - 1 ];
}


int64 sum( int64 a , int64 b ) {
	return ( ( a % MOD ) + ( b % MOD ) ) % MOD;
}
int64 mult( int64 a , int64 b ) {
	return ( sum( a , 0LL ) * sum( b , 0LL ) ) % MOD; 
}
int64 mod_exp( int64 a , int64 b ){
	if( b == 1 ) return a;
	int64 c = mod_exp( a , b / 2 );
	c = mult( c , c );
	if( b & 1 ) c = mult( c , a );
	return c;
}

int64 calc_min_len(){

}

int64 solve(){
	if( P == 1 ) return S;
	preprocess();
	int64 min_len = calc_min_len();
	if( min_len == 1LL )
		return mod_exp( S , P );
	else				
		return sum  ( mod_exp( S , P ) ,
					( P / min_len  - 1 ) * mod_exp( S , P / min_len ) );
}

int main(){
	while( read() ){
		int64 ans = solve();
	}
	return 0;
}

