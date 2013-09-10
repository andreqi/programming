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

char q[1010], txt[100100];
int bc[256], rank[100100], sa[100100];
int t;

int cmp(int i, int j) {return rank[i+t] < rank[j+t];}
void build_suffix(char *str , int len){
    clr(bc, 0);
    rep (i, len) bc[str[i]]++;
    repn (i, 1, len) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t = 1; t < len; t *= 2) {
        for (int i=0, j=1; j < len; i=j++){
            while (j < len and rank[sa[i]] == rank[sa[j]]) j++;
            if (j-i == 1) continue;
            int *begin = sa + i, *end = sa + j;
            sort(begin, end, cmp);
            int pk, fst = rank[*begin + t], id = i;
            for (; begin < end; rank[*begin++] = id) {
                pk = rank[*begin + t];
                if (pk == fst or (i <= fst and pk < j)){}
                else fst = pk, id = begin - sa;
            }
       }
    }
}

bool query(char *str, int len){
    int lo = 1, hi = len;
    int len_query = strlen(str);
    while (lo < hi){
        int mid = (lo + hi)/2;
        int ans = strncmp(txt+sa[mid], str, len_query);
        if (ans == 0) return true;
        if (ans < 0) lo = mid + 1;
        else         hi = mid;
    }
    return strncmp(txt+sa[lo], str, len_query)==0;
}

int main(){
    int test = 0;
    scanf("%d", &test);
    while (test--) {
        scanf("%s", txt);
        int len = strlen(txt);
        build_suffix(txt, len + 1);
        int q_len;
        scanf("%d", &q_len);
        while (q_len--) {
            scanf("%s", q);
            printf("%s\n", query(q, len)?"y":"n");
        }
    }
	return 0;
}

