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


int64 f( int64 n , int64 x ){ return n * x + ( ( n - 1LL ) * n ) / 2LL ;}

int main(){
	int64 x , d;
	while( scanf("%lld %lld" , & x , & d ) == 2 ){
		int64 lo = 1 , hi = 100000000 , mid;
		while( lo < hi ){
			mid = ( lo + hi ) / 2LL;
			if( f( mid , x ) < d )	lo = mid + 1; 
			else				  	hi = mid;
		}
		printf("%lld\n" , lo - 1 + x );
	}
	return 0;
}

