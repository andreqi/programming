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

const int MAXN = 3000000;

int rank[MAXN], sarr[MAXN];
int bc[256], t, lcp[MAXN];

int cmp(int i, int j) { return rank[i+t] < rank[j+t];}

void suffix_build(char * str, int len){
    clr(bc, 0);
    rep (i, len) bc[str[i]]++;
    repn (i, 1, 256) bc[i] += bc[i-1];
    rep (i, len) sarr[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t = 1; t < len ; t <<= 1){
        for(int i = 0, j = 0; j < len; i = j++){
            while (j < len and rank[sarr[i]] == rank[sarr[j]]) j++;
            if (j-i == 1) continue;
            int * begin = sarr + i, * end = sarr + j;
            sort(begin, end, cmp);
            int pk, fst = rank[*begin + t], id = i;
            for(;begin < end; rank[*begin++] = id){
                pk = rank[*begin + t];
                if (pk == fst or (i <= fst and pk < j)){}
                else fst = pk, id = begin - sarr;
            }
        } 
    }
    int k = 0;
    rep (i, len) if(rank[i]){
        int j = sarr[rank[i] - 1];
        while (str[i + k] == str[j + k]) k++;
        lcp[rank[i] - 1] = k;
        if ( k ) k--;
    }
    lcp[len-1] = 0;
    //rep(i , len){
    //   printf("%s\n", str + sarr[i]);
    //}
}

char str[MAXN];

int main(){
    int test;
    test = 1;
    while (test--){
        scanf("%s", str);
        int len = strlen(str);
        rep (i, len) str[len + i] = str[i];
        str[len * 2 ] = 0;
        suffix_build(str, 2 * len + 1);
        int eq = true;
        int ans = 0;
        rep (i, 2*len) if (sarr[i] < len){
            ans = sarr[i];
            while ( lcp[i] >= len ){
                if ( sarr[i] < len ) 
                    ans = min(ans, sarr[i+1]);
                i++;
            }
            break;
        }
        printf("%d\n", ans);
    }
	return 0;
}

