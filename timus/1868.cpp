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
string order[12];
string type = "gsb";
map< string, int > id;
int main(){
    rep (i, 12){
        cin >> order[i];
        id[order[i]] = i;
    }
    int n;
    cin >> n;
    int ans[200];
    clr(ans, 0);
    rep (i, n) {
        int k;
        cin >> k;
        rep (j, k) {
           string uni, dot, types;
           cin >> uni >> dot >> types;
           if (id.count(uni)==0) continue;
           int idx = id[uni];
           int real = idx / 4;
           int t = type.find(types[0]);
           if (t == real) ans[i] ++;
        }
    }
    int mx = *max_element(ans, ans + n);
    int paga = 0;
    rep (i, n) if (mx == ans[i]) paga += 5; 
    cout << paga << endl;
	return 0;
}

