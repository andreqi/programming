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
#define MAXN 100001
typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int nxt[ MAXN ] , head[ MAXN ] , links[ MAXN ], len[ MAXN ];
int val[ MAXN ];
pii tree[ MAXN ];

int iterate(){
	int ans = 0;
	while( links[ 0 ] != -1 ){
		int prev = 0;
		int eval = links[ 0 ];
		int sum = 0;
		while( eval != -1 ){
			int type = val[ eval ];
			int node = head[ type ];
			head[ type ] = nxt[ node ];
			sum = max( sum , tree[ node ].snd );
			if( head[ type ] == -1 ){
				links[ prev ] = links[ eval ];
			}
			else { 
				prev = eval; 
			}
			eval = links[ eval ];
		}
		ans += sum;
	}
	return ans;
}

int cmp( pii a , pii b ){
	return a.snd != b.snd ? a.snd < b.snd : a.fst < b.fst;
}

int solve(){
	int n; scanf("%d" , &n );
	rep( i , n ) scanf( "%d%d" , &tree[ i ].fst , &tree[ i ].snd );
	memset( nxt , -1 , sizeof nxt );
	memset( head , -1 , sizeof head );
	memset( len , 0 , sizeof head );
	sort( tree , tree + n , cmp );
	for( int i = 0 ; i < n  ; i++ ){ 
		int id = tree[ i ].fst - 1 ;
		nxt[ i ] = head[ id ];
		head[ id ] = i;
		len[ id ] ++;
	}
	links[ 0 ] = -1;
	int j = 1;
	rep( i , MAXN ) if( head[ i ] != -1 ) { 
		val[ j ] = i;
		links[ j - 1 ] = j ;
		links[ j ] = -1;
		j++; 
	} 
	j = 0;
	while( links[ j ] != -1 ){
		j = links[ j ];
		cout << val[ j ] << endl;
	}
	cout << endl;
	return iterate(); 
}

int main(){
	int test , t_case = 1;
	scanf("%d" , &test );
	while( test-- ){
		printf("Case %d: %d\n" , t_case++, solve());
	}
	return 0;
}

