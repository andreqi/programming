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
#define MAXN 50
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
int src = MAXN + MAXN * MAXN - 1 ;
int snk = MAXN + MAXN * MAXN - 2;
const int oo = 1<<28;

struct Edge{
	int u , v , cap , nxt;
	Edge(){}
	Edge( int u , int v , int cap , int nxt )
		: u( u ) , v( v ) , cap( cap ) , nxt( nxt ) {}
};


struct network{
	int teams , matches ;
	int played[ MAXN ][ MAXN ];
	int points[ MAXN ];
	int faltan[ MAXN ];
	int total_points;
	int e_len;
	Edge edge[ ( MAXN + MAXN * MAXN + 3 ) * 2 ];
	int head[ MAXN + MAXN * MAXN + 3 ];
	int usd[ MAXN + MAXN * MAXN + 3 ];
	int pai[ MAXN + MAXN * MAXN + 3 ];
	void clear( int t , int m ){
		memset( faltan , 0 , sizeof played );
		memset( points , 0 , sizeof played );
		teams = t;
		matches = m;
		memset( played , 0 , sizeof played );
	}
	void add_game( int u , int v , char r ){
		switch( r ){
			case '<' :
				points[ v ] += 2;
				break;
			case '>' :
				points[ u ] += 2;
				break;
			case '=' :
				points[ u ]++; points[ v ]++;
				break;
		}
		if( u > v ) swap( u , v );
		played[ u ][ v ]++;
	}
	void win_all(){ 
		repn( i , 1 , teams ){
			int quedan = matches - played[ 0 ][ i ];
			points[ 0 ] += 2 * quedan;
			played[ 0 ][ i ] = matches;
		}	
		memset( faltan , 0 , sizeof faltan );
		total_points = 0;
		rep( i , teams ) repn( j , i + 1 , teams ){
			faltan[ i ] += matches - played[ i ][ j ];
			faltan[ j ] += matches - played[ i ][ j ];
			total_points += matches - played[ i ][ j ];
		}
		total_points *= 2;
	}

	void add_edge( int u , int v , int cap ){
		edge[ e_len ] = Edge( u , v , cap , head[ u ] );
		head[ u ] = e_len++;
		edge[ e_len ] = Edge( v , u , 0 , head[ v ] );
		head[ v ] = e_len++;
	}

	int team( int v ) {
		return v;
	}

	int game( int u , int v ){ 
		return teams + u * teams + v;
	}

	int path( int s , int t ){
		memset( usd , -1 , sizeof usd );
		queue< int > q;
		q.push( s );
		usd[ s ] = oo;
		while( not q.empty() ){
			int cur = q.front(); 
			q.pop();
			if( cur == t ) break;
			for( int ptr = head[ cur ] ; ptr != -1 ; ptr = edge[ ptr ].nxt ){
				int v = edge[ ptr ].v;
				if( edge[ ptr ].cap and usd[ v ] == -1 ){
					usd[ v ] = min( edge[ ptr ].cap , usd[ cur ] );
					pai[ v ] = ptr;
					q.push( v );
				}
			}
		}
		if( usd[ t ] == -1 ) return 0;
		int id = pai[ t ];
		while( edge[ id ].u != s ){
			edge[ id ].cap -= usd[ t ];
			edge[ id ^ 1 ].cap += usd[ t ];
			id = pai[ edge[ id ].u ];
		}
		return usd[ t ];
	}

	int max_flow( int s , int t ){
		int f = 0;
		int mf = 0;
		do{
			f = path( s , t );
			mf += f;
		} while( f );
		return mf;
	}

	void make_graph(){ 
		memset( head , -1 , sizeof head );
		e_len = 0;
		rep( i , teams - 1 ){ 
			if( points[ 0 ] <= points[ i + 1 ] ) return;
			add_edge( src , team( i + 1 ) , 
					 min( max( faltan[ i + 1 ] * 2 , 0 ) , max( points[ 0 ] - 1 - points[ i + 1 ] , 0 ) ) );
		}
		rep( i , teams ) repn( j  , i + 1 , teams ){
			add_edge( team( i ) , game( i , j ) , 2 * ( matches - played[ i ][ j ] ) );
			add_edge( game( i , j ) , snk , 2 * ( matches - played[ i ][ j ] ) ); 
		}
	}
	bool absolute_winner(){ 
		
		//cout << points[ 0 ] << " " ;
		rep( i , teams - 1 ){
		//	cout << points[ i + 1 ] << " ";
			if( points[ 0 ] <= points[ i + 1 ] ) return false;
		}
		//cout << endl;
		int mf = max_flow( src , snk );	
		//cout << mf << " - " << total_points << endl;
		return mf == total_points;
	}
} net;

int N , M , G;

int main(){
	char tmp[ 3 ];
	while( scanf("%d%d%d" ,&N , &M , &G ) == 3 and
		   N + M + G ){
		net.clear( N , M );		   
		rep( i , G ){
			int u , v ;  
			scanf("%d%s%d", &u , tmp , &v );
			net.add_game( u , v , tmp[ 0 ] );
		}
		net.win_all();
		net.make_graph();
		if( net.absolute_winner() )
			printf("Y");
		else
			printf("N");
		putchar(10);
	}
	return 0;
}

