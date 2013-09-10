#include <cstdio>
#include <iostream>
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
int coins[ 50 ];
int knapsack[ 300 ];

int main(){
	int test;
	scanf( "%d\n" , &test );
	while( test -- ){
		int nr , len = 0 ; char c; 
		while( scanf("%d%c", &nr , &c ) == 2 and c == ' ' )
			coins[ len++ ] = nr;
		coins[ len++ ] = nr;
		int sum = 0;
		rep( i , len ) sum += coins[ i ];
		memset( knapsack , 0 , sizeof knapsack );
		knapsack[ 0 ] = 1;
		rep( i , len )	for( int j = sum ; j >= coins[ i ] ; j -- ){
			knapsack[ j ] |= knapsack[ j - coins[ i ] ];
		}
		if( sum % 2 == 0 and knapsack[ sum / 2 ] )
			printf( "YES\n" );
		else
			printf( "NO\n" );
	}
	return 0;
}

