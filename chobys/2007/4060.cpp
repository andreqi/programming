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
#define MAXN 1000001LL
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int dv[ MAXN ];
int buff[ 4 ];
int len;

void solve( int n ){
	int ans = 0;
	rep( i , n - 2 ) if( ( dv[ i + 2 ] - dv[ i ] ) <= 25LL ) { 
		int e = i + 2;
		while( e < n and ( dv[ e ] - dv[ i ] ) <= 25LL ) e++; 
		int a = i;
			repn( b , a + 1 , e - 1 )
				repn( c , b + 1 , e ) {
					buff[ 0 ] = dv[ a ] , buff[ 1 ] = dv[ b ] , buff[ 2 ] = dv[ c ];
					rep( j , 3 ) printf("%d%c" , buff[ j ] , j == 2 ? '\n' : ' ' );
					ans++;
				}
	}
	if( ans == 0 ){
		printf("Such bells don't exist\n");
	} 
}

int main(){
	int64 n;
	int tcase = 1;
	while( scanf("%lld" , &n ) == 1 and n ){
		len = 0;
		for( int64 i = 1LL ; i <= n and i <= 1000000LL ; i++ ){
			if( n % i ) continue;
			int64 a = i ; // a * b = n
			dv[ len++ ] = (int)a;	
		} 
		printf("Scenario %d:\n" , tcase++ );
		if( len <= 2 )
			printf("Such bells don't exist\n");	
		else
			solve( len );
		printf("\n");
	}
	return 0;
}

