#include <cstdio>
#include <cstring>

#define repn(i, a, b) for(int i=(int)a ; i <(int) b ; i++)
#define rep(i, n) repn(i, 0, n) 
#define clr(x, y) memset(x, (y), sizeof x)
using namespace std;

const int MAXN = 100011;
const int MAXT = 200011;

int wei[MAXN];
int tree[MAXT];

int sum(int idx) {
	int ans = 0;
	while (idx > 0) {
		ans += tree[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

void add(int idx, int val) {
	while (idx < MAXT) {
		tree[idx] += val;
		idx += (idx&-idx);
	}
}

int main(){
	int test;
	scanf("%d", &test);
	while (test--) {
		int n, r;
		int req;
		scanf("%d %d", &n, &r);
		int it = r + 1;
		rep (i, n) wei[i] = it + i + 1; 
		clr(tree, 0);
		rep (i, n) add(wei[i], 1);
		rep (i, r) {
			if (i) putchar(' ');
			scanf("%d", &req);
			req--;
			printf("%d", sum(wei[req]-1));
			add(wei[req], -1);
			wei[req] = it--;
			add(wei[req], 1);
		}
		printf("\n");
	}
	return 0;
}

