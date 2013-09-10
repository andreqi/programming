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
#define MAXN 1010

char str[ MAXN ];
int palin[ MAXN ][ MAXN ];
int cache[ MAXN ];
int n;
const int oo = 1 << 28;

int partition( int i ){
	int & ans = cache[ i ];
	if( i == n ) return 0;
	if( ans != -1 ) return ans;
	ans = oo;
	for( int len = 1 ; len + i <= n ; len++ ){
		if( palin[ i ][ len ] ){
			ans = min( ans , 1 + partition( i + len ) );
		}
	}
	return ans;
}

int main(){
	int test = 0;
	scanf("%d" , &test );
	while( test-- ){
		scanf("%s" , str );
		n = strlen( str );
		rep( i , n ) rep( j , 2 ) palin[ i ][ j ] = 1;
		repn( len , 2 , n + 1 ){
			for( int i = 0 ; i + len <= n ; i++ ){
				palin[ i ][ len ] = palin[ i + 1 ][ len - 2 ] and
									str[ i ] == str[ i + len - 1 ]; 
			} 
		}
		rep( i , n + 1 ) cache[ i ] = -1;
		printf("%d\n", partition( 0 ) );
	}
	return 0;
}

