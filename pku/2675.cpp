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
#define MAXN ( 1 << 17 )
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
int n , sel;
double rank[ MAXN ] , freq[ MAXN ];
int id[ MAXN ], pi[ MAXN ], len[ MAXN ];

int read(){
	int op = scanf("%d" , & n );
	if( op != 1 ) return false;
	rep( i , n ) scanf("%d %d %lf" , id + i , len + i , freq + i );
	scanf("%d" , &sel );
	return true;
}

int cmp( int a , int b ){
	return freq[ b ] * len[ a ] < freq[ a ] * len[ b ] ;
}

void solve(){
	rep( i , n ) pi[ i ] = i;
	sort( pi , pi + n , cmp );
	printf("%d\n" , id[ pi[ sel - 1 ] ] );
}

int main(){
	while( read() ){
		solve();
	}
	return 0;
}

