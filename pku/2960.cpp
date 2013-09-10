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

int g[ 10100 ];
int coins[ 100 ];
int n;
bool read(){
	cin >> n;
	if( n == 0 ) return false;
	rep( i , n ) cin >> coins[ i ] ;
	sort( coins , coins  + n );
	return true;
}

int grundy( int nim ){
	if( g[ nim ] != -1 ) return g[ nim ];
	int usd[ 10100 ];
	memset( usd , 0 , sizeof usd );
	for( int i = 0 ; i < n and coins[ i ] <= nim ; i ++ ){
		usd[ grundy( nim - coins[ i ] ) ] = 1;
	}  
	int j = 0;
	while( usd[ j ] ) j ++;
	return g[ nim ] = j;
}

void solve(){
	memset( g , -1 , sizeof g );
	rep( i , 10100 ) g[ i ] = grundy( i );
	int test;
	string w = "WL";
	cin >> test;
	rep( i , test ){
		int len ; cin >> len;
		int t_ans = 0;
		rep( j , len ){
			int c ; cin >> c;
			t_ans ^= g[ c ];
		}
		cout << w[ t_ans == 0 ];
	}
	cout << endl;
}

int main(){
	while( read() ){
		solve();
	}
	return 0;
}

