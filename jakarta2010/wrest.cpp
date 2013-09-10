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
const int MAXN = two(15) + 1;
int k ;
int str[MAXN];
int win[MAXN][16];
pii f(int p, int pot) {

    if (pot == 0){
        win[p][pot] = p;
        return pii(str[p], p);
    }
    pii x = f(p, pot - 1);
    pii y = f(p + two(pot-1), pot - 1);
    pii a, b;
    if (x.fst >= y.fst) a = x, b = y;
    else  a = y, b = x;
    win[p][pot] = a.snd;
    return pii(min(str[a.snd], a.fst + k - b.fst), a.snd);
}
int order[100];
void rec(int id, int p, int pot) {
     if (pot == 0) return;
     int x = win[p][pot-1];
     if (x == id) {
         order[pot] = win[p + two(pot-1)][pot-1];
         rec(id, p, pot-1);
     } else {
         order[pot] = win[p][pot-1];
         rec(id, p + two(pot-1), pot-1);
     }
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        int n; scanf("%d", &n);
        scanf("%d", &k);
        rep (i, two(n)) scanf("%d", str + i);
        pii ans = f(0, n);
        printf("%d\n", ans.snd + 1);
        rec(ans.snd, 0, n);
        rep (i, n) printf("%d%c", order[i+1] + 1,((i+1) == n)? '\n' : ' ');
    }
	return 0;
}

