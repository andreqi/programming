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
#define MAXN 110
#define MAXM 110
#define MAXW 1010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct entry{
	int i , j , w;
	int dis;
	entry(){}
	entry( int a , int b , int c , int d ){
		i = a , j = b , w = c , dis = d;
	}
	bool operator < ( entry a ) const {
		if( dis != a.dis )
			return dis < a.dis;
		if( a.i != i )	return i < a.i;
		if( a.j != j )	return j < a.j;
		return w < a.w;
	}
};

int F[ MAXN ][ MAXN ];
int dx[] = { 0 , 0 , 1 , -1 };
int dy[] = { 1 , -1 , 0 , 0 };
int C[ MAXN ][ MAXN ];
int N , M , H ;

double dis[ MAXN ][ MAXN ][ MAXW ];

int min_wait( int x ,int y , int a , int b , int water ){
	int df = C[ x ][ y ] - F[ a ][ b ];
	int dg = C[ a ][ b ] - F[ x ][ y ];
	int dw = C[ a ][ b ] - water;
	if( df < 50 or dg < 50 or dw < 50 ){
		if( dg < 50 or df < 50 ) return -1;
		return 50 - dw;
	}
	return 0;
}

double solve(){
	cin >> N >> M >> H;
	H *= 10;
	rep( i , N ) rep( j , M ) cin >> C[ i ] [ j ];
	rep( i , N ) rep( j , M ) cin >> F[ i ] [ j ];
	rep( i , MAXN ) rep( j , MAXN ) rep( k , MAXW ) dis[ i ][ j ][ k ] = -1;  
	set< entry > q; 
	q.insert( entry( 0 , 0 , H , 0 ) );
	dis[ 0 ][ 0 ][ H ] = 0;
	double ans = 0;
	while( not q.empty() ){
		entry cur = *q.begin();
		cout << cur.i << " " << cur.j << endl;
		q.erase( q.begin() );
		if( cur.i == N - 1 and cur.j == M - 1 ) return ( double )cur.dis / 10.0;
		rep( i , 4 ){
			int nx = cur.i + dx[ i ];
			int ny = cur.j + dy[ i ];
			if( nx < 0 or ny < 0 or nx >=N or ny >=M ) continue;
			int wait_water = min_wait( cur.i , cur.j , nx , ny , cur.w );
			if( wait_water == -1 ) continue;
			int next_water = cur.w - wait_water ;
			int ndis = cur.dis + wait_water + ( ( cur.w - F[ cur.i ][ cur.j ] ) >= 20  ? 10 : 100 );
			int ww;
			entry new_entry = entry( nx , ny , ww = max( next_water - 10 , 0 ), ndis );
			if( dis[ nx ][ ny ][ ww ] != -1 ) continue;
			dis[ nx ][ ny ][ ww ] = ndis;
			q.insert( new_entry );
		}
	}
	return ans;
}

int main(){
	int t;
	cin >> t;
	repn( test , 1 , t + 1 ){
		printf("Case #%d: %lf\n" , test , solve() );
	}
	return 0;
}

