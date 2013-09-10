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
#define MAXN 50010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

char str[ MAXN ];
int n;

int id( int i , int j ){
	int ans = min( i , n - i - 1 );
	ans = min( min( j , ans ) , n - 1 - j );
	return ans;
}

void solve(){
	int r1 , c1 , r2 , c2;
	scanf("%d%d%d%d\n" , &r1 , &c1 , &r2 , &c2 );
	repn( i , r1 - 1, r2 ){
		repn( j , c1 - 1 , c2  ){
			putchar( str[ id( i , j  ) ] ) ;
		}
		putchar( 10 );
	}
}

int main(){
	int t;
	scanf("%d\n" , &t );
	rep( tcase , t ) {
		printf("Square %d:\n", tcase + 1  );
		scanf("%s\n" , str );
		int q; scanf("%d\n" ,&q );
		n = strlen( str );
		n *= 2; n--;
		rep( tquery , q ){
			printf("Query %d:\n" , tquery + 1 );
			solve();
		}
		putchar( 10 );
	}
	return 0;
}

