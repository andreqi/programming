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
    int n;
    while( scanf("%d", &n) == 1 and n > 0 ){
        scanf("%s", p);
        int len = strlen(p);
        if (len > n) printf("0\n");
        else {
            int i = 0 , j = -1;
            b[i] = j;
            while ( i < len ){
                while ( j >= 0 and p[i] != p[j] ) 
                    j = b[j];
                i++; j++;
                b[i] = j;
            }
            if (j == 0) printf("%d\n", n / len ); 
            else printf("%d\n", (n-j)/(len-j));
        }
    }
	return 0;
}

