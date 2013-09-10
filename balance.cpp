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

pair< int , pii > edge[ MAXN ]; 

struct disjoin_set{
	int pai[ MAXN ];
	void clear( int n ){
		rep( i , n ) pai[ i ] = i;
	}
	int find_set( int x ){ 
		if( x == pai[ x ] ) return x;
		return pai[ x ] = find_set( pai[ x ] );
	}
	void union_set( int u , int v ){
		int pa = find_set( u );
		int pb = find_set( v );
		pai[ pa ] = pai[ pb ];
	}
} ufind;

int s , t;
vector< int > adj[ MAXN ];
vector< int > we[ MAXN ];
int e_max[ MAXN ] , e_min[ MAXN ];


int solve( int v , int e , int id ){
	ufind.clear( v );
	rep( i , v ) adj[ i ].clear();
	rep( i , v ) we[ i ].clear();
	while( id >= 0 and ( ufind.find_set( s ) != ufind.find_set( t ) ) ){
		int a = edge[ id ].snd.fst , b = edge[ id ].snd.snd; 
		int c = edge[ id ].fst;
		if( ufind.find_set( a ) != ufind.find_set( b ) ) {
			adj[ a ].push_back( b );
			we[ a ].push_back( c );
			adj[ b ].push_back( a );
			we[ b ].push_back( c );
			ufind.union_set( a , b );
		}
		id--;
	}
	if( ufind.find_set( s ) != ufind.find_set( t ) ) return -1;
	queue< int > q;
	q.push( s );
	rep( i , v ) e_max[ i ] = -1;
	e_max[ s ] = -2;
	e_min[ s ] = 1 << 30;
	while( not q.empty() ){
		int cur = q.front(); q.pop();
		if( cur == t ){
			return e_max[ cur ] - e_min[ cur ];
		}
		rep( i , adj[ cur ].size() ) {
			int nxt = adj[ cur ][ i ];
			if( e_max[ nxt ] != -1 ) continue;
			e_max[ nxt ] = max( e_max[ cur ] , we[ cur ][ i ] );
			e_min[ nxt ] = min( e_min[ cur ] , we[ cur ][ i ] );
			q.push( nxt );
		}
	}
	return -1;
}

int main(){
	int n , m;
	while( scanf("%d%d" , &n , &m ) == 2 and n + m ){
		rep( i , m ){
			int u , v , d;
			scanf("%d%d%d" , &u , &v , &d );
			u--; v--;
			edge[ i ] = mp( d , pii( u , v ) );
		}
		scanf("%d%d" , & s , &t );
		s-- ; t --;
		sort( edge , edge + m ) ;
		int ans = -1;
		for( int ban = m - 1; ban >= 0 ; ban -- ){
			int banned = solve( n , m , ban );
			if( banned == -1 ) continue;
			if( ans == -1 or ans > banned ) ans = banned;
		}
		printf( "%d\n", ans );
	}
	return 0;
}

