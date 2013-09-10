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
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

char board[4][10];
char solved[][10] = { "X won" , "O won" };
char cnt[300];
pii search(int bi, int bj, int dx, int dy){
	if (board[bi][bj]=='.') return pii(0, 0); 
	cnt['X'] = cnt['O'] = cnt['T'] = cnt['.'] = 0;
	rep(i, 4){
		if ( bi < 0 or bj < 0 or bi >= 4 or bj >= 4 ) 
			return pii(0, 0);
		cnt[board[bi][bj]]++;
		bi += dx, bj += dy;
	}
	if (cnt['.']) return pii(0, 0);
	if (cnt['X'] == 0) return pii(4, 1);
	if (cnt['O'] == 0) return pii(4, 0);
	return pii(0, 0);
}

const char * solve(){
	int full = false;
	rep(i, 4) rep(j, 4){
		full += board[i][j] == '.';
		repn(dx, -1, 2){
			repn(dy, -1, 2){
				if ( dx == 0 and dy == 0 ) continue;
				pii ans = search(i, j, dx, dy);
				if ( ans.fst == 4 ) return solved[ans.snd];
			}
		}
	}
	if (!full) return "Draw";
	return "Game has not completed";	
}


int main(){
	int test, id = 1;
	scanf("%d", &test);
	while (test--){
		scanf("\n");
		memset(cnt, 0, sizeof cnt);
		rep(i, 4) scanf("%s\n", board[i]); 
		printf("Case #%d: %s\n", id++, solve());
	}
	return 0;
}

