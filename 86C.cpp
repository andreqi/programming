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

struct AhoCorasick {
    static const int MAXNODE = 110;
    static const int CHARSET = 4;
    static const int UNDEF = 0;

    int end;
    int trie[MAXNODE][CHARSET];
    int fail[MAXNODE];
    int tag[MAXNODE];

    void init(){
        tag[0] = UNDEF;
        end = 1;
        clr(trie[0], -1);
    }

    void add(int len, const int * str, int id) {
        int p = 0;
        rep (i, len) {
            if (trie[p][*str] == -1) {
                clr(trie[end], -1);
                tag[end] = UNDEF;
                trie[p][*str] = end++;
            }
            p = trie[p][*str++];
        }
        tag[p] |= id;
    }

    void build () {
        queue <int> bfs;
        rep (i, CHARSET){
            int & root = trie[0][i];
            if (root == -1 ) {
                root = 0;
            } else {
                bfs.push(root);
                fail[root] = 0;
            }
        }
        while ( not bfs.empty() ) { 
            int p = bfs.front(); 
            bfs.pop();
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                int &next = trie[p][i];
                if ( next != -1 ) {
                    fail[next] = trie[fail[p]][i];
                    bfs.push(next);
                } else {
                    next = trie[fail[p]][i];
                }
            }
        }
    }
} ac;
char gen[100][100];
int code[100];
map<int, int> dp[1010][12];
int memo[two(11)];
string acgt  = "ACGT";
const int64 MOD = 1000000009LL;
int maxlen = 0;
int64 sum (int64 a, int64 b = 0LL) {
    return ((a%MOD + b%MOD) % MOD + MOD ) % MOD;
}

int max_len( int mask ) {
    if (memo[mask] != -1) return memo[mask];
    int ans = 0;
    rep (i, 10) if (mask & two(i))  ans = max(ans, (int)strlen(gen[i])); 
    return memo[mask] = ans;
}
int64 f(int idx, int noMatch, int state) {
   // cout << idx << " " << noMatch << " " << state << endl;
    if (idx == 0) return noMatch == 0 ;
    if( dp[idx][noMatch].count(state) ) return dp[idx][noMatch][state];
    int64 ans = 0;
    if( noMatch >= maxlen ) 
        return dp[idx][noMatch][state] = 0;
    rep (i, 4) {
        int nxt = ac.trie[state][i];
        int nnm = max(noMatch + 1 - max_len(ac.tag[nxt]), 0);
        int64 nans = 0;
        if (nnm > 0) nans = f(idx-1, noMatch+1, nxt);
        else nans = f(idx-1, nnm, nxt);
        ans = sum(ans, nans);
    }
    return dp[idx][noMatch][state] = ans;
}
int main(){
    int k, len = 0;
    clr(memo, -1);
    scanf("%d %d", &len, &k);
    rep (i, k) scanf("%s", gen[i]);
    ac.init();
    int j;
    rep (i, k){
        for (j=0; gen[i][j]; j++) 
            code[j] = acgt.find(gen[i][j]);
        ac.add(j, code, two(i));
        maxlen = max(j, maxlen);
    }
    ac.build();
    rep(i, 1010) rep(j, 12) dp[i][j].clear();
    cout << f(len,0,0) << endl;
	return 0;
}

