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
const int MAXO = 2002;
const int MAXN = 1011;
const int CHARSET = 'Z' - 'A' + 1;

struct AhoCorasick {
    static const int NODES = 1000011;
    int trie[NODES][CHARSET];
    int fail[NODES];
    vector<int> tags[NODES];
    int end;
    void init() {
        end = 1;
        clr(trie[0], -1);
        tags[0].clear();
    }
    void add(const int * seq, int len, int id){
        int p = 0;
        rep (i, len) {
            if ( trie[p][*seq] == -1 ) {
                clr(trie[end], -1);
                tags[end].clear();
                trie[p][*seq] = end++;
            }
            p = trie[p][*seq];
            seq++;
        }
        tags[p].push_back(id);
    }

    void build() {
        queue <int> bfs;
        fail[0] = 0;
        rep (i, CHARSET) {
            if (trie[0][i] == -1) {
                trie[0][i] = 0;
            } else {
                bfs.push(trie[0][i]);
                fail[trie[0][i]] = 0;
            }
        }
        while ( not bfs.empty() ){
            int st = bfs.front(); 
            bfs.pop();
            rep (i, tags[fail[st]].size()) tags[st].push_back(tags[fail[st]][i]);
            rep (i, CHARSET) {
                if (trie[st][i] != -1) {
                    fail[trie[st][i]] = trie[fail[st]][i];
                    bfs.push(trie[st][i]);
                } else {
                    trie[st][i] = trie[fail[st]][i];
                }
            } 
        }
    }
} ac;


pii order[MAXO];
int t_order;
int N, M;

int grid[MAXN][MAXN];

void add_init(int idx, int idy) {
    if (idx and idy){
        add_init(idx, 0);
        add_init(0, idy);
        return;
    }
    int top = idx ? M : N;
    int fix = idx ? ( idx > 0 ? 0 : N - 1 ) : ( idy > 0 ? 0 : M - 1 );
    rep (i, top) {
        order[t_order++] = idx ? pii(fix, i) : pii(i , fix);
    }
}
bool valid(int pos, int top) {
    return pos >= 0 and pos < top;
}
char buff[MAXN];
int seq[MAXN];
int len[MAXN];
pair <pii, char> ans[MAXN];
string dir = "HABGCFED";
int main(){
    /*
     * Test for add_init
    N = 2 , M = 3;
    repn(idx, -1, 2) repn (idy, -1, 2) if (idx != 0 or idy != 0) {
        t_order = 0;
        add_init(idx, idy);
        rep (i, t_order) cout << order[i].fst << ":" << order[i].snd <<  ", ";
        cout << endl;
    }
    */
    int test = 0;
    scanf("%d", &test);
    int q;
    while (test--) {
        scanf("%d%d%d", &N, &M, &q);
        ac.init();
        rep (i, N){
            scanf("%s", buff);
            for (int idx = 0; buff[idx]; idx++) grid[i][idx] = buff[idx] - 'A';
        }
        rep (i, q){
            scanf("%s", buff);
            int idx;
            for (idx = 0; buff[idx]; idx++) seq[idx] = buff[idx] - 'A';
            ac.add(seq, idx, i);
            ans[i] = mp(mp(-1,-1), 'X');
            len[i] = idx - 1;
        }
        ac.build();
        int id_dir = 0;
        repn (idx, -1, 2) repn(idy, -1, 2) if (idx or idy) {
            char cur_dir = dir[id_dir++];
            t_order = 0;
            add_init(idx, idy);
            rep (i, t_order) {
                int x = order[i].fst , y = order[i].snd;
                int state = 0;
                while (valid(x, N) and valid(y, M)) {
                    int c = grid[x][y];
                    int nxt = ac.trie[state][c];
                    rep (i, ac.tags[nxt].size() ) {
                        int id_str = ac.tags[nxt][i];
                        ans[id_str] = mp(mp(x - idx * len[id_str], y - idy * len[id_str] ) ,cur_dir);
                    }
                    x += idx, y += idy;
                    state = nxt;
                }
            }
        }
        rep (i, q) printf("%d %d %c\n", ans[i].fst.fst, ans[i].fst.snd, ans[i].snd);
        if (test) printf("\n");
    }
	return 0;
}

