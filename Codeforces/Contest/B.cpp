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

int64 nxt[100010];

int main(){
    int64 n, m;
    cin >> n >> m;
    rep (i, m) cin >> nxt[i];
    int64 cur = 0;
    rep (i, m) nxt[i]--;
    int64 ans = 0;
    rep (i, m) {
        ans += (nxt[i] - cur + n) % n;
        cur = nxt[i];
    }
    cout << ans << endl;
	return 0;
}

