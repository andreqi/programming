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

int64 t[] = { 1231231LL , 0LL };

const int MAXN = 10000000;
int usd[ MAXN ];

struct pollard_rho{
	vector< int64 > f;
	vector< int64 > primes;
	
	pollard_rho(){
		usd[ 0 ] = usd[ 1 ] = 1; 
		rep( i , MAXN )  if( usd[ i ] == 0 ){
			for( int j = i + i ; j < MAXN ; j += i ){
				usd[ j ] = 1;
			}
		}
		rep( i , MAXN ) if( usd[ i ] == 0 )
			primes.push_back( i );
	}

	int64 fx( int64 x , int64 mod , int64 c ){
		int64 a = x * x;
		a %= mod;
		a += c + mod;
		a %= mod;
		return a ;
	}

	int64 rho( int64 n , int64 c ){
		if( n % 2LL == 0LL ) return 2LL;
		int64 x = abs( rand() ) ;
		int64 y = x , div ;
		do{
			x = fx( x , n , c );
			y = fx( fx( y , n , c ) , n , c );
			div = __gcd( abs( x - y ) , n );
		} while( div == 1LL );
		return div;
	}

	void factor( int64 n ){
		if( n == 1LL ) return ;
		int64 d;
		for( int i = 0 ; t[ i ] ; i++ ){
			d = rho( n , t[ i ] );
			if( d == n ) continue;
			factor( d );
			while( n % d == 0LL ){
				 n /= d ; 
			}
			factor( n );
			return;
		}
		f.push_back( n );
	}

	vector< int64 > factorize( int64 n ){
		f.clear();
		int64 x = n;
		for( int i = 0 ; i < primes.size() and primes[ i ] * primes[ i ] <= n ; i ++ ){
			while( n % primes[ i ] == 0 ){
				f.push_back( primes[ i ] );
				n /= primes[ i ];
			}
		}
		if( x == n )
			f.push_back( n );
		else
			factor( n );
		return f;
	} 
	
} solver;

void print( int64 a , int b ) {
	cout << ' ' << a ;
	if( b > 1 ) cout << "^" << b ;
}

void solve(){
	int64 n;
	cin >> n;
	vector< int64 > f = solver.factorize( n );
	sort( all( f ) );
	cout << n << " =";
	rep( i , f.size() ){
		int j = i;
		while( j < f.size() and f[ i ] == f[ j ] ) j++;
		if( i ) cout << " *";
		print( f[ i ] , j - i );
		i = j - 1;
	}
	cout << endl;
}

int main(){
	int test;
	cin >> test;
	rep( i , test ){
		solve( ); 
	}
	return 0;
}

