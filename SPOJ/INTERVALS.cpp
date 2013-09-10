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

struct Node {
    int l, r, c, id;
    bool operator < ( Node n ) const {
        if (l != n.l) return l < n.l;
        if (r != n.r) return r < n.r;
        if (c != n.c) return c < n.c;
        return id < n.id;
    }
    void print(){
        cout << l << " " << r << " " << c << endl;
    } 
};

int inter(Node &a, Node &b) {
    if (a.l == b.l) return b.r - a.r;
    return a.r - b.l + 1;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        int n, l, r, c, len = 0;
        scanf("%d", &n);
        set <Node> s;
        rep (i, n) { 
           scanf("%d%d%d", &l, &r, &c); 
           Node n_node = (Node){l, r, c, len++};
           s.insert(n_node);
        }
        int ans = 0;
       /* int it = 20;
        while (s.size() > 1) {
        */
        while (s.size() > 1) {
            /*
            it--;
            if (it <= 0) break;
            cout << s.size() << endl;
           vector<Node> vs = vector<Node>(all(s));
           rep (i, vs.size()) vs[i].print();
           cout << endl;
           */
           Node a = *s.begin();
           s.erase(s.begin());
           Node b = *s.begin();
           s.erase(s.begin());
           if (a.r < b.l) {
              ans += a.c;
              s.insert(b);
              continue;
           }

           if (a.l == b.l) {
              if (a.r == b.r) {
                 Node n_node = (Node){a.l, a.r, max(a.c, b.c), a.id};
                 s.insert(n_node);
              } else {
                 int in = inter(a, b);
                 int pone = min(b.c, in);
                 int queda = b.c - pone;
                 a.c = max(a.c, pone);
                 //ans += a.c;
                 s.insert(a);
                 if (queda){
                     Node n_node = (Node){a.r+1, b.r, queda, len++};
                     s.insert(n_node);
                 }
              }
           } else {
               int in = inter(a, b);
               int pone = min(a.c, in);
               int queda = a.c - pone;
               s.insert(b);
               if (pone) {
                  Node n_node = (Node){b.l, a.r, pone, len++};
                  s.insert(n_node);
               }
               if (queda) {
                  //Node n_node = (Node){a.l, b.r-1, queda, len++};
                  ans += queda; 
                 // s.insert(n_node);
               }
           }
        }
        if (s.empty()){}
        else {
            Node no = *s.begin();
            ans += no.c;
        }
        printf("%d\n", ans);
    }
	return 0;
}

