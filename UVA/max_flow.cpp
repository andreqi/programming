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
#define MAXE 10000000
#define MAXV 1000000
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int oo = 1<<28;

struct edge {
	int u , v , nxt , c ;
	edge(){}
	edge( int _u , int _v , int _nxt , int _c ){ 
		u = _u , v = _v , nxt = _nxt , c = _c ;
	}
};

struct network {
	edge E[ MAXE ];
	int b[ MAXV ];
	int pai[ MAXV ];
	int bot[ MAXV ];
	int e , v;
	network( ) {}
	network( int e , int v ): e(e ), v(v) {}
	void clear(){
		e = 0 , v = 0 ;
		memset( b , -1 , sizeof b );
	}
	int add( int frm , int to , int cap , int nxt ){
		E[ e++ ] = edge( frm , to , nxt , cap );
		return e - 1;
	}
	void add_edge_d( int frm , int to , int cap ){
		b[ frm ] = add( frm , to , cap , b[ frm ] );
		b[ to ] = add( to , frm , 0 , b[ to ] );
	}

	void add_edge_u( int frm , int to , int cap ){
		b[ frm ] = add( frm , to , cap , b[ frm ] );
		b[ to ] = add( to , frm , cap , b[ to ] );
	}


	int _i( int x ){ return x ^ 1; } 

	int bottleneck( int s, int t ){
		rep( i , v ) pai[ i ] = -1;
		queue< int > q;
		q.push( s );
		bot[ s ] = oo; 
		pai[ s ] = -1;
		while( not q.empty() ){
			int u = q.front(); q.pop();
			for( int id_e = b[ u ] ; id_e != -1 ; id_e = E[ id_e ].nxt ){
				int v = E[ id_e ].v;
				int c = E[ id_e ].c;
				if( c <= 0 ) continue;
				if( pai[ v ] != -1 ) continue;
				pai[ v ] = id_e;
				bot[ v ] = min( bot[ u ] , c );
				q.push( v );
				if( pai[ t ] != -1 ) break;
			}
			if( pai[ t ] != -1 ) break;
		}
		if( pai[ t ] == -1 ) return 0; 
		int id_e = pai[ t ];
		int neck = bot[ t ];
		int st = t;
		while( st != s ){
			E[ id_e ].c -= neck;
			E[ _i( id_e ) ].c += neck;
			st = E[ id_e ].u;
			id_e = pai[ st ];
		}
		return bot[ t ];
	}

	int max_flow( int s , int t ){
		int flow = 0;
		int p = 0;
		do{
			p = bottleneck( s , t );
			flow += p;
		}while( p );
		return flow;
	}
};

int main(){
	return 0;
}

