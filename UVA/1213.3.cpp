#include <cstdio>
#include <vector>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define MAXN 1124
#define PRIMEN 190
#define MAXK 15
using namespace std;

int N , K ;
int dp[ MAXN ][ MAXK ];
vector< int > prime;
int usd[ MAXN ];

void cribe( int top ) {
	usd[ 0 ] = usd[ 1 ] = 1;
	repn( i , 2 , top ) if( not usd[ i ] ){
		for( int j = i + i ; j < MAXN ; j += i )
			usd [ j ] = 1;
	}
	rep( i , top ) if( not usd[ i ] ) prime.push_back( i ) ;
}

int iterative(){
	rep( i , N + 1 ) rep( j , K + 1 ) dp[ i ][ j ] = 0;
	int prev = prime.size() ;
	dp[ N ][ 0 ] = 1;
	for( int i = prev - 1 ; i >= 0 ; i-- ){
		rep( n , N + 1 ) rep( left , K + 1 ){
			if( left != 0 and n + prime[ i ] <= N )
				dp[ n ][ left ] += dp[ n + prime[ i ] ][ left - 1 ];
		}
	}
	return dp[ 0 ][ K ];
}

int main(){
	cribe( MAXN );
	while( scanf("%d%d", &N , &K ) == 2 ){
		if( N + K == 0 ) break;
		int ans = iterative();
		printf( "%d\n" , ans );
	}
	return 0;
}

