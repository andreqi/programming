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

vector<int> val;

int dp[1111][10][101];
int m;

int f(int id, int prev, int diff) {
    if (id == m) {
        return true;
    }
    int x = id, y = prev, z = diff + 50;
    if (dp[x][y][z] != -1) return dp[x][y][z];
    int &ans = dp[x][y][z];
    ans = 0;
    rep (i, val.size()) {
        if (i+1 == y) continue;
        if (id%2) {
            int nxt = diff - val[i];
            if (nxt < 0) {
                ans = f(id + 1, i + 1, nxt);
                if (ans > 0) return ans;
            }
        } else {
            int nxt = diff + val[i];
            if (nxt > 0) {
                ans = f(id + 1, i + 1, nxt);
                if (ans > 0) return ans;
            }
        }
    }
    return ans;
}

vector<int> sol;

void g(int id, int prev, int diff) {
    if (id == m) {
        return;
    }
    int x = id, y = prev, z = diff + 50;
    int ans = 0;
    rep (i, val.size()) {
        if (i+1 == y) continue;
        if (id%2) {
            int nxt = diff - val[i];
            if (nxt < 0) {
                ans = f(id + 1, i + 1, nxt);
                if (ans){ 
                    sol.push_back(val[i]);
                    g(id + 1, i + 1, nxt);
                    return;
                }
            }
        } else {
            int nxt = diff + val[i];
            if (nxt > 0) {
                ans = f(id + 1, i + 1, nxt);
                if (ans > 0) {
                    sol.push_back(val[i]);
                    g(id + 1, i+1, nxt);
                    return;
                }
            }
        }
    }
}

int main(){
    string c;
    cin >> c;
    rep (i, c.size()) {
        if (c[i] == '0') continue;
        val.push_back(i+1);
    }
    cin >> m;
    memset(dp, -1, sizeof dp);
    int ans = f(0, 0, 0);
    if (ans) {
        cout << "YES" << endl;
        g(0,0,0);
        rep (i, sol.size()) {
            if (i) cout << " ";
            cout << sol[i];
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
	return 0;
}

