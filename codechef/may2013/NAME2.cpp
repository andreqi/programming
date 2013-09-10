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

char m[25010], w[25010];

bool is_substr( const char * s, const char * t){
    int i = 0, j = 0;
    while (t[j] and s[i]){
        if (s[i] == t[j]) i++;
        j++;
    }
    return s[i] == '\0';
}

int main(){
    int test = 0;
    scanf("%d", &test);
    while (test--){
        scanf("%s", m); 
        scanf("%s", w); 
        if ( is_substr(m, w) or is_substr(w, m) ){
           printf("YES\n");
        } else 
           printf("NO\n");
    }
	return 0;
}

