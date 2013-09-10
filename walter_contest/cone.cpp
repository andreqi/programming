#include <iostream>
#include <iomanip>
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

long double PI = acos(-1.0);

int main(){
	long double s;
	while (cin >> s) {
		long double r = sqrt(s/(4*PI));
		long double h = sqrt(8.0)*r;
		long double v = ( PI * r * r * h )/ 3.0;
		std::cout << std::fixed;
		cout << setprecision(2) << v << endl;
		cout << setprecision(2) << h << endl;
		cout << setprecision(2) << r << endl;
	}
	return 0;
}

