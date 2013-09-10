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
char o[MAXN];
char r[MAXN];
int b[MAXN];

int main(){
    while ( scanf("%s", o) == 1 ) { 
        int len = strlen(o);
        rep (i, len) r[i] = o[len - i - 1];
        r[len] = '\0';
        int i = 0, j = -1;
        b[i] = j;
        while( i < len ) {
            while ( j >= 0 and r[i] != r[j] )
                j = b[j];
            b[++i] = ++j;
        }
        i=0; j = 0;
        while( i < len ) {
            while ( j >= 0 and o[i] != r[j] )
                j = b[j];
            i++; j++;
        }
        printf("%s", o);
        while ( r[j] )  putchar(r[j++]);
        printf("\n");
    }
	return 0;
}

