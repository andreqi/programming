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

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        char txt[5];
        vector <pii> cards;
        rep (i, 52) cards.push_back(pii(i,0));
        rep (i, 26) {
            scanf("%s", txt);
            int number = toNum(txt);
            cards[number].snd = 1;
        }
        int cur = 0;
        int ans = 0;
        rep (i, 52) {
            pii x = cards[51 - i];
            if (x.snd == 1) cur++;
            else {
                if (cur) {
                    cur--;
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
	return 0;
}

