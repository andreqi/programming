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

char * pat;
int * back;
int len_pat;

void kmp_preprocess(char * p, int n){
    int i = 0, j = -1;
    back[i] = j;
    while ( i < n ) {
        while ( j >= 0 and p[i] != p[j] ) 
            j = back[j];
        i++; j++;
        back[i] = j;
    }
}



int main(){
    int i, j;
    char cur_char;
    while ( scanf("%d", &len_pat) == 1 ) {
        getchar();
        pat = new char[len_pat + 2];
        back = new int[len_pat + 2];
        scanf("%s", pat);
        getchar();
        kmp_preprocess(pat, len_pat);
        i = 0, j = 0;
        while ( (cur_char = getchar()) != '\n' ) {
            while( j >= 0 and cur_char != pat[j] )
                j = back[j];
            j++; i++;
            if (j == len_pat){
                printf("%d\n", i - j ); 
                j = back[j];
            }
        }
        printf("\n");
        delete pat;
        delete back;
    }
	return 0;
}

