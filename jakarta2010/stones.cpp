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
#define clr(x, y) memset(x, (y), sizeof x)
#define two(x) (1<<(x))
#define twol(x) (1LL<<(x))
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

set <int64> pot;
int64 grundy( int64 x ){
    if ( x % 2LL == 0) return x / 2LL;
    if (pot.count(x+1LL)) return 0LL;
    return grundy(x - (x + 1LL)/2LL);
}

int main(){
    int test;
    cin >> test;
    rep (i, 63)  pot.insert(twol(i));
    while (test--) {
        int n;
        int64  ans = 0;
        cin >> n;
        rep (i, n) {
            int64 x ;
            cin >> x;
            ans ^= grundy(x);
        }
        cout << (ans == 0? "NO" : "YES") << endl;
    }
	return 0;
}

