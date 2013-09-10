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
#define MOD 5000000

#define MAXN 10011
int sum[ MAXN * 4 ][ 51 ];

int suma( int a , int b = 0 ){
	return ( a % MOD + b % MOD ) % MOD;
}

struct segtree{

	int query( int upper , int k , int b , int e , int id ){
		if( e < upper ) return suma( sum[ id ][ k ] );
		if( upper <= b ) return 0;
		int mid = ( b + e ) >> 1;
		int l = id << 1 ; int r = l + 1;
		int ans_l = query( upper , k , b , mid , l );
		int ans_r = query( upper , k , mid + 1 , e , r );
		return suma( ans_l , ans_r );
	}

	void update( int key , int pos , int value , int b , int e , int id ){
		if( key < b ) return ;
		if( e < key ) return ;
		if( b == e ){
			sum[ id ][ pos ] = suma( sum[ id ][ pos ] , value );
			return;
		}
		int mid = ( b + e ) >> 1;
		int l = id << 1 ; int r = l + 1;
		update( key , pos , value , b , mid , l );
		update( key , pos , value , mid + 1 , e , r );
		sum[ id ][ pos ] = suma( sum[ l ][ pos ] , sum[ r ][ pos ] );
	}

} tree;

set< int > sset;
vector< int > posi;
int data[ MAXN ];

int main(){
	int n , k ;
	int total_k = 0;
	scanf("%d%d", &n , &k );
	rep( i , n ) scanf("%d" , data + i ); 
	rep( i , n ) sset.insert( data[ i ] );
	posi = vector< int > ( all( sset ) );
	rep( i , n ) data[ i ] = lower_bound( all( posi ) , data[ i ] ) - posi.begin();
	int top = posi.size();
	rep( i , n ){
		int x = data[ i ]; 
		int last = 1;
		tree.update( x , 0 , 1 , 0 , top - 1 , 1 );
		repn( j , 1 , k ){
			int ans = tree.query( x , j - 1 , 0 , top - 1 , 1 );
			tree.update( x , j , ans , 0 , top - 1 , 1 );
			last = ans;
		}
		total_k = suma( total_k , last );
	} 
	printf("%d\n", total_k );
	return 0;
}

