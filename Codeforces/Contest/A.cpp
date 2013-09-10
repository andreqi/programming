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

int main(){
    string s;
    cin >> s;
    rep (i, s.size()) {
        if (s[i] == '+') s[i] = ' ';
    }
    istringstream is(s);
    vector<string> vs;
    string r;
    while (is >> r) vs.push_back(r);
    sort(all(vs));
    int p = 0;
    rep (i, vs.size()) {
        if (p) cout << '+';
        cout << vs[i];
        p = 1;
    }
    cout << endl;
	return 0;
}

