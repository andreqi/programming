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

typedef unsigned int int64;
typedef long double ldouble;
typedef pair< int , int > pii;

map< int64 , int64 > dis;
int64 dig[ 10 ] , d10[ 20 ];
int64 suff[ 10 ] , pre[ 11 ];
void bfs(){
	int64 ini = 123456789 , cur , x , pref ,weight , nxt , rev;
	dis[ ini ] = 0; 
	d10[ 0 ] = 1;
	rep( i , 13 ) d10[ i + 1 ] = d10[ i ] * 10;
	queue< int64 > q;
	q.push( ini );
	while( not q.empty() ){
		cur = q.front(); q.pop();
		x = cur;
		pref = 0 ;
		weight = dis[ cur ] + 1;
		rep( i , 10 ){ dig[ i ] = x % 10 ; x /= 10; }
		x = cur;
		rep( i , 10 ){ pre[ i ] = x ; x /= 10 ; }
		x = 0;
		rep( i , 10 ){ x = x * 10 + dig[ i ] ; }
		rep( i , 10 ){ suff[ i ] = x ; x /= 10; }
		rep( i , 10 ) { 
			repn( j , i + 1 , 10 ) {
				nxt = pref;
				rev = suff[ 9 - j  ] % d10[ j - i + 1 ];
				nxt = nxt + rev * d10[ i ] + d10[ j + 1 ] * pre[ j + 1 ]; 
				if( dis.count( nxt ) ) continue;
				dis[ nxt ] = weight;
				q.push( nxt );
			}
			pref = pref + d10[ i ] * dig[ i ];
		}
	}
}

int hash( char c[] ){
	int ans = 0;
	rep( i , 10 )	ans = ( c[ i ] - '0' ) * d10[ i ]; 
	return ans;
}


char a[ 10 ] , b[ 10 ];
char trans[ 256 ];
int main(){
	bfs();
	return 0;
	while( scanf("%s %s" , a , b ) == 2 and a[ 0 ] != '*' ){
		rep( i , 10 ) trans[ b[ i ] ] = i + '0';  
		rep( i , 10 ) a[ i ] = trans[ a[ i ] ];
		printf("%d\n" , dis[ hash( a ) ] );
	}
	return 0;
}

