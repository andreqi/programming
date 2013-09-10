#include <cstdio>
#include <algorithm>

using namespace std;

int participants , budget , hotels , weeks;

const int oo = 1<<28;

void solve(){
	int ans = oo;
	for( int i = 0 ; i < hotels ; i++ ){
		int price_person ; scanf( "%d" , &price_person );
		for( int j = 0 ; j < weeks ; j++ ){
			int rooms ; scanf( "%d" , &rooms );
			if( rooms < participants ) continue;
			int cost = participants * price_person;
			ans = min( ans  , cost );
		}
	}
	if( ans > budget )	printf("stay home\n"); 
	else				printf("%d\n" , ans );
}

bool read(){
	int op = scanf( "%d" , & participants );
	if( op != 1 ) 	return false;
	scanf("%d%d%d" , &budget , &hotels , &weeks );
	return true;
}
int main(){
	while( read() ){
		solve();
	}
	return 0;
}
