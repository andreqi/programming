#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <cctype>
#include <queue>
#include <numeric>
#include <cmath>
#define repn(a,x,y) for (int a=x; a<y; a++)
#define rep(a,y) repn(a, 0, y)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define mp make_pair
#define FOR(it,A) for (typeof A.begin() it=A.begin(); it!=A.end(); it++)
#define ones(x) __builtin_popcountll(x)
#define clr(A,x) memset (A, x, sizeof A)
#define EPS (1e-9)
#define cua(x) (x)*(x)
#define fst first
#define snd second
#define debug(x) cout << #x << " = " << x <<endl
#define TAM 110

using namespace std;

typedef long double ld ;
typedef long long int64 ;
typedef pair<int64,int64> pii ;

const int MAXN3 = 181712 + 15;
const int MAXN4 = 12446 + 15;
const int MAXN5 = 2605 + 15;
const int MAXN = 946 + 15;
const int64 oo = 1LL << 51;
const int64 MAXSQRT = 31622776 + 2; 

int64 n3[MAXN3];
int64 n4[MAXN4];
int64 n5[MAXN5];
int64 nk[MAXN][MAXN];
pii ans[MAXN3 + 1000];

void pre() {
	nk[0][0] = 1;
	rep (i, MAXN) {
		nk[i][0] = nk[i][i] = 1;
		repn (j, 1, i) {
			if ( nk[i-1][j-1] > oo ) continue;
			if ( nk[i-1][j] > oo ) continue;
			nk[i][j] = nk[i-1][j-1] + nk[i-1][j]; 
		}	
	}
	
	rep (i, MAXN3) {
		if (i < 3) n3[i] = 0;
		else {
			int64 cast = i;
			int64 mult = ((cast)*(cast-1)*(cast-2))/6LL;
			n3[i] = mult;
		}
	}

	rep (i, MAXN4) {
		if (i < 4) n4[i] = 0;
		else {
			int64 cast = i;
			int64 mult = ((cast)*(cast-1)*(cast-2)*(cast-3))/24LL;
			n4[i] = mult;
		}
	}

	rep (i, MAXN5) {
		if (i < 5) n5[i] = 0;
		else {
			int64 cast = i;
			int64 mult = ((cast-4)*(cast)*(cast-1)*(cast-2)*(cast-3))/120LL;
			n5[i] = mult;
		}
	}
}
int len;
int64 is_sqr(int64 n) {
	int64 lo = 1, hi = MAXSQRT;
	while (lo < hi) {
		int64 mid = (hi + lo) >> 1;
		if (mid * mid < n) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}
	if (lo *lo != n) return -1;
	return lo;
}
void solve2(int64 m) {
	ans[len++] = (mp(m, 1));
	if (m > 1)
	ans[len++] = (mp(m, m-1));
	if (m&1LL) return;
	int64 disc = 1 + 8*m;
	int64 x;
	if ((x=is_sqr(disc)) != -1) {
		int64 a = 1 + x;
		if (a&1LL) return;
		a /= 2LL;
		ans[len++] = (mp(a, 2));
		if (a > 2)
			ans[len++] = (mp(a, a-2));
	} 
}

int main() {
	pre();
	int test;
	scanf("%d", &test);
	rep (tcase, test) {
		int64 m;
		scanf("%lld", &m);
		len = 0;
		rep (i, MAXN3) if (n3[i] == m) {
			ans[len++] = (mp(i, 3));
			if (i > 3)
			ans[len++] = (mp(i, i-3));
		}
		rep (i, MAXN4) {
			if (n4[i] == m) {
				ans[len++] = (mp(i, 4));
				if (i > 4)
				ans[len++] = (mp(i, i-4));
			}
		}
		rep (i, MAXN5) {
			if (n5[i] == m) {
				ans[len++] = (mp(i, 5));
				if (i > 5)
				ans[len++] = (mp(i, i-5));
			}
		}
		rep (i, MAXN) {
			repn (j, 0, i+1) {
				if (nk[i][j] == m) {
					ans[len++] = (mp(i,j));
				}
			}
		}
		solve2(m);
		sort(ans, ans + len);
		len = unique(ans, ans + len) - ans;
		printf("%d\n", len);
		rep (i, len) {
			if (i) putchar(' ');
			printf("(%lld,%lld)", ans[i].first, ans[i].second);
		}
		putchar(10);
	}
	return 0;
}



