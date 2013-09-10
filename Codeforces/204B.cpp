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

const int oo = 1 << 28;

map< int , int > times;
map< int , int > can_flip;
set< int > color;

int main(){
	int n ;
	cin >> n;
	rep( i , n ){
		int u , v; 
		cin >> u >> v;
		color.insert( u );
		color.insert( v );
		times[ u ]++;
		if( u == v ) continue;
		can_flip[ v ]++;
	}
	int ans = -1;
	int target = ( n + 1 ) / 2;
	int cnt;
	for( int cur = *color.begin() ; not color.empty() and ans != 0 ; color.erase( color.begin() ) 
		 , cur = * color.begin() ){
		if( ( cnt = times[ cur ] ) >= target ){
			ans = 0;
			break;
		}
		int flip_times = target - cnt; 
		if( can_flip[ cur ] < flip_times ) continue;
		if( ans == -1 or ans > flip_times ) ans = flip_times;
	}

	cout << ans  << endl;
	return 0;
}

