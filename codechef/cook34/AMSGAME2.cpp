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

int64 dp[61][10010];
int data[61];
int64 f(int idx, int gcd) {
    if (idx == 0) return gcd == 1;
    int64 & ans = dp[idx][gcd];
    if (ans != -1LL) return ans;
    ans = f(idx - 1, gcd);
    ans += f(idx - 1, __gcd(gcd, data[idx-1]));
    return ans;
}
int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        int n;
        scanf("%d", &n);
        rep (i, n) scanf("%d", data + i);
        int top = *max_element(data, data + n);
        rep (i, n + 1) rep(j , top + 1) dp[i][j] = -1LL;
        cout << f(n, 0) << endl;
    }
	return 0;
}

