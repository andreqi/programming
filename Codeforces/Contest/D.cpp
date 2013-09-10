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

const int MAXN = 1<<18;

int tree[20][MAXN];
int n, m;

int change(int p, int b) {
    tree[0][p] = b;
    int id = (p/2);
    rep (i, n) {
        int ans = 0;
        if (i % 2 == 0) 
            ans = tree[i][id*2] | tree[i][id*2+1];
        else
            ans = tree[i][id*2] ^ tree[i][id*2+1];
        tree[i + 1][id] = ans;
        id /= 2;
    }
    return tree[n][0];
}

int main(){
    cin >> n >> m;
    rep (i, two(n)) cin >> tree[0][i];
    rep (i, two(n)) change(i, tree[0][i]);
    while (m--) {
        int p, b;
        cin >> p >> b;
        change(p - 1, b);
        cout << tree[n][0] << endl;
    }

	return 0;
}

