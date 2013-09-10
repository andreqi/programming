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
#define MAXN 1000
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct translator{
	map< int , string > to_str;
	map< string , int > to_id;
	int id ;
	void clear(){
		id = 0 , to_str.clear() , to_id.clear();
	}
	int get_id( string s ){
		if( to_id.count( s ) ) return to_id[ s ];	
		to_str[ id ] = s;
		return to_id[ s ] = id++;
	} 
	string get_str( int x ){
		return to_str[ x ];
	}
} trans;

int seen[ MAXN ] , low[ MAXN ];
int in_stack[ MAXN ] , scc[ MAXN ] , n_scc;
int out_deg[ MAXN ] , tam_scc[ MAXN ] , timer;
stack< int > comp;
vector< int > adj[ MAXN ];
vector< int > cond[ MAXN ];
char buff[ MAXN ];
string str_buff[ MAXN ];

void read( int n ){
	trans.clear();
	rep( i , n ) adj[ i ].clear();
	rep ( i , n ){
		gets( buff );
		istringstream is( buff );
		string str_u;  is >> str_u;
		int u = trans.get_id( str_u );
		while( is >> str_u ){
			int v = trans.get_id( str_u );
			adj[ u ].push_back( v );
		}
	}
}

int dfs( int u ){
	seen[ u ] = low[ u ] = timer++;
	in_stack[ u ] = 1 , comp.push( u );
	int & low_u = low[ u ];
	rep( i , adj[ u ].size() ){
		int v = adj[ u ][ i ];
		if( seen[ v ] == -1 )	 low_u = min( low_u , dfs( v ) );
		else if( in_stack[ v ] ) low_u = min( low_u , seen[ v ]); 
	}
	if( low_u == seen[ u ] ){
		int x ; tam_scc[ n_scc ] = 0;
		do{
			tam_scc[ n_scc ]++;
			scc[ x = comp.top() ] = n_scc , comp.pop();
			in_stack[ x ] = 0;
		} while( x != u );
		n_scc++;
	}
	return low_u;
}

void solve( int n ){
	timer = n_scc = 0;
	memset( seen , -1 , sizeof seen );
	memset( out_deg , 0 , sizeof out_deg );
	memset( in_stack , 0 , sizeof in_stack );
	rep ( i , n ) if( seen[ i ] == -1 ) dfs( i ); 
	rep ( i , n ) cond[ i ].clear();
	rep ( u , n ){
		rep ( i , adj[ u ].size() ){
			int v = adj[ u ][ i ];
			if( scc[ v ] != scc[ u ] ){
				cond[ scc[ u ] ].push_back( scc[ v ] );
			}
		} 
	}
	queue< int > q;
	int ans = 0;
	memset( seen , 0 , sizeof seen ); 
	rep ( i , n_scc ) if( tam_scc[ i ] != 1 ) q.push( i ), seen[ i ] = 1;
	while( not q.empty() ){
		int cur = q.front(); q.pop();
		ans += tam_scc[ cur ];
		rep( i , cond[ cur ].size() ) if( ! seen[ cond[ cur ][ i ] ] ){
			seen[ cond[ cur ][ i ] ] = 1;
			q.push( cond[ cur ][ i ] ) ;
		}
	}
	printf("%d\n" , ans );
	int len = 0;
	if( ans ){ 
		rep ( i , n ) if( seen[ scc[ i ] ] )  str_buff[ len++ ] = trans.get_str( i );
		while( ans != len );
		sort( str_buff , str_buff + len );
		printf("%s" , str_buff[ 0 ].c_str() );
		rep ( i , len - 1 ) printf(" %s" , str_buff[ i + 1 ].c_str() );
	}
	printf("\n");
}

int main(){
	int n;
	while( scanf("%d\n" , &n ) == 1 and n ){
		read( n );
		solve( n );
	}
	return 0;
}

