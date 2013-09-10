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
#define MAXN 120001
#define mod1 1000000009LL
#define mod2 1000000007LL
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int64 , int64 > pii;


string w[ MAXN ];
map< pii , bool > dic;
int n;
int64 lenv = 'z' - 'a' + 1231;
void read(){
	n = 0;
	while( cin >> w[ n ] ) n++ ;
}


int64 exp( int64 a , int64 b , int64 mod ){
	if( b == 1LL ) return a;
	int64 c = exp( a , b >> 1 , mod ) % mod ;
	return b & 1LL ?  ( ( c * c ) % mod * a ) % mod : ( c * c ) % mod ;  
}

pii hash( string & str ) {
	pii key = mp( 0 , 0 ); 
	int64 pot1 = 1LL , pot2 = 1LL ;
	rep( i , str.size() ){
		key.fst = ( key.fst +  pot1 * ( str[ i ] - 'a' + 1 ) + mod1 ) % mod1;  
		key.snd = ( key.snd +  pot2 * ( str[ i ] - 'a' + 1 ) + mod2 ) % mod2;  
		pot1 = ( pot1 * lenv ) % mod1 ;
		pot2 = ( pot2 * lenv ) % mod2 ;
	}
	return key;
}

int64 key_suff( int64 dn , int64 pot , int64 mod ){
	int64 ans = 0;
	dn %= mod;
	dn += mod;
	dn %= mod;
	ans = ( dn * exp( exp( lenv , pot , mod ) , mod - 2LL , mod ) ) % mod;
	return ans;
}
pii f[ MAXN ];
void solve(){
	sort( w , w + n );
	rep( i , n ) {
		dic[ hash( w[ i ] ) ] = 1;
	}
	rep( i , n ) {
		string & str = w[ i ];
		int len = str.size();
		int64 pot1 = 1LL , pot2 = 1LL;
		pii suff;
		rep( j , len ){
			f[ j ].fst = ( ( j ? f[ j - 1 ].fst : 0 ) +  pot1 *( str[ j ] - 'a' + 1 ) + mod1 ) % mod1;
			f[ j ].snd = ( ( j ? f[ j - 1 ].snd : 0 ) +  pot2 *( str[ j ] - 'a' + 1 ) + mod2 ) % mod2;
			pot1 = ( pot1 * lenv ) % mod1;
			pot2 = ( pot2 * lenv ) % mod2;
		}
		rep( j , len - 1 ){
			if( !dic.count( f[ j ] ) ) continue;
			suff.fst = key_suff( f[ len - 1 ].fst - f[ j ].fst , j + 1  , mod1 );
			suff.snd = key_suff( f[ len - 1 ].snd - f[ j ].snd , j + 1, mod2 );
			if( !dic.count( suff ) ) continue;
			cout << w[ i ] << endl;
			break;
		}
	}
}

int main(){
	read();
	solve();
	return 0;
}

