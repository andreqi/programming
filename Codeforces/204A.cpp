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

int64 p10[ 20 ];
int64 x[ 20 ] , sx[ 20 ];

void preprocess(){
	p10[ 0 ] = 1;
	rep( i ,  19 ) if( i ) p10[ i ] = p10[ i - 1 ] * 10LL;
	x[ 0 ] = 0 , x[ 1 ] = 9 , x[ 2 ] = 9;
	repn( i , 3 , 19 ) x[ i ] = 9LL * p10[ i - 2 ] ; 
	repn( i , 1 , 19 ) sx[ i ] += sx[ i - 1 ] + x[ i ];
}

int64 toint( string s ){
	istringstream is( s );
	int64 ans;
	is >> ans;
	return ans ;
}

int64 solve( int64 r ){ 
	if( r == 0 ) return 0;
	if( r < 10 ) return r ;
	if( r < 100 ) return 9 + ( r / 10 - ( ( r / 10 ) > r % 10 ) );
	ostringstream os;
	os << r;
	string str_r = os.str();
	int n = os.str().size();
	int64 ans = sx[ n - 1 ];
	int64 dig = str_r[ 0 ] - '0';
	ans += ( dig - 1LL ) * p10[ n - 2 ];
	ans +=  toint( str_r.substr( 1 , n - 2 ) ) + 1 - ( r % 10 < dig );
	return ans;
}

int main(){
	int64 a , b ;
	preprocess();
	cin >> a >> b;
	cout << solve( b ) - solve( a - 1 ) << endl;
	return 0;
}

