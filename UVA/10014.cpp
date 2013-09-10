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
#define MAXN 3010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

double c[ MAXN ];
double a[ MAXN ], b[ MAXN ], r[ MAXN ];
// 2 ai-1 + 2 ci-1 - ai-2 = ai


int main(){
	int test;
	scanf("%d" ,& test );
	while( test-- ){
		int n; scanf("%d", &n );
		double an1 , a0 ;
		scanf("%lf%lf" , &a0 , &an1 );
		rep( i , n ) scanf("%lf" , c + i + 1 );
		if( n == 1 ){
			printf("%.2lf\n" , ( an1 + a0 ) / 2. - c[ 1 ] );
		}
		else{
			a[ 0 ] = 1, b[ 0 ] = 0 , r[ 0 ] = 0; 
			a[ 1 ] = 0, b[ 1 ] = 1 , r[ 1 ] = 0; 
			repn( i , 2, n + 1 ){
				a[ i ] = 2. * a[ i - 1 ] - a[ i - 2 ]; 
				b[ i ] = 2. * b[ i - 1 ] - b[ i - 2 ]; 
				r[ i ] = 2. * r[ i - 1 ] - r[ i - 2 ] + 2. * c[ i - 1 ]; 
			} 
			double sum = 0;
			rep( i , n ) sum += c[ i + 1 ];
			double ans = an1 + a0 - 2. * sum - a0 * a[ n ] - r[ n ];
			ans /= ( b[ n ] + 1. );
			printf("%.2lf\n" , ans );
		}
		if( test ) printf("\n");
	}
	return 0;
}

