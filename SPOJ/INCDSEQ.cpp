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
#define MAXN 10010

int sum[ MAXN * 4 ][ 51 ];
int suma( int a , int b = 0 ){
	return ( a % MOD + b % MOD + MOD ) % MOD;
}

struct segment{
	int query( int ini , int fin , int k , int b , int e , int id ){
		if( ini > fin ) return 0;
		if( fin < b or ini > e ) return 0;
		if( ini <= b and e <= fin ) return sum[ id ][ k ];
		int mid = ( b + e ) / 2;
		int le = id + id ; int ri = le + 1 ;
		int ansle = query( ini , fin , k , b , mid , le );
		int ansri = query( ini , fin , k , mid + 1 , e , ri );
		return suma( ansle , ansri );
	}
	void update( int idx , int valx , int k , int b , int e , int id ){
		if( idx < b or idx > e ) return ;
		if( b == e ){
			sum[ id ][ k ] = suma( valx );
			return;
		}
		int mid = ( b + e ) / 2;
		int le = id + id ; int ri = le + 1 ;
		update( idx , valx , k , b , mid , le );
		update( idx , valx , k , mid + 1 , e , ri );
		sum[ id ][ k ] = suma( sum[ le ][ k ] , sum[ ri ][ k ] );
	}
} tree;

vector< int > val;
vector< int > data;
map< int , int > renew;

int main(){
	int n , k;
	scanf("%d%d" , &n , &k );
	val.resize( n );
	rep( i , n ) scanf("%d" , &val[ i ] );
	data = val;
	sort( all( val ) );
	val.resize( unique( all( val ) ) - val.begin() );
	rep( i , val.size() ) renew[ val[ i ] ] = i; 
	rep( i , n ) data[ i ] = renew[ data[ i ] ];
	int tope = val.size() , key , tmp;
	rep( i , n ){
		key = data[ i ];
		tree.update( key , 1 , 0 , 0 , tope , 1 );
		repn ( j , 1 , k ) {
			tmp = tree.query( 0 , key - 1 , j - 1 , 0 , tope , 1 );
			tree.update( key , tmp , j , 0 , tope , 1 );
		}
	}
	int ans = tree.query( 0 , tope , k - 1 , 0 , tope , 1 );
	printf("%d\n" , ans ) ;
	return 0;
}

