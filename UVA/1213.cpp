#include <cstdio>
#include <vector>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define MAXN 1124
#define PRIMEN 190
#define MAXK 15
using namespace std;

int N , K ;
int dp[ MAXK ][ MAXN ];
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
	int prev = prime.size() - 1 ;
	while( prev >= 0 and prime[ prev ] > N ) prev--;
	prev++;
	rep( j , K + 1 ) rep( i , N + 1 ) dp[ j ][ i ] = 0;
	dp[ 0 ][ N ] = 1;
	for( int i = prev - 1 ; i >= 0 ; i-- ){
		rep( n , N + 1 ) rep( left , K + 1 ){
			if( left != 0 and n + prime[ i ] <= N )
				dp[ left ][ n ] += dp[ left - 1 ][ n + prime[ i ] ];
		}
	}
	return dp[ K ][ 0 ];
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

