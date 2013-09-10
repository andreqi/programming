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
int a[100];
double da[100];
int main(){
    int n;
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i );
    rep (i, n) da[i] = a[i];
    int sum = 0;
    rep (i, n) sum += a[i];
    int base = 0;
    rep (i, n) {
        if ( a[i] * (n + 1) - sum <= 0) continue;
        base += a[i] * (n + 1) - sum;
    }
    rep (i, n) {
        if (i) putchar(' ');
        if ( a[i] * (n + 1) - sum <= 0 ) { printf("0"); } 
        else {
            printf("%d", ((((a[i] * ( n + 1 ) - sum) * 100) / base) ) );
        }
    }
    printf("\n");
	return 0;
}

