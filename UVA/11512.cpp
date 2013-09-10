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

const int MAXN = 1010;
char str[MAXN];
int rank[MAXN], lcp[MAXN];
int sa[MAXN] , bc[256] , t;
int cmp(int i, int j) { return rank[i+t] < rank[j+t];}
void build_suffix(char *str , int len){
    clr(bc, 0);
    rep (i, len) bc[str[i]]++;
    repn (i, 1, 256) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t=1; t<len; t *= 2) {
        for (int i=0,j=1; j < len; i=j++) { 
            while(j < len and rank[sa[i]] == rank[sa[j]]) j++;
            if (j-i == 1) continue; 
            int *begin = sa + i, *end = sa + j;
            sort(begin, end, cmp);
            int pk, fst = rank[*begin+t], id = i;
            for (; begin < end; rank[*begin++] = id) {
                pk = rank[*begin + t];
                if ( pk == fst or (i<= fst and pk < j)){}
                else fst = pk , id = begin - sa;
            }
        }
    }
    int k = 0;
    rep (i, len) if (rank[i]) {
        int j = sa[rank[i] - 1];
        while ( str[i+k] == str[j+k] ) k++;
        lcp[rank[i] - 1] = k;
        if (k) k--;
    }
    lcp[len-1] = 0;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%s", str);
        int len = strlen(str);
        str[len+1]=0;
        build_suffix(str, len+1);
        int * max_e = max_element(lcp, lcp + len);
        if (*max_e == 0) {
            printf("No repetitions found!\n");
        } else {
            int i = 0;
            int id = max_e - lcp;
            char *ans = str + sa[id];
            ans[*max_e] = 0;
            while (max_e[i] == *max_e) i++;
            printf("%s %d\n", ans, i + 1);
        }
    }
	return 0;
}

