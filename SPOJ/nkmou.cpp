#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#define rep( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i++ )
#define all( x ) x.begin(), x.end()

using namespace std;

#define MAXN 600010 

typedef int int64;
struct tree{
	vector< int64 > real_cord;
	int64 maxn[ MAXN * 4 ];
	int64 sum[ MAXN * 4 ];
	int64 value[ MAXN * 4 ];
	int lazy[ MAXN * 4 ];
	void clear( int n ){
		int top = n * 4;
		rep ( i , 0 , top ) maxn[ i ] = 0;
		rep ( i , 0 , top ) sum[ i ] = 0;
		rep ( i , 0 , top ) lazy[ i ] = 0;
		rep ( i , 0 , top ) value[ i ] = 0;
	}

	void lupdate( int b , int e ,int id ){
		//cout << b << " " << e << endl;
		int64 push = value[ id ];
		lazy[ id ] = 0;
		if( b != e ){
			value[ id << 1 ] = push;
			value[ ( id << 1 ) + 1 ] = push;
			lazy[ id << 1 ] = 1;
			lazy[ ( id << 1 ) + 1 ] = 1;
		}
		int64 ini = real_cord[ b - 1 ] + 1 , fin = real_cord[ e ];
		maxn[ id ] = sum[ id ] = push * ( fin - ini + 1 );
		maxn[ id ] = max( maxn[ id ] , 0 );
	}

	void update( int ini , int fin , int b , int e , int64 data , int id ){
		if( lazy[ id ] ) lupdate( b , e , id );
		if( fin < b or ini > e ) return;
		if( ini <= b and e <= fin ){
			value[ id ] = data;
			lupdate( b , e , id );
			return;
		}
		int mid = ( b + e ) >> 1;
		update( ini , fin , b , mid , data , ( id << 1 ) );
		update( ini , fin , mid + 1 , e , data , ( id << 1 ) + 1 );
		sum[ id ] = sum[ id << 1 ] + sum[ ( id << 1 ) + 1 ];
		maxn[ id ] = max( maxn[ id << 1 ] , maxn[ ( id << 1 ) + 1 ] + sum[ id << 1 ] );
		maxn[ id ] = max( maxn[ id ] , 0 );
	}

	int64 size( int b , int e ){ return real_cord[ e ] - real_cord[ b - 1 ];  }


	//TODO : tiene que darte la suma de segmentos, no la ultima coordenada
	int64 query( int b , int e , int64 target , int id ){
		if( lazy[ id ] ) lupdate( b , e , id ); 
		//cout << "query " << b <<  " "  << e << endl;
		//cout << sum[ id ] << " " << target << " " << maxn[ id ] << endl;
	
		if( maxn[ id ] <= target ){
			//cout << real_cord[ e ] << " " << real_cord[ b ] << endl;
			return size( b , e );
		} 
		if( b == e ){
			int64 len = size( b , e );
			int64 di = sum[ id ] / len;
			//cout << sum[ id ] << " " << target << " " << maxn[ id ] << " " << di << endl;
			if( target < di ) return 0;
			//cout << di << endl;
			if( di <= 0 ) return len;
			int64 ans = target / di;
			return max( ans , 0 );
		}

		int mid = ( b + e ) >> 1;
		if( lazy[ id << 1 ] )	lupdate( b , mid , id << 1 );
		int64 ans = 0 ;
		if( maxn[ id << 1 ] > target ) ans = query( b , mid , target , ( id << 1 ) );
		else ans = query( mid + 1 , e , target - sum[ id << 1 ] , ( id << 1 ) + 1 ) + size( b , mid ) ;
		if( lazy[ id << 1 ] )	lupdate( b , mid , id << 1 );
		if( lazy[ ( id << 1 ) + 1  ] )	lupdate( mid + 1 , e , ( id << 1 ) + 1 );

		sum[ id ] = sum[ id << 1 ] + sum[ ( id << 1 ) + 1 ];
		maxn[ id ] = max( maxn[ id << 1 ] , maxn[ ( id << 1 ) + 1 ] + sum[ id << 1 ] );
		maxn[ id ] = max( maxn[ id ] , 0 );
		//cout << "mid " << real_cord[ mid] << endl;
		//cout << b << " " << e << " = " << ans << endl;
		return ans;
	}

} seg_tree;

char c[ MAXN ];
int64 a[ MAXN ] , b[ MAXN ] , d[ MAXN ];
vector< int64 > & cord = seg_tree.real_cord;
char buff[ 3 ];
int main(){
	int n, len = 0 ;  
	scanf("%d" , &n );
	int64 nn = n;
	while( scanf("%s" , buff ) and buff[ 0 ] != 'E' ){
		c[ len ] = buff[ 0 ] == 'I';
		if( c[ len ] ){
			scanf("%d%d%d" , a + len, b + len , d + len );
			for( int i = -1 ; i<= 1 ; i++ ){
				if( a[ len ] + i > 0 and a[ len ] + i <= nn )
					cord.push_back( a[ len ] + i );
				if( b[ len ] + i > 0 and b[ len ] + i <= nn ) 
					cord.push_back( b[ len ] + i );
			}
		} else  
			scanf("%d" , a + len );
		len++;
	}
	cord.push_back( 0 );
	cord.push_back( 1 );
	cord.push_back( ( int64 ) n );
	sort( all( cord ) );
	cord.resize( unique( all( cord ) ) - cord.begin() );
	n = cord.size();
	seg_tree.clear( n );
	rep( i , 0 , len ) if( c[ i ] ) 
		a[ i ] = lower_bound( all( seg_tree.real_cord ) , a[ i ] ) - seg_tree.real_cord.begin();
	rep( i , 0 , len ) if( c[ i ] )
		b[ i ] = lower_bound( all( seg_tree.real_cord ) , b[ i ] ) - seg_tree.real_cord.begin();
	rep( i , 0 , len ){
		if( c[ i ] ){
			seg_tree.update( a[ i ] , b[ i ] , 1 , n - 1 , d[ i ] , 1 );
		} else {
			 printf("%d\n", seg_tree.query( 1 , n - 1 , a[ i ] , 1 ) );
		}
	}
	return 0;
}
