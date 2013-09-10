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
const int MAXN = 100010;
const int CHARSET = 62;

char txt[MAXN];
int str[MAXN];

struct AhoCorasick {
    int end;
    int trie[MAXN][CHARSET];
    int64 tag[MAXN][21];
    int fail[MAXN];
    int q[MAXN];
    void init () {
        end = 1;
        clr(trie[0], -1);
        clr(tag[0], 0);
    }
    void add(int *str, int len, int id) {
        int p = 0;
        int x = id / 50;
        rep (i, len) {
            if (trie[p][*str] == -1) {
                clr(trie[end], -1);
                clr(tag[end], 0);
                trie[p][*str] = end++;
            }
            p = trie[p][*str++];
        }
        tag[p][x] |= twol(id%50); 
    }
    void build() {
        int h = 0, t = 0;
        rep (i, CHARSET) {
            if (trie[0][i] < 0) {
                trie[0][i] = 0;
            } else {
                fail[trie[0][i]] = 0;  
                q[h++] = trie[0][i];
            }
        }
        while (t < h) {
            int p = q[t++];
            rep (i, 20) tag[p][i] |= tag[fail[p]][i];
            rep (i, CHARSET) {
                if (trie[p][i] < 0) {
                    trie[p][i] = trie[fail[p]][i];
                } else {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    q[h++] = trie[p][i];
                }
            }
        }
    }
} ac;

char buff[MAXN];
int bc[256];
char charset[70];
void init() {
    int len =  'Z' - 'A' + 1;
    int h = 0;
    rep (i , len) {
        charset[h++] = i + 'A';
        charset[h++] = i + 'a';
    }
    rep (i, 10) charset[h++] = i + '0';
    rep (i, h) bc[charset[i]] = i;
}

int main(){
    init();
    scanf("%s", txt);
    int len = strlen(txt);
    int q;
    scanf("%d", &q);
    ac.init();
    rep (i, q) {
        scanf("%s", buff);
        int idx = 0;
        for (;buff[idx];idx++) str[idx] = bc[buff[idx]];
        ac.add(str, idx, i);
    }
    int64 total[21] = {0LL};
    ac.build();
    int p = 0;
    rep (i, len) {
        p = ac.trie[p][bc[txt[i]]];
        rep (j, 20) total[j] |= ac.tag[p][j];
    }
    rep (i, q) {
        if (total[i/50]&(twol(i%50))) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
	return 0;
}

