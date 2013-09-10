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

int n, m;
int64 A[ 200 ];
int64 a[ 200 ];
int64 B[ 200 ], b[ 200 ];
int64 dp[ 200 ][ 200 ];

int64 f( int i , int j ){
	if( i == n or j == m ) return 0;
	int64 & ans = dp[ i ][ j ];
	if( ans != -1LL ) return ans;
	ans = 0LL;
	ans =  max( f( i + 1 , j ) , f( i , j + 1 ) );
	int64 q = a[ i ] , sell = 0;
	repn( k , j , m ){
		if( q >= b[ k ] and A[ i ] == B[ k ] ){
			q -= b[ k ];
			sell += b[ k ];
			ans = max( ans , sell + f( i + 1, k + 1 ) );
		}
		else if( A[ i ] == B[ k ] and q < b[ k ] ) {
			int64 r = b[ k ] ;
			repn( l , i , n ){
				if( r >=
			}
			break;
		}
	}
	return ans;
}

int64 solve(){
	int64 ans = 0;
	memset( dp , -1 , sizeof dp );
	cin >> n >> m;
	rep( i , n ) cin >> a[ i ] >> A[ i ];
	rep( i , m ) cin >> b[ i ] >> B[ i ];
	return f( 0, 0 );
}

int main(){
	int test;
	cin >> test;
	rep( t , test ){
		printf("Case #%d: ", t + 1 );
		cout << solve() << endl;
	}
	return 0;
}

