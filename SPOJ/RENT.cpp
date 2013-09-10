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

#define MAXN 2000010

int maxn[ MAXN * 4 ];
struct tree{
	void clear(){
		memset( maxn, 0 , sizeof maxn );
	}
	int query( int b , int e, int pos , int id ){
		if( e < pos ) return 0;
		if( b >= pos ) return maxn[ id ];
		int mid = ( b + e ) / 2;
		int l = id * 2 , r = id * 2 + 1;
		int ans_l =	query( b , mid , pos , l );
		int ans_r = query( mid + 1 , e , pos , r );
		return max( ans_l , ans_r );
	}
	void update( int b , int e , int pos , int val , int id , int clear = 0 ){
		if( pos < b or e < pos ) return ;
		if( b == e ){
			if( clear ) maxn[ id ] = 0;  
			else		maxn[ id ] = max( maxn[ id ] , val );
			return;
		}
		int mid = ( b + e ) / 2;
		int l = id * 2 , r = id * 2 + 1;
		update( b , mid , pos , val, l , clear );
		update( mid + 1 , e , pos , val , r , clear );
		maxn[ id ] = max( maxn[ l ] , maxn[ r ] );
	}
} stree ;

pair< pii , int > data[ MAXN ];

int main(){
	int test;
	scanf("%d" ,&test );
	while( test-- ){
		int n ; scanf("%d", &n );
		rep( i , n ){
			int a , b , c ;
			scanf("%d%d%d" , & a , & b , & c );
			data[ i ] = mp( mp( a , a + b ) , c ) ;
		}
		sort( data , data + n );
		for( int i = n - 1 ; i >= 0 ; i -- ){
			int nxt = data[ i ].fst.snd;
			int ans = data[ i ].snd + stree.query( 0 , MAXN - 1 , nxt , 1 );  
			stree.update( 0 , MAXN - 1 , data[ i ].fst.fst , ans , 1 );
		}
		int ans = stree.query( 0 , MAXN - 1 , 0 , 1 );
		rep( i , n ) stree.update( 0 , MAXN -1 , data[ i ].fst.fst , 0 , 1 , 1 ) ;
		printf("%d\n", ans );
	}
	return 0;
}

