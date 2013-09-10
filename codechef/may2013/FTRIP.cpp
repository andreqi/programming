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
#define two(x) (1<<(x))
#define twol(x) (1LL<<(x))
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

double p[1010][1010];
int s, n, m, k;

inline double amix(int np, int kp){
    int salio = n - np;
    int quedan = m - (k - kp);
   // if ( s == salio ) cout << "wtf" << endl;
  //  cout << np << " " << kp << " " << (quedan * 1.0) / (1.0*(s - salio)) << endl;
    return (quedan * 1.0) / (1.0*(s - salio)) ;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--){
        scanf("%d%d%d%d", &s, &n, &m, &k);
        s--,n--,m--;
        rep (i, k+1) p[0][i] = 0;
        if (n<k) printf("0.000000\n");
        else {
            p[0][0] = 1;
            repn (i, 1, n+1) repn (j, 0, k+1){
                int saque = n - i;
                int amigos = m - k + j;
                int quedan = s - saque;
                if ( quedan < amigos ) { // invalid
                    p[i][j] = 0;
                    continue;
                }
                if ( i < j ) {
                    p[i][j] = 0; 
                    continue;
                }
                if ( j == 0 ){
                    p[i][j] = p[i-1][j];
                    continue;
                }
                p[i][j] = p[i-1][j] * (1.-amix(i,j))
                        + p[i-1][j-1] * (amix(i, j));
            }
        //    rep(i, n+1){
        //        rep(j, k+1) 
        //            cout << p[i][j] << " ";
        //        cout << endl;
        //    }
            printf("%.6lf\n",p[n][k]);
        }
    }
	return 0;
}

