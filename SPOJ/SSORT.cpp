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
#define MAXN 1001

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
struct node {
	int suma , len , minimo;
	bool operator < ( node x ) const {
		return minimo < x.minimo;
		return minimo * ( len - 1 ) + x.minimo * ( x.len - 1 ) >
				max( minimo , x.minimo ) + min( x.minimo , minimo ) * ( x.len + len - 1 ) + x.minimo + minimo;
	}
	void merge( node x ){
		suma += x.suma + max( x.minimo , minimo ) ;
		len += x.len ;
		minimo = min( minimo , x.minimo );
	}
	int solve(){
		return suma + minimo * ( len - 1 );
	}
	void print(){
		cout << suma << " " << len<< " " << minimo << endl;
	}
};

int data[ MAXN ];
int id[ MAXN ];
int nxt[ MAXN ];
int usd[ MAXN ];
int dp[ MAXN ];

node peso_ciclo( int v ){
	int ans = 0;
	int minimo = 1 << 30;
	int total = 0 , len = 0;
	do { 
		usd[ v ] = 1; 
		minimo = min( minimo , data[ v ] );
		total += data[ v ];
		v = nxt[ v ];
		len ++;
	} while ( usd[ v ] == 0 );
	node fin = { total - minimo , len , minimo };
	return fin;
}

vector< node > ciclo;

int f( int id ){
	if( id == ciclo.size() ) return 0;
	int & ans = dp[ id ];
	if( ans != -1 ) return ans;
	node c = ciclo[ id ];
	ans = c.solve() + f( id + 1 );
	int acum = 0;
	repn( i , id + 1 , ciclo.size() ){
		acum += c.minimo + ciclo[ i ].minimo;
		c.merge( ciclo[ i ] );
		ans = min( ans , f( i + 1 ) + c.solve() + acum );
	}
	return ans;
}

int cmp( int i , int j ){ return data[ i ] < data[ j ]; }
int main(){
	int n, tcase = 1;
	while( scanf("%d", &n ) == 1 and n  ){
		ciclo.clear();
		rep( i , n ) usd[ i ] = 0;
		rep( i , n ) dp[ i ] = -1;
		rep( i , n ) scanf("%d" , data + i );
		rep( i , n ) id[ i ] = i;
		sort( id , id + n , cmp );
		rep( i , n ) nxt[ id[ i ] ] = i;
		rep( i , n ) if( not usd[ i ] ){
			node x = peso_ciclo( i );
			ciclo.push_back( x );
		}
		sort( rall( ciclo ) );
	//	rep( i , ciclo.size() ) ciclo[ i ].print();
		int ans = 0 , j ;
		node & back = ciclo.back() , total= { -1 , -1 , -1 };
		memset( usd , 0 , sizeof usd );
		rep( i , ciclo.size() - 1 ){
			node c = ciclo[ i ];
			if( c.len * ( c.minimo - back.minimo ) - back.minimo > 3 * c.minimo ){ 
				ans += c.minimo + back.minimo;
				back.merge( c ) , usd[ i ] = 1;	
			}
		}
		rep( i , ciclo.size() ) if ( not usd[ i ] ){
			ans += ciclo[ i ].solve();
		}
		printf("Case %d: %d\n\n" ,tcase++, ans );
	}
	return 0;
}

