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

int border[100];
int kmp ( string s ){
    rep (i, s.size()) cout << " " << s[i];
    cout << endl;
    int i = 0 , j = -1;
    border[0] = -1;
    while( i < s.size() ){
        while ( j >= 0 and ( s[i] != s[j] ) ) j = border[j]; 
        i++; j++;
        border[i] = j;
    }
    repn (i ,1 , s.size()+1) cout << " " << border[i]; 
    cout << endl;
    return 0;
}

int main(){
    kmp ("seventy seven");
    kmp ("abracadabra");
	return 0;
}

