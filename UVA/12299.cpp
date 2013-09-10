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

const int MAXN = 100200;
const int oo = two(25);
int data[MAXN];

struct segment_tree {
	int min_tree[4*MAXN];

	void update(int idx, int val, int t_left, int t_right, int t_id) {
		if (idx < t_left or idx > t_right) 
			return;

		if (t_right == t_left) {
			min_tree[t_id] = val;
			return;
		}
		int mid = (t_left + t_right)/2;
		update(idx, val, t_left, mid, t_id*2);
		update(idx, val, mid + 1, t_right, t_id*2 + 1);
		min_tree[t_id] = min(min_tree[t_id*2], min_tree[t_id*2 + 1]);
	}

	int query(int q_left, int q_right, int t_left, int t_right, int t_id) {
		if (q_right < t_left or t_right < q_left) return oo;
		
		if (q_left <= t_left and t_right <= q_right)
			return min_tree[t_id];

		int mid = (t_left + t_right) / 2;
		int a = query(q_left, q_right, t_left, mid, 2*t_id);
		int b = query(q_left, q_right, mid+1 , t_right, 2*t_id + 1);
		return min(a, b);
	} 
} tree;

vector<int> parse(char * buff) {
	vector<int> ans;
	for (int i=0; buff[i]; i++) {
		if (buff[i] < '0' or buff[i] > '9') 
			buff[i] = ' ';
	}
	istringstream is(buff);
	int token;
	while (is >> token) {
		ans.push_back(token-1);
	}
	return ans;
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	rep (i, n) {
		int dt;
		scanf("%d", &dt);
		tree.update(i, dt, 0, n - 1, 1);
		data[i] = dt;
	}
	char buff[50];
	rep (i, q) {
		scanf("%s", buff);
		bool is_query = buff[0] == 'q';
		vector<int> tokens = parse(buff);
		if (is_query) {
			printf("%d\n", tree.query(tokens[0], tokens[1], 0, n-1, 1));
		} else {
			int p = tokens[0];
			int p_data = data[tokens[0]];
			int sz = tokens.size();
			repn (i, 1, tokens.size()){ 
				data[tokens[i-1]] = data[tokens[i]];
			}
			data[tokens[sz-1]] = p_data;
			rep (i, sz) tree.update(tokens[i], data[tokens[i]], 0, n-1, 1);
		} 
	}
	return 0;
}

