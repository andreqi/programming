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
const int MAXN = 12312123;

int usd[ MAXN + 1 ];

struct pollard_rho{
	vector< int64 > divi;
	vector< int64 > primes;
	int64 c;

	pollard_rho(){
		usd[ 0 ] = 1; usd[ 1 ] = 1;  
		rep( i , MAXN ) if( !usd[ i ] ) {
			for( int j = i + i ; j < MAXN ; j+= i ) usd[ j ] = 1;
		}
		rep( i , MAXN ) if( !usd[ i ] ) primes.push_back( i ); 
	}

	void clear(){
		c = 123412341;
		divi.clear();
	}
	
	int64 sqr( int64 x , int64 n ){ return ( x % n )  * ( x % n ) ; }

	int64 f( int64 x , int64 n ){
		return ( ( sqr( x , n ) % n + c % n ) % n + n ) % n ; 
	}

	int64 rho( int64 n ){
		if( ( n & 1LL )  == 0LL ) return 2LL; 
		if( n % 3 == 0LL ) return 3LL;
		int64 x = abs( rand() );
		int64 y = x , div ;
		do{
			x = f( x , n );
			y = f( f( y  , n ) , n );
			div = __gcd( abs( x - y ) , n );
		} while( div == 1LL ); 
		return div;
	}
	void factor( int64 n ){
		if( n == 1LL ) return;
		int64 d = rho( n ) ;
		if( d == n ){
			divi.push_back( d );
			return;
		}
		factor( d );
		factor( n / d );
	}

	void factorize( int64 n ){
		for( int i = 0 ; i < primes.size() and n >= primes[ i ] ; i++ )
			while( n % primes[ i ] == 0LL ){
				divi.push_back( primes[ i ] );
				n /= primes[ i ];
			}
		factor( n );
	}

} solver;



void solve( int64 n ) {
	solver.clear();
	solver.factorize( n );
	vector< int64 > v = solver.divi;
	sort( all( v ) );
	rep( i , v.size() ) cout << v[ i ] << endl;
}

int main(){
	int64 n;
	while( cin >> n  and n >= 0  ){
		solve( n );
		cout << endl;
	}
	return 0;
}

