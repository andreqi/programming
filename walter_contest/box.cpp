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

const int mod = 10007;
int sum(int a, int b) {
	return (a + b + mod) % mod;
}
int mult(int a, int b) {
	return (a * b + mod) % mod;
}
struct Matrix{
	int m[4][4];
	int n ;
	Matrix() { n = 4; clr(m, 0);}

	Matrix operator * (Matrix &b) {
		Matrix ans;
		rep (i, n) rep (j, n) rep(k, n) {
			ans.m[i][j] = sum(ans.m[i][j], mult(m[i][k] , b.m[k][j]));
		}
		return ans;
	} 
};
Matrix orig;

Matrix bin_exp(Matrix m, int64 e) {
	if(e == 1) return m;
	Matrix c = bin_exp(m, e/2);
	c = c * c;
	if (e&1) c = c * m;
	return c;
}

int solve(int64 n) {
	Matrix ans = bin_exp(orig, n);
	return ans.m[0][0];
}

int main(){
	rep (i, 4) rep (j, 4) orig.m[i][j] = (i==j)?2:1;
	rep (i, 4) orig.m[i][3-i] = 0;
	int test;
	cin >> test;
	rep (tcase, test) {
		int64 n;
		cin >> n;
		cout << solve(n) << endl;
	}
	return 0;
}

