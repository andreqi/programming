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
#define MAXN 40011
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct point_seg{
	int id , is_lower , is_ini;
	pii p;
	point_seg(){}
	point_seg( int id , int is_lower , pii p ): id( id ) , is_lower( is_lower ) , p( p ) {}
	bool operator < ( point_seg b ) const {
		if( b.p.fst != p.fst ) return p.fst < b.p.fst;
		if( is_ini != b.is_ini ) return is_ini > b.is_ini;
		if( is_ini ) return p.snd < b.p.snd;
		return p.snd > b.p.snd;
	}
};

struct segment{
	point_seg a , b;
	int id;
	segment(){}
	segment( point_seg a , point_seg b , int id ) : a( a ) ,b ( b ) , id( id ) {}
	double eval( int x ){
		if( x == a.p.fst ) return a.p.snd;
		if( x == b.p.fst ) return b.p.snd;
		double dx = b.p.fst - a.p.fst , dy = b.p.snd - a.p.snd;
		double dp = x - b.p.fst;
		return ( double )b.p.snd + ( dp * dy ) / dx;
	}
	void print(){
		printf("(%d, %d) - - - (%d, %d) id: %d\n" , a.p.fst , a.p.snd , b.p.fst , b.p.snd , id );
	}
} seg[ MAXN ] ;

struct events{
	vector< segment > data;
	void insert( segment a ){
		data.push_back( a );
	}
	void remove( segment b ){
		vector< segment > new_data;
		rep( i , data.size() ) if( b.id != data[ i ].id ) 
			new_data.push_back( data[ i ] );
		data = new_data;
	}
	int get_low( pii point , int id_p ){
		double d_ans ; int id = -1 ;
		rep( i , data.size() ){
			double eval = data[ i ].eval( point.fst );
			if( eval > ( double ) point.snd ) continue;
			if( data[ i ].id == id_p ) continue;
			if( id == -1 or d_ans < eval ){
				d_ans = eval;
				id = data[ i ].id;
			}
		}
		return id;
	}
	int get_top( int x1 , int x2 ){
		double d_ans = -1;
		int id = -1;
		rep( i , data.size() ){
			double eval = data[ i ].eval( x1 );
			if( id == -1 or d_ans < eval ){
				d_ans = eval;
				id = data[ i ].id;
			}
		}
		return id;
	}
} active_area;

point_seg order[ MAXN * 2 ];
vector< int > adj[ MAXN ];
int seen[ MAXN ] , flow[ MAXN ];

int read(){
	int n; scanf("%d" ,&n );
	int x1 , x2 , y1 , y2;
	rep( i , n ) adj[ i ].clear();
	memset( seen , -1 , sizeof seen );
	memset( flow , 0 , sizeof flow );
	rep( i , n ){
		scanf("%d%d%d%d" , &x1 , &y1 , &x2 , &y2 );
		point_seg a = point_seg( i , y1 < y2 , pii( x1 , y1 ) );
		a.is_ini = 1;
		point_seg b = point_seg( i , y1 > y2 , pii( x2 , y2 ) );
		b.is_ini = 0;
		seg[ i ] = segment( a , b , i );
		order[ 2 * i ] = a;
		order[ 2 * i + 1 ] = b;
	}
	return n;
}

int f( int v ){
	if( seen[ v ] != -1 ) return seen[ v ];
	seen[ v ] = flow[ v ]; 
	rep( i , adj[ v ].size() ) seen[ v ] += f( adj[ v ][ i ] );
	return seen[ v ];
}
void solve( int n ) {
	sort( order , order + n * 2 );
	rep( i , n * 2 ){
		point_seg & p = order[ i ];
		//cout << p.p.fst << "." << p.p.snd << endl;
		//seg[ p.id ].print();
		if( p.is_lower ){
			int next = active_area.get_low( p.p , p.id	);
			//cout << next << endl;
			adj[ next + 1 ].push_back( p.id + 1 );
		}
		if( i ){
			int dx = order[ i ].p.fst - order[ i - 1 ].p.fst ;
			if( dx ){ 
				int top = active_area.get_top( order[ i ].p.fst , order[ i - 1 ].p.fst );
			//	cout << "winner "<< top << " " << dx << endl;
				flow[ top + 1 ] += dx;
			}
		}
		if( p.is_ini )	active_area.insert( seg[ p.id ] );
		else			active_area.remove( seg[ p.id ] );
	}
	rep( i , n )	printf("%d\n" , f( i + 1 ) );
}

int main(){
	int test;
	scanf("%d" , & test );
	while ( test-- ){
		int n = read();
		solve( n );
		if( test ) printf("\n");
	}
	return 0;
}

