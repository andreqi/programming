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

#define MAXN 100001
#define tiene 1
#define no_tiene 0

int dp[ 2 ][ MAXN ];
int seen[ MAXN ], padre[ MAXN ];
int order[ MAXN ];
int timer = 0;

vector< int > adj[ MAXN ];

void topsort( int v , int pai = -1 ){
	seen[ v ] = true;
	padre[ v ] = pai;
	rep( i , adj[ v ].size() ) {
		int u = adj[ v ][ i ];
		if( u == pai ) continue;
		if( seen[ u ] ) continue;
		topsort( u , v ); 
	}
	order[ timer++ ] = v ;
}
int main(){
	int n , u  , v , sum_g , sum_f ; 
	scanf("%d" , & n ) ; 
	rep( i , n - 1 ){
		scanf("%d%d" ,& u , & v );
		u-- , v--;
		adj[ u ].push_back( v );
		adj[ v ].push_back( u );
	}
	topsort( 0 );
	rep( i , n ){
		v = order[ i ];
		sum_g = 1 , sum_f = 0;
		rep( j , adj[ v ].size() ){
			u = adj[ v ][ j ];
			if( u == padre[ v ] ) continue;
			sum_g += dp[ tiene ][ u ];
			sum_f += dp[ no_tiene ][ u ];
		}
		dp[ tiene ][ v ] = min( sum_g , sum_f );
		dp[ no_tiene ][ v ] = sum_g;
	}
	printf("%d\n" , dp[ tiene ][ 0 ] );
	return 0;
}

