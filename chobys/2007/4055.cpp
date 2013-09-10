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

struct frac{
	int64 n , d;
	frac(){}
	frac( int64 a , int64 b ){ n = a , d = b; }
	void norm(){
		int64 g = __gcd( n , d );
		n /= g , d /= g ;
	}
	bool operator < ( frac c ){
		norm();
		c.norm();
		return n * c.d < c.n * d;
	}
	bool operator == ( frac c ){
		norm() , c.norm();
		return n == c.n and c.d == d;
	}
};
int main(){
	int s , b, tcase = 1;
	while( scanf("%d%d" ,&b , &s ) == 2 and s + b ){
		frac c( s , b );
		printf("Case %d: ", tcase++);
		if( b == 1 ) 		printf(":-\\\n");
		else if( s >= b ) 	printf(":-|\n");
		else{
			if( c == frac( s - 1 , b - 1 ) ) printf(":-|\n");
			else{
				printf(":-%c\n", c < frac( s - 1 , b - 1 ) ? ')': '(' );
			}
		}
	}
	return 0;
}

