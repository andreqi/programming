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
#define MAXN 40010
#define MAXNO 1000004
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct segment {
	pii begin, end;
	int id;
	segment(){}
	segment( pii b , pii e , int i ) : begin( b ), end( e ) , id( i ) {}
	pii & min_point(){
		if( begin.snd < end.snd ) return begin;
		return end;
	}
	bool operator < ( segment b ) const {
		if( begin != b.begin ) return begin < b.begin;
		return end < b.end;
	}

	bool have_inter( int x ){
		return begin.fst <= x and x <= end.fst;
	}
	
	double eval( int x ){
		double dy = end.snd - begin.snd , dx = end.fst - begin.fst;
		double dxp = x - begin.fst ;
		return ( double )( begin.snd ) + ( ( dy * dxp ) / dx ); 
	}
	void print(){
		cout << begin.fst << "," << begin.snd << " : " << end.fst << "," << end.snd << endl;
	}
} seg[ MAXN ];

struct segment_set{
	int active[ 2 ][ MAXN ];
	pii eval[ MAXN ];
	int len , cur ;
	void clear(){ len = 0; cur = 0; }
	void delete_nointer( int x ){
		int j = 0;
		rep( i , len ){
			int id = active[ cur ][ i ];
			if( !seg[ id ].have_inter( x ) ) continue; 
			active[ 1 - cur ][ j++ ] = id;
		}
		len = j;
		cur = 1 - cur;
	}
	void add( int i ){
		active[ cur ][ len++ ] = i;
	}
	int get_top( int from , int to ){
		int n_len = 0;
		rep( i , len ){
			int id = active[ cur ][ i ];
			if( !seg[ id ].have_inter( from ) or !seg[ id ].have_inter( to ) ) continue;
			eval[ n_len++ ] = pii ( max( seg[ id ].eval( from ) , seg[ id ].eval( to ) ) ,
								    id ); 
		}
		if( n_len == 0 ) return -1; 
		sort( eval , eval + n_len ); 
		return seg[ eval[ n_len - 1 ].snd ].id;
	}
	
	int lower_segment( pii & p ){
		double top = p.snd , ans ;
		int id_ans = -1;
		rep( i , len ){
			int id = active[ cur ][ i ];
			double y = seg[ id ].eval( p.fst );
			if( top < y ) continue;
			if( seg[ id ].min_point() == p ) continue;
			if( id_ans == -1 or ans < y ){
				id_ans = id;
				ans = y;
			}
		}
		if( id_ans == -1 ) return -1;
		return seg[ id_ans ].id;
	}
	void print(){
		rep( i , len ) seg[ active[ cur ][ i ] ].print();
	}
} sset; // guarda los segmentos y responde consultas


int flow_to[ MAXN ];
vector< int > adj[ MAXN ];
int deg[ MAXN ];
int seen[ MAXN ];
int flow[ MAXN ] , cx_len;
int cx[ MAXN * 4 ];
pii range[ MAXN ];
set< int > buff; 
int read(){ // retorna nro de segmentos
	int n;	scanf("%d" , &n );
	buff.clear();
	int x1 , x2 , y1 , y2;
	rep( i , n ){
		scanf("%d%d%d%d" , &x1 ,&y1 , &x2 , &y2 );
		seg[ i ] = segment( pii( x1 , y1 ) , pii( x2 , y2 ) , i ); 
		range[ i ] = pii ( x1 , x2 );
		buff.insert( x1 ); buff.insert( x2 );
	}
	cx_len = 0;
	while( not buff.empty() ) cx[ cx_len++ ] = *buff.begin() , buff.erase( buff.begin() ); 
	return n;
}

pair< pii , int > evnt[ MAXN ];
int f( int v ){
	if( seen[ v ] != -1 ) return seen[ v ];
	seen[ v ] = flow[ v ];
	rep( i , adj[ v ].size() ) seen[ v ] += f( adj[ v ][ i ] );
	return seen[ v ];
}

void solve( int n ){
	rep( i , n ) flow_to[ i ] = -1;
	rep( i , n ) deg[ i ] = 0;
	rep( i , n ) seen[ i ] = 0;
	rep( i , n ) flow[ i ] = 0;
	rep( i , n ) evnt[ i ] = mp( seg[ i ].min_point() , i );
	rep( i , n ) adj[ i ].clear();
	sort( seg , seg + n );
	sort( evnt , evnt + n );
	// el evento de swep line es el punto de menor y en cada segmento
	// hacer sweep por todos los eventos
	int j = 0;
	rep( i , n ){
		pii & event = evnt[ i ].fst;
		int id = evnt[ i ].snd;
		sset.delete_nointer( event.fst );
		while( j < n and seg[ j ].have_inter( event.fst ) ){
			sset.add( j );
			j++ ;
		}
		
		flow_to[ id ] = sset.lower_segment( event );
		if( flow_to[ id ] != -1 ){
			deg[ flow_to[ id ] ]++;
			adj[ flow_to[ id ] ].push_back( id );
		}
	}
	sset.clear();
	j = 0;
	rep( i , cx_len - 1 ){
		sset.delete_nointer( cx[ i ] );
		while( j < n and seg[ j ].have_inter( cx[ i ] ) ){ sset.add( j++ ); }
		while( j < n and seg[ j ].have_inter( cx[ i + 1 ] ) ){ sset.add( j++ ); }
		int id_winner = sset.get_top( cx[ i ] , cx[ i + 1 ] );
		if( id_winner == -1 ) continue;
		flow[ id_winner ] += cx[ i + 1 ] - cx[ i ];
	}

	memset( seen , -1 , sizeof seen );
	rep( i , n ) printf("%d\n" , f( i ) );
}

int main(){
	int test;
	scanf( "%d" , &test );
	while( test-- ){
		int n = read();
		solve( n );
		if( test ) printf("\n"); 
	}
	return 0;
}

