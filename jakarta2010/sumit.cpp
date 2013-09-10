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
#define MOD 1000000007

vector<int> d;
vector<int> fq;

int C[100][100];
int pot[ 12 ];
int q[ 12 ];
int f(int dig, int n, int k){
   return C[dig - n - k ][k-1] ;
}

int solve(int dig){
    int res = 0;
    for(int i = 1; i <= dig; i++){
        for(int l = 0; l < fq.size(); l++){
            int tmp = 0;
            for(int k = 0; k < i; k++){
                for( int j = 0 ; j < d.size(); j++){
                    if ( q[ d[j] ] < fq[l] ) continue;
                    if ( i - fq[l] <= dig - q[d[j]] ) 
                     tmp = (tmp%MOD + d[j] * pot[k] %MOD )%MOD;
                }
            }
            res = (res%MOD +f(dig,i, fq[l])*tmp%MOD)%MOD; 
    //            cout << f(i,fq[l])*tmp << endl;
        }
    }
	return res;
}

int main(){
    pot[0] = 1;
    for( int i = 1; i < 12; i++) pot[i] = pot[i-1]*10;
    
    for( int i = 0; i < 100; i++){
        for(int j = 0; j <= i ; j++){
            if ( j == 0 || j == i ) C[i][j] = 1;
            else C[i][j] = (C[i-1][j]%MOD + C[i-1][j-1]%MOD)%MOD;
        }

    }
    int runs;
    cin >> runs;
    while(runs--){
        d.clear();
        int dig = 0;
        set<int> tmp;
        for( int i = 1; i <= 9; i++){
            cin >> q[ i ];
            if (q[i]){
               d.push_back(i);
               tmp.insert(q[i]);
               dig += q[i];
            }
        }
       fq =  vector<int> (tmp.begin(),tmp.end());
       cout << solve(dig) << endl;
    }

    return 0;
}


