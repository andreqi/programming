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
const int MAXN = 100100;
map <int, int> to, from;
map <int, int> same;
int seq[MAXN];
int next[MAXN];
int comp[MAXN];
int nlen;
int str[MAXN], rank[MAXN], lcp[MAXN], sa[MAXN], bc[MAXN];
int t;
int spar[MAXN][20];
int lcp_len (int i, int j) { 
    if ( i > j ) printf("NSP!\n");
    int len = j - i;
    int pot = 1;
    while (len > two(pot)) pot++;
    pot--;
    int ans = min(spar[i][pot], spar[j-two(pot)][pot]);
    //cout << i << " " << j << " " << ans << endl;
    return ans;
}
int cmp(int i, int j) { return rank[i + t] < rank[j+t]; }

void build_suffix(int *str , int len) {
    rep (i, MAXN) bc[i] = 0;
    rep (i, len) bc[str[i]]++;
    repn (i, 1, MAXN) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i; 
    rep (i, len) rank[i] = bc[str[i]];
    for (t=1; t < len; t *= 2) {
        for (int i=0,j=1; j < len; i=j++) {
            while (j < len and rank[sa[i]] == rank[sa[j]]) j++;
            if ( j - i <= 1 ) continue;
            int *begin = sa + i, *end = sa + j;
            sort(begin, end, cmp);
            int pk, fst = rank[*begin + t], id = i;
            for (; begin < end; rank[*begin++] = id) {
                pk = rank[*begin + t];
                if (pk==fst or (i <= fst and pk < j)) {}
                else fst = pk, id = begin - sa;
            }
        }
    }
    int k = 0;
    rep (i, len) if (rank[i]) {
        int j = sa[rank[i]-1];
        while (str[i+k] == str[j+k]) k++;
        lcp[rank[i]-1] = k;
        if (k) k--;
    }
    lcp[len-1] = 0;
    /*
    rep (i, len) {
        int j = sa[i];
        printf("%d -> ", j);
        while (str[j] > 0) printf("%d ", str[j++]);
        printf("\n");
    } */
    rep (i, len) spar[i][0] = lcp[i];
    for (int p = 1; two(p) <= len; p++ ) 
        for (int id = 0; len - id >= two(p); id++ ) 
            spar[id][p] = min(spar[id][p-1], spar[id+two(p-1)][p-1]);
} 

bool operator < (pii a , pii b){
    int len_a = a.snd - a.fst;
    int len_b = b.snd - b.fst;
    if (len_a != len_b) return len_a < len_b;
    return a < b;
}

int main(){
    int len;
    scanf("%d", &len);
    rep (i, len) scanf("%d", seq + i);
    rep (i, len) comp[i] = seq[i]; 
    sort(comp, comp + len);
    int k = 1;
    rep (i, len) if ( !to.count(comp[i]) ) { 
        to[comp[i]] = k;
        from[k] = comp[i];
        k++;
    }
    rep (i, len) comp[i] = to[seq[i]];
    for (int i = len - 1; i >= 0; i-- ) {
        next[i] = !same.count(comp[i]) ? -1 : same[comp[i]];
        same[comp[i]] = i;
    }
    //rep (i, len) printf("%d ", next[i]);
    //cout << endl;
    comp[len] = 0;
    build_suffix(comp, len + 1);
    vector<pii> ans;
    rep (i, len){
        int rank_i = rank[i];
        int j = i;
        while (next[j] > 0) {
            j = next[j];
            int rank_j = rank[j];
            int s = min(rank_j, rank_i), e = max(rank_j, rank_i);
            int len = j - i;
            if (lcp_len(s, e) >= len) ans.push_back(pii(i, j));
        }
    }
    sort(all(ans));
    int ini = 0;
    rep (i, ans.size()) {
      //  cout << ans[i].fst << " <> " << ans[i].snd << endl;
        if ( ans[i].snd >= ini and ans[i].fst >= ini ){
            ini = ans[i].snd;
        }
    }
    printf("%d\n", len - ini);
    while (ini < len) printf("%d%c", seq[ini++], ini == len ? '\n':' ');
    return 0;
}

