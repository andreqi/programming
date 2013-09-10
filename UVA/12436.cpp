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
#define MAXN 250010
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct operation {
	char id;
	bool sum;
	int64 op , times;
	operation (){}
	void clear(){ id = '-'; op = 0; times = 1; sum = true; }
	operation( char _id , char _op ){
		id = _id;
		op = _op;
		times = 1;
		sum = _id != 'C';
	}
	void merge( operation b , int s , int e ){
		if( id == '-' or b.sum == false ){
			id = b.id , sum = b.sum , op = b.op , times = b.times;
			return;
		}
		if( b.id == 'D' ){ op += b.op; sum = sum and b.sum ; return; }
		if( b.id == 'C' ){ 
			id = 'C';
			times = 1; op = b.op; sum = false; 
			return; 
		}
		if( b.id == id ){
			times+= b.times;
			op += b.op;
			sum = sum and b.sum;
			return;
		}
		if( id == 'C' or id == 'D' ){
			times = b.times;
			op += b.op;
			id = b.id;
			sum = sum and b.sum;
		}
		else {
			sum = sum and b.sum;
			int64 t_eval = min( times , b.times );
			op +=  b.op + ( e - s + 2LL ) * t_eval ;
			times -= t_eval;
			if( times == 0LL ){ 
				b.times -= t_eval;
				if( b.times == 0LL ) id = 'D' , times = 1LL;
				else {
					times = b.times;
					id = b.id;
				} 
			}
		}
	}
};

struct node {
	int64 sum ; 
	operation o;
	node() {
		sum = 0;
		o = operation( '-' , 0 );
	}
	void add_operation( operation op , int b , int e ){ o.merge( op , b , e ); }
	bool updated(){ return o.id == '-'; }
	operation next_operation(){ operation x = o; o.clear(); return x; } 
};

struct segment_tree {
	segment_tree(){ for( int i = 0 ; i < 4 * MAXN ; i ++ ) data[ i ].sum = 0, data[ i ].o.clear(); }
	node data [ MAXN * 8 ];
	void clear() { for( int i = 0 ; i < 4 * MAXN ; i ++ ) data[ i ].sum = 0, data[ i ].o.clear(); }
	void lazy( int sb , int se , int id ){
		operation op = data[ id ].next_operation();
	//  cout << sb << " " << se << " " << op.id  << " "  << op.op <<  endl;
		bool has_children = sb != se;
		int m = (sb + se ) / 2 ;
		if( has_children ){
			data[ id * 2 ].add_operation( op , sb , m );
			data[ id * 2 + 1 ].add_operation( op , m + 1 , se );
		}
		else{
			switch( op.id ){
				case 'A': case 'B': case 'D' :
					if( op.sum )
						data[ id ].sum += op.op;
					else
						data[ id ].sum = op.op;
					if( op.id != 'D' ) data[ id ].sum += op.times; 
					break;
				case 'C':
					data[ id ].sum = op.op;
					break;
			}
	//		cout << data[ id ].sum << endl;
			return;
		}
		int64 n = se - sb + 1;
		switch( op.id ){
			case 'A': // suma i + 1 , i + 2 , i + 3 .. , i + n 
				if( op.sum )	data[ id ].sum += op.op * n;
				else			data[ id ].sum = op.op * n;
				data[ id ].sum += ( ( n * ( n + 1LL ) ) / 2LL ) * op.times ; 
				op = operation( 'D' , m - sb + 1 );
				data[ id * 2 + 1 ].add_operation( op , m + 1 , se );
				break;
			case 'B': // suma i + n , i + n - 1 , .. , i + 1
				if( op.sum )	data[ id ].sum += op.op * n;
				else			data[ id ].sum = op.op * n;
				data[ id ].sum += ( ( n * ( n + 1LL ) ) / 2LL ) * op.times; 
				op = operation( 'D' , se - ( m + 1 ) + 1 );
				data[ id * 2 ].add_operation( op , sb , m );
				break;
			case 'C': // setea todo a x
				data[ id ].sum = n * op.op;
				break;
			case 'D': // suma x , x , x  a todo
				if( op.sum )	data[ id ].sum += op.op * n;
				else			data[ id ].sum = op.op * n;
				break;
		}
	//	cout << data[ id ].sum << endl;
	}
	int64 sum( int b , int e , int id = 1 , int sb = 0 , int se = MAXN - 1 ){ 
		if( ! data[ id ].updated() )
			lazy( sb , se , id );
		if( sb > e or se < b ) return 0LL ;
		if( b <= sb and se <= e ) return data[ id ].sum;
		int m = ( sb + se ) / 2; 
		int64 l , r;
		l = sum( b , e , id * 2 , sb , m );
		r = sum( b , e , id * 2 + 1 , m + 1 , se ); 
		data[ id ].sum = data[ id * 2 ].sum + data[ id * 2 + 1 ].sum;
		return l + r;
	}
	void update( int b , int e , operation op , int id = 1 , int sb = 0 , int se = MAXN - 1 ){
		if( ! data[ id ].updated() )
			lazy( sb , se , id );
		if( e < sb or se < b ) return ;
		if( b <= sb and se <= e ){
			data[ id ].add_operation( op , sb , se );
			lazy( sb ,se , id );
			return ;
		} 
		operation lr = op , ll = op;
		int m = ( sb + se ) / 2;
		if( b <= m and m < e ){
			if( op.id == 'A' )		lr.op = m - b + 1;
			else if( op.id == 'B' )	ll.op = e - m ;
		}
		update( b , e , ll , id * 2 , sb , m );
		update( b , e , lr , id * 2 + 1 , m + 1 , se );
		data[ id ].sum = data[ id * 2 ].sum + data[ id * 2 + 1 ].sum;
	}
} tree;


bool read(){
	int test , b , e , x ;
	operation p;
	char buff[ 3 ];
	if( scanf("%d" , &test ) != 1 ) return false ;
	while( test-- ){
		scanf("%s" , buff );
		switch( buff[ 0 ] ){
			case 'A' : case 'S' : case 'B' :
				scanf("%d%d" , &b , &e );
				p = operation( buff[ 0 ] , 0 );
				if( buff[ 0 ] == 'S' ) 
					printf("%lld\n" , tree.sum( b - 1 , e - 1 ) );
				else
					tree.update( b - 1 , e - 1 , p );
				break;
			case 'C' :
				scanf("%d%d%d" , &b , &e , &x );
				p = operation( buff[ 0 ] , x );
				tree.update( b - 1 , e - 1 , p );
				break;
		}
	//	cout << "end" << endl;
	}
	return true;
}

int main(){
	while( read() ){
	}
	return 0;
}

