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
const int oo = 1 << 28;
int data[ 20 ] , n ;
pii dp[ 1 << 15 ][ 20 ];

pii perim( int mask, int prev , int left ){
	pii & ans = dp[ mask ][ prev ];
	if( ans.fst != -1 ) return ans;
	if( left == 0 ) return ans = pii( data[ prev ] , 1 );
	ans = pii ( 0 , 0 );
	int max_area = -oo , ways = 0;
	rep( i , n ) if( mask & ( 1 << i ) ){
		int cost = abs( data[ prev ] - data[ i ] ) + 1;
		pii nxt = perim( mask ^ ( 1 << i ) , i , left - 1 );
		nxt.fst += cost;
		max_area = max( nxt.fst , max_area );
	}
	rep( i , n ) if( mask & ( 1 << i ) ){
		int cost = abs( data[ prev ] - data[ i ] ) + 1;
		pii nxt = perim( mask ^ ( 1 << i ) , i , left - 1 );
		if( max_area == nxt.fst + cost ) ways += nxt.snd;
	}
	return ans = pii( max_area , ways );
}

int main(){
	while( scanf("%d", &n ) == 1 and n ){
		rep( i , n ) scanf("%d" , data + i );
		data[ n ] = 0;
		rep( i , ( 1 << n ) ) rep ( j , n + 1 ) dp[ i ][ j ] = pii( -1 , 0 );
		pii ans = perim( ( 1 << n ) - 1 , n , n );
		printf("%d %d\n" , ans.fst + n , ans.snd );
	} 
	return 0;
}

