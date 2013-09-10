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
    int i , j, test, len, lenA, k;
    int tcase = 1;
    scanf("%d", &test);
    while ( test-- ) {
        scanf("%d", &len); 
        scanf("%s", p);
        i = 0, j = -1; 
        b[0] = -1;
        printf("Test case #%d\n", tcase++);
        while ( i < len ){ 
            while ( j >= 0 and p[i] != p[j] ) 
                j = b[j];
            i++, j++;
            lenA = i - j;
            k = i / lenA;
            if ( i % lenA == 0 and k > 1 ) {
                printf("%d %d\n", i, k);
            }
            b[i] = j;
        }
        printf("\n");
    }
	return 0;
}

