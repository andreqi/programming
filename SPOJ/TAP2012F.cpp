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

string op[ 10 ];
int pos[ 10 ];
char txt[ 200 ];
int n ;
int move(){
	int ans = -2 ;
	rep( i, n ) if( pos[ i ] < op[ i ].size() ){
		ans = max( ans , -1 );
		if( op[ i ][ pos[ i ] ] == '1' ) {
			ans = i;
			continue;
		}
		char id = '2' + i;
		int nxt = op[ i ][ pos[ i ] ] - '2';
	//	cout << nxt << " " << i << endl;
		if( op[ nxt ][ pos[ nxt ] ] == id ){
			pos[ i ]++ , pos[ nxt ]++;
			return -1;
		} 
	}
	//cout << " ans: " << ans << endl;
	return ans;
}

int main(){
	int id = 0;
	while( scanf("%d" , & n ) == 1 and n != -1 ){
		n--;
		rep( i , n ){
			scanf("%s" , txt);
			op[ i ] = string( txt );
		} 
		rep( i , 10 ) pos[ i ] = 0;
		while( true ){
			while( ( id = move() ) == -1 ); 
			if( id == -2 ) break;
			putchar( '2' + id );
			pos[ id ]++;
		}
		putchar( 10 );
	}
	return 0;
}

