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

int dx[110], idx[110];
void add(int i, int j, int arr[], int p) {
    repn (k, i, j) arr[k] += p;
}
int main(){
    int n , p;
    scanf("%d", &n);
    clr(dx, 0); clr(idx, 0);
    rep (i, n) rep (j, n) {
        scanf("%d", &p);
        if (i == j) continue;
        if (i < j)  add(i, j, dx, p); 
        if (i > j)  add(j, i, idx, p); 
    }
    int ans = max(*max_element(dx, dx + n), *max_element(idx, idx + n));
    int div = (ans + 35) / 36;
    printf("%d\n", div);
	return 0;
}

