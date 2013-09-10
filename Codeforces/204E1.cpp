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
#define MAXN 300000
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

// suffix array O( n lg n )
int rank[ MAXN ] , sa[ MAXN ];
int lcp[ MAXN ] , str[ MAXN ] ;
int bc[ MAXN ] , t;
char buff[ MAXN ];

int cmp( int i , int j ) { return rank[ i + t ] < rank[ j + t ] ;}

char to_char( int s , int len ){
	int top = len - ( 'z' - 'a' + 1 );
	if( s < top ) return '$';
	return s - top + 'a';
}

void build_suffix( int * str , int ABC_len , int n ){
	rep( i , ABC_len ) bc[ i ] = 0;
	rep( i , n ) bc[ str[ i ] ]++;
	repn( i , 1 , ABC_len ) bc[ i ] += bc[ i - 1 ];
	rep( i , n ) sa[ -- bc[ str[ i ] ] ] = i;
	rep( i , n ) rank[ i ] = bc[ str[ i ] ];

	for( t = 1 ; t < n ; t <<= 1 ){
		for( int i = 0 , j = 0 ; j < n ; i = j++ ){
			while( j < n and rank[ sa[ i ] ] == rank[ sa[ j ] ] ) j++;
			if( j - i == 1 ) continue;
			int * ini = sa + i , * fin = sa + j ;
			sort( ini, fin , cmp );
			int pk , pri = rank[ *ini + t ] , num = i;
			for( ; ini < fin ; rank[ *ini++ ] = num ){
				pk = rank[ * ini + t ];
				if( pk == pri or ( i <= pri and pk < j ) ){}
				else pri = pk , num = ini - sa;
			}
		}
	}
	


	int k = 0;
	rep( i , n ) if ( rank[ i ] ){
		int j = sa[ rank[ i ] - 1 ];
		while( str[ i + k ] == str[ j + k ] ) k++;
		lcp[ rank[ i ] - 1 ] = k;
		if ( k ) k--;
	}

	lcp[ n - 1 ] = 0;
	/*
	rep( i , n ){
		int j;
		cout << i << " " << lcp[ i ] << " " ;
		for( j = 0 ; j < n ; j ++ ){
		if( to_char( str[ sa[ i ] + j ] , ABC_len ) == '$'  ) { cout << " " ; break; }
		else cout << to_char( str[ sa[ i ] + j ] , ABC_len) ;
		}
		cout << str[ sa[ i ] + j ] ;
		cout << endl;
	} */
}

// rmq O( n lg n )
int dp[ MAXN ][ 20 ];
void build_lca( int * arr , int n ){
	rep( i , n ) dp[ i ][ 0 ] = arr[ i ];
	for( int i = 1 , sz = 1 ; sz <= n ; i++ , sz *= 2 )
		rep( j , n - sz )
			dp[ j ][ i ] = min( dp[ j ][ i - 1 ] , dp[ j + sz ][ i - 1 ] );
}
// query O( lg n )
int query( int i , int j , int n ){
	if( i == j ) return n - j;
	j--;
	int p = 0 , len = j - i + 1;
	while( ( 1 << ( p + 1 ) ) <= len ) p++; 
	int fixed = 1 << p;
	int ans = min( dp[ i ][ p ] , dp[ j - fixed + 1 ][ p ] ); 
	return ans;
}

// sweep line O( n )
int R[ MAXN ];
int freq[ MAXN ];
void sweep_line( int * id ,int * sa , int n , int k  ){
	int i = 0, j = 0;
	int len = 0;
	rep( i , n ) freq[ i ] = 0;
	rep( i , n ) R[ i ] = 1 << 28;
	while( j < n ){
		while( j < n and len < k ){
			len += freq[ id[ sa[ j ] ] ] == 0;
			freq[ id[ sa[ j++ ] ] ]++;
		}
		while( i < j and len == k ){
			R[ i ] = j - 1;
			freq[ id[ sa[ i ] ] ]--;
			len -= freq[ id[ sa[ i++ ] ] ] == 0;
		}
	}
}

bool maximal_k( int n , int * str , int id , int len ){
	if( n == 0 ) return true;
	int l = 0 , h = id;
	while( l < h ){
		int mid = ( l + h ) / 2;
		if( query( mid , id , len ) >= n )	h = mid;
		else						l = mid + 1;
	}
	int left = l;
	l = id , h = len - 1;
	while ( l < h ) {
		int mid = ( l + h + 1 ) / 2;
		if( query( id , mid , len ) >= n )	l = mid;
		else						h = mid - 1;
	}
	int rigth = l;
	return R[ left ] <= rigth;
}

// solver O( n * lg ^ 2 n )
int64 ans[ MAXN ];
int solve( int *id , int * len , int * str , int n , int ABC_len , int k ){
	rep( i , n ) ans[ i ] = 0;
	build_suffix( str , ABC_len , n );
	build_lca( lcp , n );
	sweep_line( id , sa , n , k ); 
	rep( i , n ) if( len[ sa[ i ] ] ) {
		int lo = 0 , hi = len[ sa[ i ] ];
		int * suffix = & str[ sa[ i ] ];
		while( lo < hi ){
			int mid = ( lo + hi + 1 ) / 2;
			if( !maximal_k( mid , suffix , i , n  ) )	hi = mid - 1;	
			else					lo = mid;
		}
		ans[ id[ sa[ i ] ] ] += lo;
	}
	
	return 0;
}

pii read( int * id , int * len , int * str , int &kth , int &xy ){

	ios::sync_with_stdio( false );
	int words , k = 0;
	if( !( cin >> words ) ) return pii( -1 , -1 );
	cin >> kth;
	xy = words;
	int ABC_len = ( 'z' - 'a' + 2 + words );
	for( int i = 0 ; i < words ; i++ , k++ ){
		cin >> buff;
		int b_len = strlen( buff );
		for( int j = 0 ; buff[ j ] ; j++ , k++ ){
			str[ k ] = (int) ( buff[ j ] - 'a' ) + words + 1;
			id[ k ] = i;
			len[ k ] = b_len - j;
		}
		str[ k ] = i ; 
		id[ k ] = i;
		len[ k ] = 0;
	}
	/*
	rep( i , k ){
		char c = ( int )( str[ i ] - words - 1) + 'a';
		if( str[ i ] < words + 1 ) cout << ('$') ;
		else cout << c ;
	}
	cout << endl; */
	return pii( ABC_len , k );
}

int id[ MAXN ] , len[ MAXN ];
 
int main(){
	int k , n ;
	while( true ){
		pii x = read( id , len , str , k  , n);
		if( x.snd == -1 ) break;
		solve( id , len , str , x.snd , x.fst , k );
		cout << ans[ 0 ];
		repn( i , 1, n) cout << " " << ans[ i ] ; 
		cout << endl;
	}
	return 0;
}


