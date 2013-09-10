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

int64 raiz( int64 n ){
	int64 lo = 0 , hi = 100000 , mid;
	while( lo < hi ){
		mid = ( lo + hi + 1 ) / 2;
		if( mid * mid > n ) hi = mid - 1;
		else				lo = mid;
	}
	return lo;
}

int main(){
	int64 n;
	while( scanf("%lld" , &n ) == 1 and n ) {
		int64 sq = raiz( n );
		n -= sq * sq;
		if( n == 0 ){
			int x = 1 , y = sq;
			if( y % 2 == 0 ) swap( x , y ); 
			printf("%d %d\n" , x , y );
		}
		else {
			int x = 1 , y = sq + 1 , id = sq + 1;
			int queda = n - 1;
			x += min( queda , id - 1 );
			y -= max( 0 , queda - ( id - 1 ) );
			if( id % 2 ) swap( x , y );
			printf("%d %d\n" , x , y );
		}
	}
	return 0;
}

