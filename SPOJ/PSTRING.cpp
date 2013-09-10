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
#define MAXN 10011
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXY = 1010, MAXX = 10010;
const int alpha = 'z' - 'a' + 1;

char pat[MAXY];
char txt[MAXX]; 
int dp[2][MAXY];
int com[MAXY][alpha+1];
int b[MAXY];
int n, m;

void kmppre(){
    int i = 0, j = -1;
    b[i] = j;
    while (i < m) {
        while (j >= 0 and pat[i] != pat[j] ) j = b[j];
        b[++i] = ++j;
    }
}

int jump(int j, char c){
    int &ans = com[j][c-'a'];
    if ( ans != -1 ) return ans;
    while( j >= 0 and c != pat[j] ) j = b[j];
    return ans = j + 1;
}
inline void mn(int & x, int r){ x = (x == -1 or x > r) ? r : x;}
int main(){
    pii cur;
    while ( scanf("%s%s", txt, pat) == 2 ){
        n = strlen(txt);
        m = strlen(pat);
        kmppre();
        memset( dp, -1, sizeof dp);
        memset( com, -1, sizeof com);
        dp[0][0] = 0;
        int min_delete = n, cost, nj;
        rep (i, n) rep(j, m) if( dp[i&1][j] != -1 ){
            cost = dp[i&1][j];   
            dp[i&1][j] = -1;
            mn(dp[1-i&1][j], cost+1);
            nj = jump(j,txt[i]);
            if( nj == m ) continue;
            mn(dp[1-i&1][nj], cost);
        }
        rep (i, m) if( dp[n&1][i] != -1 ){
            mn(min_delete, dp[n&1][i]);
        }
        printf("%d\n", min_delete);
    }
	return 0;
}

