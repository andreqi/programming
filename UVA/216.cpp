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
#define foreach( i , a ) for( typeof( a )::iterator i = n.begin() , i != a.end , i++ )
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

double x[ 10 ] , y[ 10 ];

double dp[ 1 << 9 ][ 10 ];
double child[ 1 << 9 ][ 10 ];
double dis( int i , int j ){
	double dx = x[ i ] - x[ j ];
	double dy = y[ i ] - y[ j ];
	return sqrt( dx * dx + dy * dy );
}
int n ;
double f( int mask , int last ){
	double & ans = dp[ mask ][ last ];
	double & ch = child[ mask ][ last ];
	if( ans > -.5 ) return ans;
	if( mask == ( ( 1 << n ) - 1 ) ) return ans = 0;
	ans = 1e40;
	rep( i , n ) if( mask & ( 1 << i ) ) {}
	else {
		int nmask = mask | ( 1 << i );
		double nxt = f( nmask , i ) + dis( i , last ) + 16.0;
		if( ans > nxt ){
			ans = nxt;
			ch = i;
		}
	}
	return ans;
}
int main(){
	vector< int > x;
	foreach( item , x ){}
	int tcase = 1;
	while( cin >> n and n ){
		rep( i , n ) cin >> x[ i ] >> y[ i ];
		rep( i , ( 1 << 8 ) ) rep( j , n ) dp[ i ][ j ] = -1;
		int ini = -1 ; double len = 0;
		rep( i , n ) {
			double tmp = f( 1 << i  , i );
			if( ini == -1 or tmp < len ){
				ini = i , len = tmp;
			}
		}
		printf("**********************************************************\n");
		printf("Network #%d\n", tcase++ );
		int fin = ini , mask = 1 << ini;
		while( mask != ( 1 << n ) - 1 ){
			int c = child[ mask ][ fin ];
			printf("Cable requirement to connect (%.0lf,%.0lf) to (%.0lf,%.0lf) is %.2lf feet.\n",
				   x[ fin ] , y[ fin ] , x[ c ] , y[ c ] , dis( fin , c ) + 16.0 );
			mask |= ( 1 << c );
			fin = c;
		}
		printf("Number of feet of cable required is %.2lf.\n", len);
	}
	return 0;
}

