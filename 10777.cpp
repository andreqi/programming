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

double x[ MAXN ];
double p[ MAXN ];

void solve(){
	int n = 0;
	scanf("%d" , &n );
	rep( i , n ){ scanf("%lf%lf" , x + i , p + i ); }
	double ans = 0;
	rep( i , n ) ans += ( fabs( x[ i ] ) * p[ i ] );
	double denom = 0 ; int posi = 0 ;
	rep( i , n ) denom += ( x[ i ] > 0 ) ? posi++ , p[ i ]: 0; 
	if( posi ) 	printf("%.2lf\n" , ans / denom );
	else		printf("God! Save me\n");
	return ;
}

int main(){
	int test = 0 ;
	scanf("%d" , &test);
	rep( tcase , test ){
		printf("Case %d: ", tcase + 1 );
		solve();
	}
	return 0;
}

