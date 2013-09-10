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
typedef vector< int > vi;

map< vi , bool > cache; 

bool back( vi frq , int sum ){
	if( cache.count( frq ) ) return cache[ frq ];
	rep( i , 6 ) if( frq[ i ] < 4 ) { 
		frq[ i ]++;
		int nxt_sum = sum + i + 1;
		if( nxt_sum > 31 ) continue;
		int win = back( frq , sum + i + 1 );
		frq[ i ]--;
		if( win == false ) return cache[ frq ] = true;
	}
	return cache[ frq ] = false;
}

char winner( string str ){
	int len = str.size();
	int player = len % 2 , sum = 0;
	vi freq( 6 , 0 );
	rep( i , len ) freq[ str[ i ] - '1' ]++ ;
	rep( i , 6 ) sum += freq[ i ] * ( 1 + i );
	return back( freq , sum ) ? 'A' + player : 'B' - player; 
}

int main(){
	string str;
	while( cin >> str ){
		cache.clear();
		cout << str << " " << winner( str ) << endl;
	}
	return 0;
}

