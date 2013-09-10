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
string actg = "ACTG";
const int CHARSET = 4;
struct AhoCorasick {
    static const int NODES = 20 * 60;
    int trie[NODES][CHARSET];
    int tag[NODES];
    int fail[NODES];
    int end;
    void add(int * str, int len) {
        int p = 0;
        while (len--) {
            if ( trie[p][*str] == -1 ){
                clr(trie[end], -1);
                tag[end] = 0;
                trie[p][*str] = end++;
            }
            p = trie[p][*str++];
        }
        tag[p] = 1;
    }
    void init() {
        end = 1;
        clr(trie[0], -1);
        tag[0] = 0;
    }
    void build() {
        queue<int> bfs;
        rep (i, CHARSET) {
            if (trie[0][i] == -1) {
                trie[0][i] = 0;
            } else {
                bfs.push(trie[0][i]);
                fail[trie[0][i]] = 0;
            }
        }
        while (not bfs.empty() ){
            int p = bfs.front();
            bfs.pop();
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                if ( trie[p][i] == -1 ){
                    trie[p][i] = trie[fail[p]][i];
                } else {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    bfs.push(trie[p][i]);
                }
            }
        }
    }
} ac;
const int MAXN = 1010;
char cpat[MAXN];
char buff[MAXN];
int pat[MAXN];
int dp[MAXN][20 * 51];
void mini(int & n, int x){
    if (x < 0) return;
    if (n < 0) n = x;
    else       n = min(n,x);
}
int f(int idx, int p) {
    if (pat[idx] == -1) return 0;
    int & ans = dp[idx][p];
    if (ans != -1) return ans;
    int nxt = ac.trie[p][pat[idx]];
    ans = -2;
    if (ac.tag[nxt] == 0) mini(ans, f(idx+1,nxt)); 
    rep (i, CHARSET) {
        nxt = ac.trie[p][i];
        if (ac.tag[nxt]) continue;
        mini(ans, f(idx+1,nxt) + 1);
    }
    return ans;
}

int main(){
    int n , tcase = 1;
    while ( scanf("%d", &n) == 1 and n) {
        ac.init();
        rep (i, n){
            scanf("%s", buff);
            int idx;
            for (idx = 0; buff[idx]; idx++) pat[idx] = actg.find(buff[idx]);
            ac.add(pat, idx);
        }
        ac.build();
        scanf("%s", cpat);       
        int len = 0;
        for (len=0; cpat[len]; len++) pat[len] = actg.find(cpat[len]);
        pat[len] = -1;
        clr(dp, -1);
        printf("Case %d: %d\n", tcase++, (len = f(0,0)) < 0? -1: len);  
    }
	return 0;
}

