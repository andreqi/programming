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
typedef pair< int , double > node;

int ticket[ 20 ];
node dp[ 1 << 8 ][ 30 ];
int target , t_size ;
vector< int > adj[ 30 ];
vector< int > wei[ 30 ];

node path( int mask, int cur ){
	node & ans = dp[ mask ][ cur ];
	if( ans.fst != -1 ) return ans;
	if( cur == target ) return ans = node( 1 , 0 );
	if( mask == 0 ) return ans = node( 0 , 0 );
	rep( i , adj[ cur ].size() ){
		int nxt = adj[ cur ][ i ];
		rep( j , t_size ) if ( ( 1 << j ) & mask ) {
			node nxt_ans = path( mask ^ ( 1 << j ) , nxt );
			if( not nxt_ans.fst ) continue;
			nxt_ans.snd += (double) ( wei[ cur ][ i ] ) / ( double ) ticket[ j ];
			if( ans.fst == -1 or ans.snd > nxt_ans.snd ) {
				ans = nxt_ans;
			}
		}
	}
	if( ans.fst == -1 ) ans = node( 0 , 0 );
	return ans;
}

int main(){
	int n , m , p , a , b , u , v , w;
	while( scanf("%d%d%d%d%d" , & n , &m , &p , & a , &b ) == 5 and n + m + a + b + p ){
		target = b - 1;
		t_size = n;
		rep( i , n ) scanf("%d" , ticket + i ) ;
		rep( i , ( 1 << 8 ) ) rep( j , 30 ) dp[ i ][ j ] = node( -1 , 0 );
		rep( i , m ) adj[ i ].clear();
		rep( i , m ) wei[ i ].clear();
		rep( i , p ) {
			scanf("%d%d%d" , &u , &v , &w );
			u--,v--;
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
			wei[ u ].push_back( w );
			wei[ v ].push_back( w );
		}
		node ans = path( ( 1 << n ) - 1 , a - 1 );
		if( ans.fst == 0 )	printf("Impossible\n");
		else				printf("%.6lf\n" , ans.snd );
	}
	return 0;
}

