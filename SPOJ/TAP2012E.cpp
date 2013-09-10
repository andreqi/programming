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

#define MAXN 1010
const int oo = 1 << 28;
int data[ MAXN ];
int dp[ MAXN ] , n  , h;
int sum( int i , int j ){ return i == 0 ? data[ j ] : data[ j ] - data[ i - 1 ] ; }
int range( int i , int j ) { return sum( i - 1 , j - 2 ); }
int valid( int sum , int sz ){
	return sum <= ( h * ( sz - 1 ) );
}
int moves( int id ){
	int & ans = dp[ id ];
	if( ans != -1 ) return ans;
	ans = valid( range( id , n ) , n - id + 1 ) ? n - id - 1 : oo ;
	repn( i , id + 1 , n ){
		int a = range( id , i ) , b = range( i , n );
		int lena = i - id + 1 , lenb = n - i  + 1 ; 
		if( valid( a , lena ) and valid ( b , lenb ) ){
			ans = min( lena - 2 + moves( i ) , ans );
		}
	}
	return ans;
}
int main(){
	while( scanf("%d%d" , &n , & h ) and n != -1 ){
		rep( i , n - 1 ) scanf("%d" , data + i );	
		repn( i , 1 , n - 1 ) data[ i ] += data[ i - 1 ];
		memset( dp , -1 , sizeof dp );
		printf("%d\n"  , moves( 1 ) >= oo ? -1 : moves( 1 ) );
	}
	return 0;
}

