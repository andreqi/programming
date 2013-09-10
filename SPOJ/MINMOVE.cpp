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
const int MAXLEN = 3001000;
int sa[MAXLEN], rank[MAXLEN], lcp[MAXLEN];
int bc[600];
char str[MAXLEN];
int t;
int len;
int cmp(int i, int j) {
    //if (len <= max(i,j) ) printf("%d %d %d\n",len,i,j);   
    return rank[i+t] < rank[j+t];
} 
int main(){
    scanf("%s",str);
    len = strlen(str);
    if (len == 0){
        printf("%d\n", 0);
        return 0;
    }
    rep (i, len) str[i+len] = str[i];
    str[len*2] = 0;
    str[len*2+1] = 0;
    int prevlen = len;
    len = len * 2 + 1;
    while( len >= MAXLEN );
    rep (i, len) bc[str[i]]++;
    repn (i, 1, 256) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t = 1; t < len; t *= 2) {
        for (int i=0, j=1; j < len; i=j) {
            while (j < len and rank[sa[i]] == rank[sa[j]]) j++;
            if (j-i==1) continue;
            int *begin = sa + i, *end = sa + j;
            sort(begin, end, cmp);
            int pk, fst = rank[*begin + t], id = i;
            for (; begin < end; rank[*begin++]=id) {
                pk = rank[*begin + t];
                if (pk == fst and (i <= fst and pk < j)) {}
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
    lcp[len -1] = 0;
    //rep (i, len) printf("%d %s\n", sa[i], str + sa[i]);
    
    rep (i, len){
        if(sa[i] < prevlen){
            int ans = sa[i];
            while (i < len and lcp[i] >= prevlen){
                i++;
                ans = min(ans, sa[i]);
            }
            printf("%d\n", ans);
            return 0;
        }
    }

	return 0;
}

