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

const int MAXN = 50011;
const int oo = 1 << 20;

struct tree {
	int mini[ MAXN * 4 ];
	int data[ MAXN * 4 ];
	int lazy[ MAXN * 4 ];
	void clear( int b , int e , int id = 1 ){
		mini[ id ] = data[ id ] = lazy[ id ] = oo ;
		if( b == e ) return ;
		int mid = ( b + e ) / 2;
		clear( b , mid , id * 2 );
		clear( mid + 1 , e , id * 2 + 1 );
	}

	void lazy_prop( int b , int e , int id ){
		if( b != e ){
			int l = id * 2 , r = id * 2 + 1;
		//	lazy[ l ] = lazy[ r ] = lazy[ id ];
		lazy[ l ] = lazy[ l ] == -1 ? lazy[ id ] : min( lazy[ id ] , lazy[ l ] );
		lazy[ r ] = lazy[ r ] == -1 ? lazy[ id ] : min( lazy[ id ] , lazy[ r ] );
		} 
		
		mini[ id ] = min( lazy[ id ], mini[ id ] );
	//	mini[ id ] = data[ id ] = lazy[ id ];
		lazy[ id ] = -1;
	}

	void update( int b , int e , int q_b , int q_e , int val , int id = 1 ){
		if( lazy[ id ] != -1 ) lazy_prop( b , e , id );
		if( q_e < b or q_b > e ) return ;
		if( q_b <= b and e <= q_e ){
			lazy[ id ] = val;
			lazy_prop( b , e , id );
			return;
		}
		if( b == e ) return;
		int mid = ( b + e ) / 2;
		int l = id * 2 , r = id * 2 + 1;
		update( b , mid , q_b , q_e , val ,  l );
		update( mid + 1 , e , q_b , q_e , val ,  r );
		mini[ id ] = min( mini[ l ] , mini[ r ] );
	}

	int query( int b , int e , int q_b , int q_e , int id = 1 ){
		if( lazy[ id ] != -1 ) lazy_prop( b , e , id );
		if( q_e < b or q_b > e ) return oo;
		if( q_b <= b and e <= q_e ) return mini[ id ];
		int mid = ( b + e ) / 2;
		int l = id * 2 , r = id * 2 + 1;
		int ans_l = query( b , mid , q_b , q_e , l );
		int ans_r = query( mid + 1 , e , q_b , q_e , r );
		mini[ id ] = min( mini[ l ] , mini[ r ] );
		return min( ans_l , ans_r );
	}

	int query_id( int b , int e , int x , int id = 1 ){
		if( lazy[ id ] != -1 ) lazy_prop( b , e , id );
		if( b == e ) return mini[ id ];
		int mid = ( b + e ) / 2;
		int l = id * 2 , r = id * 2 + 1;
		int ans = 0;
		if( x < mid ) ans = query_id( b , mid , x , l );
		else		  ans = query_id( mid + 1 , e , x , r );
		mini[ id ] = min( mini[ l ] , mini[ r ] ); 
		return ans;
	}

} seg_tree;

int main(){
	int test;
	scanf("%d", & test );
	while( test-- ){
		int n , m;
		scanf( "%d%d", &n , &m );
	//	cout << n << " " << m << endl;
		seg_tree.clear( 0 , n - 1 );
	//	cout << "sale " << endl;
		while( m-- ){ 
			int ini , fin;
			scanf("%d%d" , &ini , &fin );
			ini-- , fin --;
	//		cout << ini << " " << fin << endl;
			int mini = 0;
			if( ini != 0 ) mini = seg_tree.query( 0 , n - 1 , ini , fin );
			mini++;
	//		cout << mini << endl;
			seg_tree.update( 0 , n -1 , ini , fin , mini );
		}
		printf("%d\n", seg_tree.query_id( 0 , n - 1 , n - 1 ) );
	}
	return 0;
}

