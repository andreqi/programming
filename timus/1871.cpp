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
const int MAXN = 200;
int fw[MAXN][MAXN];
string str[MAXN];
map<string, int> toStr;
vector<string> adj[MAXN];
vector<int> adji[MAXN];
int usd[MAXN];
int len_msg[MAXN];
int main(){
    int n, len;
    string u, v;
    cin >> n;
    clr(fw, 0);
    clr(usd, 0);
    clr(len_msg, 0);
    rep (i, n) {
        cin >> u >> len;
        str[i] = u;
        toStr[u] = i;
        rep (j, len) {
            cin >> v;
            adj[i].push_back(v);
        }
    }
    rep (i, n) {
        rep (j, adj[i].size()) {
            adji[i].push_back(toStr[adj[i][j]]);
        }
    }
   /* rep (i, n) {
        rep (j, n) 
            cout << fw[i][j];
        cout << endl;
    } */
    string msg;
    getline(cin, msg);
    getline(cin, msg);
    set <pii> q;
    usd[0] = 1;
    q.insert(pii(msg.size(), 0)); 
    len_msg[0] = msg.size();
    while ( not q.empty() ) {
        pii cur_pair= *q.begin();
        q.erase(q.begin());
        int cur = cur_pair.snd;
        int cur_len = cur_pair.fst;
        if (cur_len > 140) continue;
        rep (i, adji[cur].size()) {
            int nxt = adji[cur][i];
            int new_len= 6 + str[cur].size() + cur_len;
            if (new_len < len_msg[nxt] or !usd[nxt] ) {
                usd[nxt] = 1;
                len_msg[nxt] = new_len;
                q.insert(pii(len_msg[nxt], nxt));
            }
        }
    }
    vector <string> ans;
    rep (i, n) if(usd[i]) {
        ans.push_back(str[i]);
    }
    cout << ans.size() << endl;
    rep (i, ans.size()) cout << ans[i] << endl;
	return 0;
}

