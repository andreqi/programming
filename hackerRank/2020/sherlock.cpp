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

const int MAXN = 100010;

pii dp[MAXN];
void min(pii &a , pii b) {
	if (a.fst == -1) a = b;
	else {
		if (a.fst < b.fst) a = b;
	}
} 
void precalc() {
	dp[0] = mp(0,0);
	repn (i, 1, MAXN) {
		dp[i] = mp (-1,-1);
		if (i >= 3) {
			pii prev = dp[i-3];
			if (prev.fst != -1) {
				prev.fst++;
				min(dp[i], prev);
			}
		}
		if (i >= 5) {
			pii prev = dp[i-5];
			if (prev.fst != -1) {
				prev.snd++;
				min(dp[i],prev);
			}
		}
	}
}

void solve(int n) {
	pii ans = dp[n];
	if (ans.fst == -1) cout << -1 << endl;
	else {
		int cinco = ans.fst * 3, tres = ans.snd * 5;
		rep (i, cinco) cout << 5 ;
		rep (i, tres) cout << 3;
		cout << endl;
	}
}


int main(){
	int test;
	cin >> test;
	precalc();
	rep (tcase, test) {
		int n;
		cin >> n;
		solve(n);
	}
	return 0;
}

