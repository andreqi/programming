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
const int MAXN = 10001;
int64 nm[MAXN];

int64 solve(int64 n, int64 k) {
	rep (i, k) nm[i] = n / k;
	repn (i, 1, n%k + 1) nm[i]++;
	int64 ans = 0;
	rep (i, k) {
		int inv = (k - i) % k;
		if (i == inv) {
			ans += ((nm[i]) * (nm[i]-1LL))/2LL;
		} else if (i < inv){
			ans += nm[i] * nm[inv];
		}
	}
	return ans;
}

int main(){
	int test;
	cin >> test;
	rep (tcase, test) {
		int64 n, k;
		cin >> n >> k;
		cout << solve(n, k) << endl;
	}
	return 0;
}

