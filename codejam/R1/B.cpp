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
#define MAXN 200
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int sum[ MAXN ];
pii f[ MAXN ];
int s_f[] = {3,2,4};
int n_f[] = {0,2,1};

int make_sum( int a , int b ){ return ( a + b ) / 3 ; }
void solve( int tcase ){
	int N , S , P;
	scanf( "%d%d%d" , &N , &S , &P );
	rep( i , N ) scanf( "%d" , sum + i );
	rep( i , N ){
		int id_sur = sum[ i ] % 3;
		f[ i ] = pii( make_sum( sum[ i ] , s_f[ id_sur ] ) ,
					  make_sum( sum[ i ] , n_f[ id_sur ] ) );
		if( sum[ i ] < 2 ) f[ i ].fst = -1;
	}
	sort( f , f + N );
	int ans = 0;
	for( int i = N -1 ; i >= 0 ; i -- ){ if( f[ i ].snd >= P ) ans++; else if( f[ i ].fst >= P and S ) { S-- ; ans++ ; } }
	printf("Case #%d: %d\n" , tcase , ans );
}

int main(){
	int test;
	scanf( "%d" , &test );
	rep( casos , test ){
		solve( casos + 1 );
	}
	return 0;
}

