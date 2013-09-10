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

struct my_struct{
	int operator [] ( int a ){
		return a * 10 ;
	}
	int operator () ( int b ){ return b; }
};

string a , b;

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	cin >> a >> b;
	my_struct my;
	cout << my[ 100 ] << endl;
	cout << my( 10 ) << endl;
	double ans = 0;
	double div = 0;
	double fa[ 256 ] = {} , fb[ 256 ] = {};
	rep( i , n ) {
		div += ( (double)( i + 1.0 ) * ( i + 1.0 ) );
		fb[ b[ i ] ] += ( i + 1 );
		ans += fb[ a[ i ] ] * ( n - i );
		ans += fa[ b[ i ] ] * ( n - i );
		fa[ a[ i ] ] += ( i + 1 );
	}
	ans /= div ;
	cout.precision(9);
	cout << ans << endl;
	return 0;
}

