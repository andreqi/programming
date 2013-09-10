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

int main(){
	int test = 0 , n;
	cin >> test;
	while( test-- ){
		cin >> n;
		int ans = 0;
		int hay_dif_uno = 0;
		rep( i , n ){
			int mm ; cin >> mm;
			hay_dif_uno = hay_dif_uno or ( mm > 1 );
			ans ^= mm;
		}
		if( ans == 0 and hay_dif_uno ) cout << "Brother" << endl;
		else if ( ans == 1 and ! hay_dif_uno ) cout << "Brother" << endl;
		else						   cout << "John" << endl;
	} 
	return 0;
}

