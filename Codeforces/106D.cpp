/*

@Tema : DP
@Lvl  : medium
@Complexity : O( n * n * k )
@Idea : precalculate the matching bracket

*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 800
#define MOD 1000000007
using namespace std;

typedef long long Int;
Int dp[ MAXN ][ MAXN ][ 4 ][ 4 ];
char buff[ MAXN ];
int nxt[ MAXN ];
int len;
Int sum( Int a , Int b ){
	return ( a % MOD + b % MOD ) % MOD;
}

Int mult( Int a , Int b ) {
	return ( sum( a , 0 ) * sum ( b , 0 ) ) % MOD ;
}

Int f( int bgn , int end , int banB , int banE ){
//	printf( "%d : %d : %d : %d | %d\n" , bgn , end , banB , banE , -1 );
	Int & ans = dp[ bgn ][ end ][ banB ][ banE ];
	if( ans != -1 ) return ans;
	if( bgn > end ) return ans = 0;
	if( bgn == end - 1 ){
		if( banB == banE and banB == 0 ) return ans = 4;
		if( banB == 0 or banE == 0 ) return ans =  3;
		return ans = 2;
	}
	bool hasNext = end != nxt[ bgn ];
	bool single = nxt[ bgn ] == bgn + 1;
	int next = nxt[ bgn ]; 
	// Don't paint any bracket
	ans = 0;
	for ( int color = 1 ; color < 3 ; color ++ ){
		// Paint the first bracket
		ans =  banB == color ? ans : 
				sum ( ans ,
					mult ( 
						single ? 1 : f( bgn + 1 , next - 1 , color , 0 ) , 
						hasNext ? f( next + 1 , end , 0 , banE ) : 1 
						)
				);
		// Paint the second bracket
		ans =  !hasNext and ( banE == color ) ? ans : 
				sum ( ans , 
					mult ( 
						single ? 1 : f( bgn + 1 , next - 1 , 0 , color ) ,
						hasNext ? f( next + 1 , end , color , banE ) : 1 
						)
				);
	}
//	printf( "%d : %d : %d : %d | %d\n" , bgn , end , banB , banE , ans );
	return ans;
}

int solve(){
	memset( nxt , -1 , sizeof nxt );
	for( int i = 0 , j , lvl ; buff[ i ] ; i ++ ) if( buff[ i ] == '(' ) {
		for ( j = i + 1 , lvl = 1 ; lvl ; ++j ){ 
			lvl += buff[ j ] == '(' ? 1 : -1 ;
			if( lvl == 0 ) break;
		}
		nxt[ i ] = j;
	}
	memset( dp , -1 , sizeof dp );
	return f( 0 , len - 1 , 0 , 0 ); 
}

int main(){
	scanf("%s", buff );
	int lvl = 0;
	len = strlen( buff );
	for( int i = 0 ; buff[ i ] ; i++ ){
		lvl += buff[ i ] == '(' ? 1 : -1 ;
		if( lvl < 0 ) break;
	}
	if( lvl < 0 ) printf( "0\n" );
	else{
		Int ans = solve();
		cout << ans << endl;
	}
	return 0;
}
