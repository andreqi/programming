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

char str[50000];
int x[300];
int y[300];

inline void add(int * f, const char * s){
    int i = 0;
    while (s[i]) f[s[i++]]++;
}

int main(){
    int test, iter, child;
    scanf("%d", &test);
    while (test--){
        memset(x, 0, sizeof x);
        memset(y, 0, sizeof y);
        scanf("%s", str);
        add(x, str);
        scanf("%s", str);
        add(x, str);
        scanf("%d", &child);
        rep (i, child){
            scanf("%s", str);
            add(y, str);
        }
        bool can = true;
        rep (i, 300) if( x[i] < y[i] ) can = false;
        printf("%s\n", can?"YES":"NO");
    }
	return 0;
}

