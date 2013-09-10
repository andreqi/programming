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

const int MAXN = 200;
const double EPS = 1e-8;

int cmp(double a, double b) {
	if (fabs(a-b) < EPS) return 0;
	if (a < b) return -1;
	return 1;
}

struct Point {
	int x, y;
	Point operator - (Point p) { return (Point){x-p.x, y-p.y}; }
	double operator * (Point p) { return x*p.y - y*p.x; }
	double angle() {
		return atan2(y, x);
	}
	double norm2() {
		double dx = x*x;
		double dy = y*y;
		return dx + dy;
	}
};

Point pt[MAXN];
Point pivot;

int cmp_pivot(Point i, Point j) {
	int ans = cmp((i-pivot).angle(), (j-pivot).angle());
	if (ans == 0) return cmp((i-pivot).norm2(), (j-pivot).norm2());
	return ans < 0;
}

int usd[MAXN][MAXN];
double ch_area[MAXN][MAXN]; 
double cache[MAXN][MAXN];
int base, n;
typedef Point Vector;

int ccw(Vector a, Vector b) {
	return a * b;
}

double dp(int id, int b) {
	int quedan = n - id - 1; 
	if (quedan + 1 < b * 2) {
		usd[id][b] = 2;
		return cache[id][b] = -1;
	}
	if (usd[id][b]) return cache[id][b];
	int first = (id + base) % n;
	if (b==1) {
		if (ch_area[first][quedan] < 0) {
			usd[first][b] = 2;
			return -1;
		}
		return ch_area[first][quedan];
	}
	usd[id][b] = 2;
	int p = 1;
	double ans = 0;
	repn (i, 1, quedan) {
		if (ch_area[id][i] < 0) break;
		double tmp = dp(id + i + 1, b-1);
		if (usd[id+1+i][b-1] == 2) continue; 
		if (p or ans > tmp + ch_area[id][i]) {
			p = 0;
			usd[id][b] = 1;
			ans = tmp + ch_area[id][i];
		} 
	}
	return ans;
}

Point ch[MAXN];

int main(){
	int b;
	while (cin >> b >> n and b+n) {
		cin >> pivot.x >> pivot.y;
		n--;
		rep (i, n) {
			int x, y;
			cin >> x >> y;
			pt[i] = (Point){x, y};
		}

		sort(pt, pt + n, cmp_pivot);
		int len = 0;
		rep (i, n) {
			cout << pt[i].x << " " << pt[i].y << endl;
			cout << " >> " ; 
			len = 0;
			ch[len++] = pivot;
			ch[len++] = pt[i];
			ch_area[i][0] = 0;
			repn (j, 1, n) {
				int nxt = (i + j) % n;
				if (ccw(pivot-pt[nxt], pt[i]-pivot) < 0) {
					repn (k, j, n) ch_area[i][j] = -1;
					break;
				}
				while (len >= 2 and 
					   ccw(ch[len-1]-ch[len-2], ch[len-1]-pt[nxt]) < 0)
					len--;
				ch[len++] = pt[nxt];
				ch[len] = pivot;
				ch_area[i][j] = 0;
				repn (k, 1, len+1) ch_area[i][j] += ccw(ch[k-1], ch[k]); 
				if (ch_area[i][j] < 0) ch_area[i][j] *= -1;
				ch_area[i][j] /= 2.0;
				cout << ch_area[i][j]  << " " ;
			}
			cout << endl;
		}


		double ans = -1;
		rep (i, n) {
			clr(usd, 0);
			base = i;
			double tmp = dp(0, b);
			if (usd[0][b] == 2) continue;
			cout << tmp << endl;
			if (ans < 0 or ans > tmp) 
				ans = tmp;
		}
		printf("%.2lf\n", ans);

	}
	return 0;
}

