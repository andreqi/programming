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

int b[1000010];
char p[1000010];

int main(){
    while (scanf("%s", p) ==1 and p[0] != '*') {
        int i = 0 , j = -1;
        b[i] = j;
        while ( p[i] ){
            while ( j >= 0 and p[i] != p[j]) {
                j = b[j];
            }
            b[++i] = ++j;
        }
        int lenA = i - j;
        int k = i / lenA;
        if ( i % lenA ) printf("1");
        else            printf("%d", k);
        printf("\n");
    }
	return 0;
}

