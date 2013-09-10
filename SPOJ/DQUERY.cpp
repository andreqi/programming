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

const int MAXN = 30011;

struct fenwick_tree {
    int tree[MAXN];

    fenwick_tree() {
        clr(tree, 0);
    }

    void add(int idx, int value) {
        while (idx < MAXN) {
            tree[idx] += value;
            idx += (idx & -idx);
        }
    }
    
    int query(int idx) {
        int ans = 0;
        while (idx > 0) {
            ans += tree[idx]; 
            idx -= (idx & -idx);
        }
        return ans;
    }
    
    int diff(int idx) { return query(idx + 1); }
    
    void add_number(int num) { return add(num + 2, 1); }
    
} bit;

enum event_type { INI, DATA, FIN };

int last[1000200];
int ans[2000200];
int data[MAXN];
int last_found[MAXN];
pii query[2000200];
struct event {
    int id, type;

    int value() const {
        if (type == DATA) return id; 
        if (type == INI) return query[id].fst;
        return query[id].snd;
    } 

    bool operator < (event e) const {
        if (value() == e.value()) {
            return type < e.type;
        }
        return value() < e.value();
    }
};
vector<event> order[30001];

int len = 0;

int main(){
    int n, m;
    scanf("%d", &n);
    rep (i, n) { 
        scanf("%d", data + i); 
        last_found[i] = last[data[i]]-1;
        last[data[i]] = i+1;
    }
    scanf("%d", &m);
    rep (i, m) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--, r--;
        query[i] = pii(l, r);
    }
    
    rep (i, m) order[query[i].fst].push_back((event) {i, INI});
    rep (i, n) order[i].push_back((event){i, DATA});
    rep (i, m) order[query[i].snd].push_back((event) {i, FIN});
    
    //sort(order, order + len);

    rep (i, 30001) rep (j, order[i].size()){
        event & e = order[i][j];
        if (e.type == DATA)
            bit.add_number(last_found[e.id]);
        else if (e.type == INI)
            ans[e.id] -= bit.diff(query[e.id].fst);
        else 
            ans[e.id] += bit.diff(query[e.id].fst);
    }

    rep (i, m) printf("%d\n", ans[i]);
    
	return 0;
}

