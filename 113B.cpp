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

const int MAXN = 2100;

char str[MAXN], pref[MAXN], suf[MAXN];
int acum_suf[MAXN], is_pref[MAXN];
int b[MAXN];

vector<int> find_matches(char *txt, char* pat){
    vector <int> ans;
    int i = 0, j = -1;
    b[i] = j;
    while (pat[i]){
        while ( j >= 0 and pat[i] != pat[j] ) j = b[j];
        b[++i] = ++j;
    }
    i = 0, j = 0;
    while (txt[i]){
        while ( j >= 0 and txt[i] != pat[j]) j = b[j];
        ++i, ++j;
        if ( !pat[j] ){
            ans.push_back(i - j);
            j = b[j];
        }
    }
    return ans;
}

int bc[256], rank[MAXN], lcp[MAXN], sa[MAXN];
int t;
int cmp(int i, int j) { return rank[i+t] < rank[j+t];}
void build_suffix(char *str, int len){
    clr(bc, 0);
    rep (i, len) bc[str[i]]++;
    repn (i, 1, 256) bc[i] += bc[i-1];
    rep (i, len) sa[--bc[str[i]]] = i;
    rep (i, len) rank[i] = bc[str[i]];
    for (t=1; t < len; t*= 2) {
        for (int i=0,j=1; j < len; i=j++) {
            while (j<len and rank[sa[i]] == rank[sa[j]] ) j++;
            if ( j - 1 == 1 ) continue;
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
    int k = 0;
    rep (i, len) if (rank[i]) {
        int j = sa[rank[i]-1];
        while (str[i+k]==str[j+k]) k++;
        lcp[rank[i]-1] = k;
        if (k) k--;
    }
    lcp[len-1]= 0;
}

int main(){
    scanf("%s", str);
    scanf("%s", pref);
    scanf("%s", suf);
    int len_suf = strlen(suf);
    int len_str = strlen(str);
    int len_pref = strlen(pref);
    vector<int> m_pref = find_matches(str, pref);   
    vector<int> m_suf = find_matches(str, suf);   
    rep (i, m_pref.size()) is_pref[m_pref[i]] = 1;
    rep (i, m_suf.size()) acum_suf[m_suf[i] + len_suf - 1] = 1; 
    for (int i = len_str-1; i >= 0; i--) acum_suf[i] += acum_suf[i+1]; 
    build_suffix(str, len_str + 1);
    int ans = 0;
    repn (i , 1, len_str + 1) 
        if( len_str - sa[i] >= max(len_pref, len_suf) 
            and is_pref[sa[i]] ){
        int valid_id = sa[i] + max(lcp[i-1],max(len_suf, len_pref)-1);
        //int valid_id = sa[i] + lcp[i-1];
        ans += acum_suf[valid_id];
    }
    printf("%d\n", ans);
	return 0;
}

