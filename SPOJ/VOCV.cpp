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
#define MAXN 100110
#define MOD 10007

vector< int > adj[ MAXN ];
pii dp[ MAXN ][ 2 ]; 
int sum( int a , int b = 0 ){ return ( a % MOD + b % MOD + MOD ) % MOD; }
int mult( int a , int b ){ return ( sum( a ) * sum( b ) ) % MOD; }

pii off( int , int );

pii on( int node , int pai ){
	pii & ans = dp[ node ][ 1 ];
	if( ans.fst != -1 ) return ans;
	pii put = off( node , pai );
	int maxim = 0 , ways = 1;
	rep( i , adj[ node ].size() ){
		int nxt = adj[ node ][ i ];
		if( nxt == pai ) continue;
		pii eval = off( nxt , node );
		maxim += eval.fst;
		ways = mult( ways , eval.snd );
	}
	ans.fst = min( put.fst , maxim );
	ans.snd = 0;
	if( put.fst == ans.fst ) ans.snd = sum( put.snd , ans.snd );
	if( maxim == ans.fst ) ans.snd = sum( ways , ans.snd );
	return ans;
}
pii off( int node , int pai ){
	pii & ans = dp[ node ][ 0 ];
	if( ans.fst != -1 ) return ans;
	int maxim = 1 , ways = 1;
	rep( i , adj[ node ].size() ){
		int nxt = adj[ node ][ i ];
		if( nxt == pai ) continue;
		pii eval = on ( nxt , node );
		maxim += eval.fst;
		ways = mult( ways , eval.snd );
	}  
	return ans = pii( maxim , ways ); 
}

int main(){
	int test;
	int n, a , b;
	scanf("%d" , &test );
	while( test-- ){
		scanf("%d" , &n );
		rep( i , n ) adj[ i ].clear();
		rep( i , n ) rep( j , 2 ) dp[ i ][ j ] = pii( -1 , -1 );
		rep( i , n - 1 ){
			scanf("%d%d" , &a , &b );
			a-- , b--;
			adj[ a ].push_back( b );
			adj[ b ].push_back( a );
		}
		pii ans = on( 0 , -1 );
		printf("%d %d\n" , ans.fst , ans.snd );
	}
	return 0;
}

