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
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
int n1, n2, m1, m2;

char patt[310][310];
char text[2010][2010];
int b[310];

int main(){
    scanf("%d%d",&n1,&n2);
    rep (i,n1) scanf("%s", patt[i] );
    scanf("%d%d",&m1,&m2);
    rep (i,m1) scanf("%s", text[i] );
    int i = 0, j = -1;
    b[i] = j;
    while( i < n1 ){
        while( j >= 0 and strncmp(patt[j], patt[i], n2) != 0  )
            j = b[j];
        b[++i] = ++j;
    }
    vector< pii > ans;
    rep (piv, m2-n2+1){
        i = 0 , j = 0;
        while( i < m1 ){
            while( j >= 0 and strncmp(patt[j], text[i]+piv, n2 ) != 0 )
                j = b[j];
            i++ , j++;
            if(j == n1){
                ans.push_back( pii(i-j, piv) );
                j = b[j];
            }
        }
    }
    sort( all( ans ) );
    rep (i, ans.size() ) {
        printf("(%d,%d)\n", ans[i].fst+1, ans[i].snd+1);
    }
    if ( ans.empty() ) printf("NO MATCH FOUND...\n");
	return 0;
}

