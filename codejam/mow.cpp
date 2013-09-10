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

int n , m;
int land[200][200];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int exists(int i , int j){
	int can = true;
	rep(idx, m) if(land[i][idx] != land[i][j]) can = false;
	if (can) return true;
	can = true;
	rep(idx, n) if(land[idx][j] != land[i][j]) can = false;
	if (can) return true;
	return false;
}

bool solve(){
	repn(color, 1, 10){
		int same = true;
		rep(i, n) rep(j, m){
			same = same and land[i][j] == land[0][0];
			if ( land[i][j] == color ) if( not exists(i,j) ) return false;
		}
		rep(i,n)rep(j,m) if(land[i][j]==color) land[i][j] = color + 1;
		rep(i, n) rep(j, m){
			same = same and land[i][j] == land[0][0];
		}
//		rep(i,n){
//			rep(j,m) cout << " " << land[i][j];
//			cout << endl;
//		}
//		cout << endl;
		if (same) return true;
	}
	return true;
}

int main(){
	int test, id = 1;
	scanf("%d", &test);
	while ( test-- ){
		scanf("%d%d", &n, &m);
		rep(i, n) rep(j, m) scanf("%d", land[i] + j);
		printf("Case #%d: %s\n", id++, solve()?"YES":"NO");
	} 
	return 0;
}

