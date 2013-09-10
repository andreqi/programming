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

const int MAXN = 400;

string type[MAXN];
int64 a[MAXN], b[MAXN];
int64 perm[MAXN];
int64 set_n[MAXN], add[MAXN];
void change(int64 &r, int64 x, int64 y) {
	if (r == x) r = y;
	else if (r == y) r = x;
}

int main(){
	int64 n, m, k;
	while (cin >> n >> m >> k) {
		if ((n + m + k) == 0) break;
		rep (i, k) {
			cin >> type[i];
			cin >> a[i];
			a[i]--;
			if (type[i][0] == 's') {
				cin >> b[i];
				b[i]--;
			}
		}
		clr(set_n, 0);
		clr(add, 0);
		rep (i, n) perm[i] = i;
		for (int i = k-1; i>=0 ;i--) {
			if (type[i][0] == 's') {
				swap(perm[a[i]], perm[b[i]]);
				rep (j, i) {
					change(a[j], a[i], b[i]);
					change(b[j], a[i], b[i]);
				}
			}
		}

		for (int i = k-1; i>=0 ;i--) {
			if (type[i][0] == 's') continue;
			if (type[i][0] == 'e') set_n[a[i]] = 1;
			else {
				if (set_n[a[i]]) continue;
				add[a[i]]++;
			}
		}
	//	rep (i, n) cout << perm[i] << " ";
	//	cout << endl;
		
		int64 nxt[MAXN], acum[MAXN], total[MAXN];
		int64 nacum[MAXN];
		int64 n_nxt[MAXN];
		rep (i, n) acum[i] = 0;
		rep (i, n) total[i] = 0;
		rep (i, n) nxt[i] = i;
		int len = 0;
		int it = 10;
		while (true) {
		//while (it--) {	
			len++;
			rep (i, n){
				nacum[i] = acum[perm[i]] + add[i];
				if (set_n[i])
					nacum[i] = add[i];
				n_nxt[i] = nxt[perm[i]];
			}
			rep (i, n) acum[i] = nacum[i];
			rep (i, n) nxt[i] = n_nxt[i];
		//	rep (i, n) cout << nxt[i] << " " ;
		//	cout << endl;
			int ans = 0;
			rep (i, n) ans += i == nxt[i];
			if (ans == n) break;
		}

		int64 big_step = m / len;

		repn (i, 0, n) {
			if (set_n[i]) 
				total[i] = acum[i];
			else
				total[i] = acum[i]*big_step;
		} 
		
		rep (i, n) acum[i] = total[i];
		rep (i, m % len) {
			rep (i, n) {
				nacum[i] = add[i] + total[perm[i]];
				if (set_n[i])
					nacum[i] = add[i];
				n_nxt[i] = nxt[perm[i]];
			}
			rep (i, n) nxt[i] = n_nxt[i];
			rep (i, n) total[i] = nacum[i];
		}
		
		cout << total[0];
		repn (i, 1, n) cout << " " << total[i] ;
		cout << endl;
	}
	return 0;
}

