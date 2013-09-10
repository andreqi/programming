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
const int MAXM = 1010, MAXN = 100100;
int bt[MAXM];

void search (char *txt, char *pat, int *save) {
    int i = 0, j = -1;
    bt[i] = j;
    while (pat[i]) {
        while (j >= 0 and pat[i] != pat[j] ) j = bt[j];
        bt[++i] = ++j;
    }
    i = 0, j = 0;
    save[i] = j;
    while (txt[i]) {
        while (j >= 0 and txt[i] != pat[j] ) j = bt[j];
        ++i , ++j;
        save[i] = max(j, save[i-1]);
        if ( !pat[j]  ){
            j = bt[j];
        }
   }
}

char str[MAXN], rstr[MAXN];
char pat[MAXM], rpat[MAXM];
int  fwr[MAXN], rev[MAXN];
int main(){
    scanf("%s", str);
    int len = strlen(str);
    rep (i, len) rstr[len-1-i] = str[i];
    rstr[len] = 0;
    int q = 0, ans = 0;
    scanf("%d", &q);
    while (q--) {
        scanf("%s", pat);
        int plen = strlen(pat);
        if (plen == 1) continue;
        rpat[plen] = 0;
        rep (i, plen) rpat[plen-1-i] = pat[i];
        //printf("%s\n", rstr);
        //printf("%s\n", rpat);
        search(str, pat, fwr);
        search(rstr, rpat, rev);
        int found = 0;
        //rep (i, len+1) cout << fwr[i]; cout << endl;
        //rep (i, len+1) cout << rev[i]; cout << endl;
        rep (i, len + 1) if (fwr[i] + rev[len-i] >= plen) {
            found = 1;
            break;
        } 
        //cout << found << endl;
        ans += found;
    }
    printf("%d\n", ans);
	return 0;
}

