#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

#define mp make_pair
#define repn( i , a , b ) for( int i = a ; i < b ; i++ ) 
#define rep( i , n ) repn( i ,0 , n )
#define all( x ) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define oo 1 << 30
#define MAXN 52

typedef pair< int, int > pii;
typedef long double ld;
typedef long long int64;

vector<int> pai[ MAXN ];
vector<int> dir_child[ MAXN ];
vector<int> child[ MAXN ];
int inCircle[ MAXN ];
int deg[ MAXN ];
class CirclesGame{
	int cache[ MAXN ];
	int dfs( int v ){
		int grundy[ MAXN ];
		memset( grundy , 0, sizeof grundy );
		int & ans = cache[ v ];
		int len = 0;
		if( ans != -1 ) return ans;
		rep( i , child[ v ].size() ){
			int u = child[ v ][ i ];
			int ban = u;
			int mex = 0;
			rep( j , dir_child[ u ].size() ) mex ^= dfs( dir_child[ u ][ j ] );
			while( u != v ){
				u = inCircle[ u ];
				rep( k , dir_child[ u ].size() ){
					int nxt = dir_child[ u ][ k ];
					if( nxt == ban ) continue;
					mex ^= dfs(nxt);
				}
			}
			grundy[ mex ] = 1;
		}
		while( grundy[ ans ] == 0 ) ans++; 
		return ans;
	}

	public :
	string whoCanWin( vector<int> x , vector<int> y , vector<int> r ){
		int n = x.size();
		rep( i , n ) pai[i].clear();
		rep( j , n ) child[j].clear();
		// check if circle[i] is in circle[j]
		rep(i ,n) rep(j ,n) {
			int dx = x[i] - x[j] , 
			 	dy = y[i] - y[j];
			if( dx*dx + dy*dy >= r[j]*r[j] ) continue;
			double nr = r[j]*r[j]*1. - sqrt(dx*dx +dy*dy);
			if( nr < r[i] ) continue;
			pai[i].push_back(j);
			child[j].push_back(i);
		}
		memset( inCircle , -1 , sizeof inCircle );
		queue< int > q;
		rep(i ,n) {
			deg[ i ] = pai[i].size();
			if( deg[i] == 0 ){
				q.push( i );	
			}
		}
		while( not q.empty() ){
			int cur = q.front(); q.pop();
			rep( i , child[ cur ].size() ) {
				int nxt = child[ cur ][ i ];
				deg[ nxt ]--;
				if( deg[ nxt ] == 0 ){
					inCircle[ nxt ] = cur;
					q.push( nxt );
				}
			}
		}
		rep(i,n) dir_child[i].clear();
		rep( i , n) if( inCircle[ i ] != -1 ) {
			dir_child[ inCircle[ i ] ].push_back( i );
		}
		int ans = 0;
		rep( i , n ) if( inCircle[ i ] == -1 ) ans ^= dfs( i );
		return ans == 0 ? "Alice" : "Bob"; 
	}
};

int main(){
	CirclesGame * game = new CirclesGame();
	game->whoCanWin( NULL , NULL , NULL );
	return 0;
}


