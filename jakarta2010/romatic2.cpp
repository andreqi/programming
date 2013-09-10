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

string dig = "23456789TJQKA";
string hnd = "DCHS";

int toNum(const char * str ) {
    int x = dig.find(str[0]);
    int y = hnd.find(str[1]);
    return x * 4 + y;
}

char buff[4];
int usd[100];

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        clr(usd, 0);
        rep (i, 26) {
            scanf("%s", buff);
            usd[toNum(buff)] = 1;
        }
        int ans = 0, g = 0;
        rep(i, 52) {
            int j = 51 - i;
            if (usd[j]) g++;
            else {
                if(g){
                    ans++;
                    g--;
                }
            }
        }
        printf("%d\n", ans);
    }
	return 0;
}

