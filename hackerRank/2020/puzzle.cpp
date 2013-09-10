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

#define repn(i, a, b) for(int i=(int)a ; i <(int) b ; i++)
#define rep(i, n) repn(i, 0, n) 
#define all(x)  x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
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

const int MAXN = 1000100;

vector<pii> pref;

int f(int c, int u) {
	return 3*u - 2*c;
}

int solve_solo(string &s) {
	int c = 0, u = 0;	
	pref.push_back(mp(f(c,u), 0));
	rep (i, s.size()) {
		if (s[i] == '1') u++;
		else			 c++;
		pref.push_back(mp(f(c,u),1));
	}
	sort(all(pref));
	set<int> idx;
	int j = 0, ans = 0;
	repn (i, 1, pref.size()) {
		while (j < pref.size() and 
			   pref[j].fst <= pref[i].fst){
			idx.insert(pref[j].snd);
		}
		if (idx.empty()) {
		} else {
			int fdx = *idx.begin();
			if (fdx > i) continue;
			ans = max(ans, i - fdx);
		}
	}
	return ans;
}
vector<pii> suff;

void build(vector<pii> &x, string &s, int idx) {
	int ini = (idx < 0)? (s.size()):(0);
	int ce = 0, un = 0;
	x.push_back(mp(f(ce, un),ini));
	rep (i, s.size()) {
		ini += idx;
		if (s[ini] == '1') un++;
		else			   ce++;
		x.push_back(mp(f(ce, un),ini));
	}
}

int solve(string &s, int n) {
	pref.clear();
	build(pref, s, 1);
	build(suff, s, -1);
}

int main(){
	int n;
	string s;
	cin >> n >> s;
	int pode = solve_solo(s);
	if (pode == s.size()) cout << n * pode << endl;
	else {
		int ans = pode;
		ans = max(pode, solve(s, n));
		reverse(all(s));
		ans = max(ans, solve(s, n));
		cout << ans << endl;
	}
	return 0;
}

