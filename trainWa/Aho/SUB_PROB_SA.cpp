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
int t, sa[MAXN], rank[MAXN];
int bc[256];
char txt[MAXN];
int cmp(int i , int j ) { return rank[i+t] < rank[j+t];}
void build_suffix( char * str, int len) {
    clr(bc, 0);
    rep (i, len) bc[str[i]]++;
    repn (i, 1, 256) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t=1; t < len; t*=2) {
        for (int i=0,j=1; j < len; i =j++) {
            while (j < len and rank[sa[i]] == rank[sa[j]]) j++;
            if (j-i==1) continue;
            int *begin = sa + i, *end = sa +j;
            sort(begin, end, cmp);
            int p, fst = rank[*begin + t], id = i;
            for (; begin < end; rank[*begin++] = id){
                p = rank[*begin+t];
                if (p==fst or (i <= fst and p < j)){}
                else fst = p, id = begin - sa;
            }
        } 
    }
   // rep (i, len) printf("%d %s\n", sa[i] , str + sa[i]);
   // printf("\n");
}
bool suff_search(char *q, int len) {
    int lo = 0,hi= len;
    int n = strlen(q);
    while (lo < hi) {
        int m = (lo+hi)/2;
        int c = strncmp(q, txt + sa[m], n);
        if (c ==0) return true;
        if (c < 0) hi = m;
        else       lo = m + 1;
    }
    return strncmp(q,txt + sa[lo],n) == 0;
}
char buff[MAXN];
int main(){
    scanf("%s", txt);
    int len = strlen(txt);
    build_suffix(txt, len + 1);
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%s", buff);
        printf("%s\n", suff_search(buff,len)?"Y":"N");
    }
	return 0;
}

