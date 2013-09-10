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
#define MAXN 100010
#define MOD 1000000007
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int t , rank[ MAXN ] , bc[ 300 ];
int sa[ MAXN ] ,lcp[ MAXN ];

int cmp( int i , int j ) { return rank[ i + t ] < rank[ j + t ] ; } 

void build_suffix( char * str , int n ){
	memset( bc , 0 , sizeof bc );
	rep( i , n ) bc[ str[ i ] ]++;
	repn( i , 1 , 256 ) bc[ i ] += bc[ i - 1 ];
	rep( i , n ) sa[ bc[ str[ i ] ]-- ] = i;
	rep( i , n ) rank[ i ] = bc[ str[ i ] ]; 
	for( t = 1 ; t < n ; t <<= 1 ){
		for( int i = 0 , j = 0 ; j < n ; i = j++ ){
			while( j < n and rank[ j ] == rank[ i ] ) j++;
			if( j - i == 1 ) continue;
			int * begin = sa + i , * end = sa + j;
			sort( begin , end , cmp );
			int n_id = i, fst = rank[ *begin + t ] , cur;
			for( ; begin < end ; rank[ *begin++ ] = n_id ){
				if( ( ( cur = rank[ *begin + t ] ) == fst ) or 
					i <= fst and cur < j ) {}
				else	fst = cur , n_id = begin - sa;
			}
		}
	}
	rep( i , n ) cout << sa[ i ] << " " << &str[ sa[ i ] ] << endl;
}

void lcp_build( char * str,  int n ){
	int k = 0 ;
	rep( i , n ) if( rank[ i ] ){
		int j = sa[ rank[ i ] - 1 ];
		while( str[ j + k ] == str[ i + k ] ) k++;
		lcp[ rank[ i ] - 1 ] = k;
		if( k ) k--;
	}
	lcp[ n - 1 ] = 0;
}

int solve( char * str ){
	int ans = 0;
	int n = strlen( str );
	str[ n ] = 0;
	build_suffix( str , n + 1 );
	lcp_build( str , n + 1 );
	rep( i , n ) if( sa[ i ] ){
		
	}
	return ans;
}

char str[ MAXN ];
int main(){
	while( scanf("%s\n" , str ) == 1 ){
		printf("%d\n" , solve( &str[ 0 ] ) );
	}
	return 0;
}

