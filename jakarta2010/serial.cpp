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
    static const int CHARSET = 11;
    static const int NODES = 200;
    int end;
    int tag[NODES], trie[NODES][CHARSET], fail[NODES];
    int q[NODES];
    void init(){
        end = 1;
        clr(trie[0], -1);
        tag[0] = 0;
    }
    void add( int * str , int len){
        int p = 0;
        rep(i, len){
            if (trie[p][*str] < 0){
                clr(trie[end], -1);
                tag[end] = 0;
                trie[p][*str] = end++;
            }
            p = trie[p][*str++];
        }
        tag[p] = 1;
    }
    void build(){
        int h= 0, t = 0;
        rep (i, CHARSET) {
            if (trie[0][i] < 0 ){
                trie[0][i] = 0;
            } else {
                fail[trie[0][i]] = 0;
                q[h++] = trie[0][i];
            }
        }
        while ( t < h) {
            int p = q[t++];
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                if (trie[p][i] < 0){
                    trie[p][i] = trie[fail[p]][i];
                } else {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    q[h++] = trie[p][i];
                }
            }
        }
    }
} ac;

char buff[100];
int str[100];
int64 x_size[100];
int64 dp[100][200];
int64 f(int idx, int p) {
    if (idx == 0) return 1LL;
    int64 & ans = dp[idx][p];
    if (ans != -1LL) return ans;
    ans = 0;
    rep (i, 10) {
        int nxt = ac.trie[p][i];
        if (ac.tag[nxt]) continue;
        ans += f(idx - 1, nxt);
    }
    return ans;
}
void rec(int idx, int p, int64 queda) {
    if (idx == 0){
        //cout << endl << "---" << queda << endl;
        while (queda != 1LL);
        return;
    }
    int64 ans = 0;
    rep (i, 10) {
        int nxt = ac.trie[p][i];
        if (ac.tag[nxt]) continue;
        int64 tmp = ans + f(idx - 1, nxt);
        if ( ans < queda and tmp >= queda ){
            printf("%d", i);
            rec(idx -1, nxt, queda - ans);
            return;
        } 
        ans = tmp;
    }
    return ;
}


int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        int K = 0, x;
        ac.init();
        scanf("%d", &K);
        rep (i, K) {
          scanf("%s", buff);
          int len = strlen(buff);
          rep (j, len) str[j] = buff[j] - '0';
          ac.add(str,len);
        }
        ac.build();
        int N;
        clr(dp, -1);
        repn (i, 1, 13){
            int64 ans = 0;
            repn (j,1 ,10){
                int nxt = ac.trie[0][j];
                if (ac.tag[nxt]) continue;
                ans += f(i-1, ac.trie[0][j]);
            } 
            x_size[i] = ans;
        }
        scanf("%d", &N);
        rep (i, N) {
            int64 q;
            scanf("%lld", &q);
            int64 que = q;
            int64 nrs = 0;
            repn (len, 1, 12) {
                if (nrs < que and nrs + x_size[len] >= que ){
                    que -= nrs;
                   // cout << "len " << nrs << " " << que << endl;
                    int64 sz = 0;
                    repn (dig, 1, 10) {
                        int nxt = ac.trie[0][dig];
                        if (ac.tag[nxt]) continue;
                        int64 nxt_sz = sz + f(len-1, nxt);
                        if (sz < que and que <= nxt_sz){
                            printf("%d", dig);
                            int64 queda = que - sz;
                            rec(len-1, nxt, queda);
                            break;
                        }
                        sz = nxt_sz;
                        //cout << sz << endl;
                    }
                    break;
                }
                nrs += x_size[len];
            }
            if ( i + 1 < N )
                printf(" ");
            else 
                printf("\n");
        }
    }
	return 0;
}

