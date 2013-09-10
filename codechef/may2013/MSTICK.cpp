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

const int MAXN = 100010;
const int LGMAXN = 20;

int n;
int64 a[MAXN];
int64 mx[LGMAXN][MAXN]; //max
int64 mn[LGMAXN][MAXN]; //min

void prep(){
    rep (i, n) mx[0][i] = a[i];
    for (int i = 1; n >= (1 << i) ; i++ ) {
        for (int j = 0; (j + (1<<i)) <= n; j++) {
            mx[i][j] = max(mx[i-1][j], mx[i-1][j+(1<<(i-1))]);
        }
    }
    rep (i, n) mn[0][i] = a[i];
    for (int i = 1; n >= (1 << i) ; i++ ) {
        for (int j = 0; (j + (1<<i)) <= n; j++) {
            mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<(i-1))]);
        }
    }
}

int get_max(int i, int j){
    int len = j - i + 1;
    if( len == 1 ) return a[i];
    int pot = 0; 
    while( (1 << (pot+1)) < len ) pot++;
    return max(mx[pot][i],mx[pot][j-(1<<pot)+1]);
}

int get_min(int i, int j){
    int len = j - i + 1;
    if( len == 1 ) return a[i];
    int pot = 0; 
    while( (1 << (pot+1)) < len ) pot++;
    return min(mn[pot][i],mn[pot][j-(1<<pot)+1]);
}


int main(){
    scanf("%d", &n);
    rep (i, n) scanf("%lld", a+i);
    prep();
    int q;
    scanf("%d", &q);
    while (q--){
        int i, j;
        scanf("%d%d",&i ,&j);
        int64 mini = get_min(i, j);
        int64 maxi = get_max(i, j);
        int64 ans = mini + maxi ;
        if ( i > 0 ) ans = max( ans , 2LL*(mini + get_max(0,i-1)));
        if ( j+1 < n ) ans = max( ans , 2LL*(mini + get_max(j+1,n-1)));
        int64 div = ans / 2;
        printf("%lld.", div);
        printf("%s\n", ans % 2LL ? "5":"0");
    }
	return 0;
}

