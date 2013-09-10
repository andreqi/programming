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
#define MAXN 10010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int d[ MAXN ];
int l[ MAXN ];
int D;
int n ;
map< int , bool > cache[ MAXN ];

bool back( int d_lim, int id ){
	if( cache[ id ].count( d_lim ) ) return cache[ id ][ d_lim ];
	bool ans = false;
	if( d[ id ] + d_lim >= D ) return cache[ id ][ d_lim ] = true; 
	int j = id + 1 ;
	while( j < n and d[ id ] + d_lim >= d[ j ] ){
		int dis = min( d[ j ] - d[ id ] , l[ j ] ) ;
		if( back( dis , j ) ){
			ans = true;
			break;
		}
		j++;
	} 
	return cache[ id ][ d_lim ] = ans;
}

void solve(){
	cin >> n;
	rep( i , n ){ cin >> d[ i ] >> l [ i ] ;}
	cin >> D;
	rep( i , n ) cache[ i ].clear();
	bool ans = back( d[ 0 ] , 0 ); 
	if ( ans ) cout << "YES" << endl;
	else		cout << "NO" << endl;
}

int main(){
	int test;
	cin >> test;
	rep( i , test ){
		printf("Case #%d: " , i + 1 );
		solve();
	}
	return 0;
}

