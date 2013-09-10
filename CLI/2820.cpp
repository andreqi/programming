#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , a ) repn( i , 0 , a )
#define MAXN 510

using namespace std;

char X[ MAXN ];
char Y[ MAXN ];
int dp[ MAXN ][ MAXN ][ 3 ] , str_x , str_y;
bool vi[ MAXN ][ MAXN ][ 3 ];
const int oo = 1<<28;

int delta( int i , int j ){
	return X[ i ] == Y[ j ] ? 2 : -1 ;
}
struct node{
	int a , b;
	int getshit(){
		a = 1 , b = 2;
	}
};

int max_value( int i , int j , int op ){
	if( vi[ i ][ j ][ op ] ) 	return dp[ i ][ j ][ op ];
	if( !X[ i ] and !Y[ j ] ) 	return 0;
	vi[ i ][ j ][ op ] = true;
	int & ans = dp[ i ][ j ][ op ];
	if( op == 0 ){
		vector< int > candidate;
		if( X[ i ] and Y[ j ] ){
			candidate.push_back( max_value( i + 1 , j + 1 , 0 ) + delta( i , j ) ); 
			candidate.push_back( max_value( i + 1 , j , 2 ) - 5 );
			candidate.push_back( max_value( i , j + 1 , 1 ) - 5 );
		}
		else if( X[ i ] )
			return ans = - 4 - ( str_x - i );
		else if( Y[ j ] )
			return ans = - 4 - ( str_y - j );
		ans = *max_element( candidate.begin() , candidate.end() );
	}
	else{
		ans = max_value( i , j , 0 );
		int keep = -oo ;
		if( op == 2 and X[ i ] )
			keep = max_value( i + 1 , j , 2 ) - 1 ;
		if( op == 1 and Y[ j ] )
			keep = max_value( i , j + 1 , 1 ) - 1 ;
		ans = max( ans , keep );
	}
	return ans;
}


int main(){
	int test ; 
	scanf( "%d\n" , &test );
	rep( times , test ){
		gets( X ); str_x = strlen( X );
		gets( Y ); str_y = strlen( Y );
		memset( vi , 0 , sizeof vi );
		printf("%d\n", max_value( 0 , 0 , 0 ) );
	}
	return 0;
}

