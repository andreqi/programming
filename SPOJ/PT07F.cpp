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
#define MAXN 10010
#define oo ( 1 << 28 )
vector< int > adj[ MAXN ];
int padre[ MAXN ];
vector< int > recover[ MAXN ][ 2 ];
int dp[ MAXN ][ 2 ];

int path( int , int );

void dfs( int v ,int pai ){
	//cout << v << " " << pai << endl;
	padre[ v ] = pai;
	rep( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( pai == u ) continue;
		dfs( u , v );
	}
}

int inicio( int v , int pai ){
	int & ans = dp[ v ][ 0 ];
	if( ans != -1 ) return ans;
	int suma_inicio = 0 ;
	rep( i , adj[ v ].size() ) {
		int u = adj[ v ][ i ];
		if( u == pai ) continue;
		suma_inicio += inicio( u , v );
	}
	
	// solo
	int solo = suma_inicio;
	pii fa ( oo , -1 ), fb ( oo , -1 ) ;
	// sacar los 2 minimos
	rep( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( u == pai ) continue;
		pii nxt ( -inicio( u ,  v ) + path( u , v ) , u );
		if( nxt < fa ){
			fb = fa ;
			fa = nxt;
		} else if ( nxt < fb ){ 
			fb = nxt;
		}
	}
	// no tiene ramas
	int una_rama = suma_inicio + fa.fst;	
	if( fa.fst == fb.fst and fa.fst == oo ){
		una_rama = oo;
	}
	// 1 rama
	int dos_ramas = suma_inicio + fa.fst + fb.fst ;
	if( fb.fst == oo ){
		dos_ramas = oo;
	}
	ans = min( solo , min( dos_ramas , una_rama ) );
	if( ans == solo ){
		recover[ v ][ 0 ].push_back( 0 );
	} else if( ans == una_rama ) {
		recover[ v ][ 0 ].push_back( 1 );
		recover[ v ][ 0 ].push_back( fa.snd );
	} else {
		recover[ v ][ 0 ].push_back( 2 );
		recover[ v ][ 0 ].push_back( fa.snd );
		recover[ v ][ 0 ].push_back( fb.snd );
	}
	ans++;
	return ans ;
}

int path( int v , int pai ){
	int & ans = dp[ v ][ 1 ];
	if( ans != -1 ) return ans;
	int termina = 0 , sigue = oo;
	int suma_inicio = 0;
	rep( i , adj[ v ].size() ) {
		int u = adj[ v ][ i ];
		if( u == pai ) continue;
		suma_inicio += inicio( u , v );
	}
	termina = suma_inicio;
	int id = -1 ;
	rep( i , adj[ v ].size() ) { 
		int u = adj[ v ][ i ];
		if( u == pai ) continue;
		int eval_i = suma_inicio - inicio( u , v ) + path( u , v ) ;
		if( eval_i < sigue ){
			sigue = eval_i;
			id = u;
		}
	}
	if( sigue < termina ){
		recover[ v ][ 1 ].push_back( 1 );
		recover[ v ][ 1 ].push_back( id );
	} else {
		recover[ v ][ 1 ].push_back( 0 );
	}
	return ans = min( sigue , termina );
}

vector< int > rec_path[ MAXN ];
queue< int > espera;
int seen[ MAXN ];
int cache[ MAXN ];
int p_cnt = 0 , len = 0 ;

void dfs_path( int , int );
void dfs_inicio ( int v , int pai ){
	int type = recover[ v ][ 0 ][ 0 ];
//	cout << "dfs_inicio " << type << " " << v << endl;
//	cout << inicio( v , pai ) << endl;
	seen[ v ] = true;
	if( type == 0 ){
		rec_path[ p_cnt++ ].push_back( v ) ;
		rep( i , adj[ v ].size() ){
			int u = adj[ v ][ i ];
			if( u == pai ) continue;
			dfs_inicio( u , v );
		}
	} else if( type == 1 ){
		int chosen = recover[ v ][ 0 ][ 1 ];
		seen[ chosen ] = true;
		len = 0 ;
		dfs_path( chosen , v );
		while( len-- ){
			rec_path[ p_cnt ].push_back( cache[ len ] );
		}
		rec_path[ p_cnt++ ].push_back( v );
		rep( i , adj[ v ].size() ){
			int u = adj[ v ][ i ];
			if( u == pai ) continue;
			if( seen[ u ] ) continue;
			espera.push( u );
		}
		while( !espera.empty() ) {
			int x = espera.front() ; espera.pop();
			if( seen[ x ] ) continue;
			dfs_inicio( x , padre[ x ] );
		}
	} else {
		int chosen = recover[ v ][ 0 ][ 1 ];
		//cout << ". "<< chosen << endl;
		seen[ chosen ] = true;
		len = 0;
		dfs_path( chosen , v );
		while( len-- ){
			rec_path[ p_cnt ].push_back( cache[ len ] );
		}
		rec_path[ p_cnt ].push_back( v );

		chosen = recover[ v ][ 0 ][ 2 ];
		//cout << ". "<< chosen << endl;
		seen[ chosen ] = true;
		len = 0;
		dfs_path( chosen , v );
		rep( i , len ) rec_path[ p_cnt ].push_back( cache[ i ] );
		p_cnt++;
		rep( i , adj[ v ].size() ){
			int u = adj[ v ][ i ];
			if( u == pai ) continue;
			if( seen[ u ] ) continue;
			espera.push( u );
		}
		while( !espera.empty() ) {
			int x = espera.front() ; espera.pop();
			if( seen[ x ] ) continue;
			dfs_inicio( x , padre[ x ] );
		}
	}
}

void dfs_path( int v , int pai ){
	//cout << v << " " << pai << endl;
	seen[ v ] = true;
	cache[ len++ ] = v;
	int nxt = -1;
	if( !recover[ v ][ 1 ][ 0 ] ) {}
	else nxt = recover[ v ][ 1 ][ 1 ];
	rep( i , adj[ v ].size() ){
		int u = adj[ v ][ i ];
		if( u == pai or u == nxt ) continue;
		espera.push( u );
	}
	if( nxt != -1 ) dfs_path( nxt , v );
}

void solve( int n ){
	int caminos = inicio( 0 , -1 );
	printf("%d\n" , caminos );
	p_cnt = 0;
	dfs_inicio( 0  , - 1 );
	//cout << p_cnt << endl;
	rep( i , p_cnt ){
		printf("%d" , rec_path[ i ][ 0 ] + 1 );
		rep( j , rec_path[ i ].size() - 1 ) printf(" %d", rec_path[ i ][ j + 1 ] + 1 );
		printf("\n");
	}
}

int main(){
	int test;
	scanf("%d", &test );
	while( test-- ){
		int n , u , v ;
		scanf("%d" , &n ) ;
		rep( i , n ) rec_path[ i ].clear();
		rep( i , n ) seen[ i ] = 0;
		rep( i , n ) adj[ i ].clear();
		rep( i , n - 1 ){
			scanf("%d%d", &u , &v );
			u--, v--;
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
		}
		dfs( 0 , -1 );
		rep( i , n ) dp[ i ][ 0 ] = dp[ i ][ 1 ] = -1; 
		rep( i , n ) rep( j , 2 ) recover[ i ][ j ].clear();
		solve( n );
	}
	return 0;
}

