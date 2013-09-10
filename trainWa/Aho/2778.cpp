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
const int MAXN = 111;
const int MOD = 100000;

int64 sum(int64 a, int64 b = 0LL) {
    return ( MOD + a%MOD + b%MOD)%MOD;
}
int64 mult(int64 a, int64 b){
    return (sum(a)*sum(b))%MOD;
}

int64 t[MAXN][MAXN];
int64 _ans[MAXN][MAXN];
void multi( int64 m[][MAXN] , int64 c[][MAXN] , int n){
     rep (i, n) rep (j, n) _ans[i][j] = 0;
     rep (i, n) rep (j, n) t[i][j] = c[j][i];
     rep (i, n) rep (j, n) rep(k, n) {
         _ans[i][j] = sum(_ans[i][j], mult(m[i][k], t[j][k])); 
     }
     rep (i, n) rep (j, n) m[i][j] = _ans[i][j];
}

int64 bin_exp(int64 n, int64 c[][MAXN]  , int id){
    int64 ans[MAXN][MAXN] = {0};
    rep (i, id) ans[i][i] = 1;
    while (n > 0){
        if (n & 1LL) multi(ans, c, id);
        multi(c, c, id);
        n >>= 1;
    }
    int64 ansi = 0;
    rep (i, id) ansi = sum(ansi, ans[0][i]);
    return ansi;
}

int que[MAXN + 100];
struct AhoCorasick {
    static const int CHARSET = 4;
    int end;
    int tag[MAXN];
    int trie[MAXN][CHARSET];
    int fail[MAXN];
    void init(){
        end = 1;
        clr(trie[0],-1);
        tag[0] = 0;
        fail[0] = 0;
    }
    void add(const int *seq, const int len, const int id){
        int p = 0;
        rep (i, len) {
            if (trie[p][*seq] == -1) {
                clr(trie[end],-1);
                tag[end] = 0;
                trie[p][*seq] = end++;
            }
            p = trie[p][*seq++];
        }
        tag[p] |= id;
    } 
    void build() {
        int h = 0 , t = 0;
        rep (i, CHARSET) {
            if (trie[0][i]==-1) {
                trie[0][i] = 0;
            } else {
                que[h++] = trie[0][i];
            }
        }
        while ( t < h ) {
            int p = que[t++];
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                if (trie[p][i] == -1 ){
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
int seq[100];
string actg = "ACTG";
int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    ac.init();
    rep (i, m) {
        scanf("%s", buff);
        int idx;
        for (idx = 0; buff[idx]; idx++) seq[idx] = actg.find(buff[idx]);
        ac.add(seq, idx, two(i));
    }
    int len = ac.end;
    ac.build();
    int64 ma[MAXN][MAXN] = {0};
    rep (i, len) {
        if ( ac.tag[i] ) continue;
        rep (j, ac.CHARSET) {
            int nxt = ac.trie[i][j];
            if (ac.tag[nxt]) continue;
            ma[i][nxt]++;
        }
    }
    //M.print();
    cout << bin_exp(n, ma, len) << endl;
	return 0;
}

