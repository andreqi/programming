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

string ejm   = "ejpmysljylckdkxveddknmcrejsicpdrysirbcpcypcrtcsradkhwyfrepkymveddknkmkrkcddekrkdeoyakwaejtysrreujdrlkgcjv";
string trans = "ourlanguageisimpossibletounderstandtherearetwentysixfactorialpossibilitiessoitisokayifyouwanttojustgiveup";
map< char , char > to;

int main(){
	int test = 0;
	rep( i , ejm.size() ) to[ ejm[ i ] ] = trans[ i ];	
	cin >> test;
	to[ ' ' ] = ' ';
	to[ 'q' ] = 'z';
	to[ 'z' ] = 'q';
	getline( cin , ejm );
	rep( casos , test ) {
		cout << "Case #" << casos + 1 << ": "; 
		getline( cin , ejm );
		rep( i , ejm.size() ) cout << to[ ejm[ i ] ]; 
		cout << endl;
	}
	return 0;
}

