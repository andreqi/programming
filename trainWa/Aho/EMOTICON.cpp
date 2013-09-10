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

struct Aho {
    static const int CHARSET = 256;
    static const int NODES = 15 * 110;
    int end;
    int trie[NODES][CHARSET];
    int tag[NODES];
    int fail[NODES];
    int que[NODES];
    void init() {
        end = 1;
        clr(trie[0], -1);
        tag[0] = 0;
    }
    void add(char *str) {
        int p = 0;
        while (*str) {
            if (trie[p][*str] < 0 ) {
                clr(trie[end], -1);
                tag[end] = 0;
                trie[p][*str] = end++;
            }
            p = trie[p][*str++];
        }
        tag[p] = 1;
    }
    void build() {
        int h = 0, t = 0;
        rep (i, CHARSET) {
            if (trie[0][i] < 0) {
                trie[0][i] = 0;
            } else {
                fail[trie[0][i]] = 0;
                que[h++] = trie[0][i];
            }
        }
        while (t < h){
            int p = que[t++];
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                if (trie[p][i]<0) {
                    trie[p][i] = trie[fail[p]][i];
                } else {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    que[h++] = trie[p][i];
                }
            }
        }
    }
} ac;

char buff[100];
map<int, int> dp[100];
int f(int idx, int p) {
    if (!buff[idx]) return 0;
    if (dp[idx].count(p)) return dp[idx][p];
    int nxt = ac.trie[p][buff[idx]];
    int ans = f(idx + 1, 0) + 1;
    if (ac.tag[nxt]) {}
    else ans = min(ans, f(idx + 1, nxt));
    return dp[idx][p] = ans;
}

int main(){
    int N , M;
    while (scanf("%d%d\n", &N, &M) ==2 and N + M) {
        ac.init();
        rep (i, N) {
            gets(buff);
            ac.add(buff);
        }
        ac.build();
        int ans = 0;
        rep (i, M){
            gets(buff);
            int len = strlen(buff);
            rep (i, len) dp[i].clear();
            ans += f(0, 0);
        }
        printf("%d\n", ans);
    }
	return 0;
}

