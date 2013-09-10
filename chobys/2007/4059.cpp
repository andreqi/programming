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
#define MAXN 1010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int deg[ MAXN ];
int impar[ MAXN ];
int color[ MAXN ] , seen[ MAXN ];
int clen;
vector< int > adj[ MAXN ];

void dfs( int v , int id ){
	color[ v ] = id;
	rep( i , adj[ v ].size() ) if( color[ adj[ v ][ i ] ] == -1 ){
		dfs( adj[ v ][ i ] , id );
	}
}

int main(){
	int v , e , t , tcase = 1 ;
	while( scanf("%d%d%d" , &v , &e , &t ) == 3 and v + e + t ){
		memset( seen , 0 , sizeof seen );
		int ans = e ;
		if( e ){
			rep( i , v ) deg[ i ] = 0;
			rep( i , v ) adj[ i ].clear();
			rep( i , e ){
				int a , b ; 
				scanf( "%d%d" ,&a , &b );
				a-- , b --;
				adj[ a ].push_back( b );
				adj[ b ].push_back( a );
				deg[ a ]++ , deg[ b ]++;
				seen[ a ] = 1 , seen[ b ] = 1;
			}
			clen = 0;
			memset( color , -1 ,sizeof color );
			rep( i , v ) if( color[ i ] == -1 and seen[ i ] ) {
				dfs( i , clen++ );
			}
			rep( i , v ) impar[ i ] = 0;
			rep( i , v ) if( color[ i ] != -1 ) {
				impar[ color[ i ] ] += ( deg[ i ] % 2 );
			}
			rep( i , clen ) if( impar[ i ] ){
				ans += ( impar[ i ] - 2 ) / 2 ; 
			}
			ans += clen  - 1 ;
		}
		printf("Case %d: %d\n" , tcase++, ans * t );
	}
	return 0;
}

