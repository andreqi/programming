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
#define MAXN 1001
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int64 matrix[ MAXN ][ MAXN ];
int64 ans[ MAXN ][ MAXN ];

int N , M;
bool read(){
	int op = scanf( "%d %d" , &N , &M ) ;
	if( op != 2 ) 	return false;
	memset( matrix , 0 , sizeof matrix );
	rep( i , N ) rep ( j , N ) scanf( "%lld" , matrix[ N - 1 - i ] + j + 1 );
	rep( i , N ) rep( j , N ) 
		matrix[ i ][ j + 1 ] += matrix[ i ][ j ] ;
	return true;
}

int64 range_sum( int row , int begin , int end ){
	return matrix[ row ][ end + 1 ] - matrix[ row ][ begin ];
}

void solve(){
	rep( i , N - M + 1 ) {
		int64 sum = 0; rep( j , M ) sum += range_sum( j , i , i + M - 1  ) ;
		ans[ 0 ][ i ] = sum;
		repn( j , M , N ){
			sum -= range_sum( j - M , i , i + M - 1 );
			sum += range_sum( j , i , i + M - 1 );
			ans[ j - M + 1 ][ i ] = sum;
		}
	}
	int64 sum = 0;
	rep( i , N - M + 1 ){
		rep( j , N - M + 1 ){
			printf( "%lld\n", ans[ N - M - i ][ j ] );
			sum += ans[ i ] [ j ];
		}
	}
	printf( "%lld\n" , sum );
}

int main(){
	int first = 1;
	while( read() ){
		if( first ) first = 0;
		else 		putchar( 10 );
		solve();	
	}
	return 0;
}

