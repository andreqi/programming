#include <string>
#include <iostream> 

using namespace std;

int main(){
	string hello;
	cin >> hello;
	string t = "hello";
	int pos = 0 ;
	for( int i = 0 ; i < hello.size() ; i ++ ){
		if( hello[ i ] == t[ pos ] ) pos++;
		if( pos == 5 ) break;
	}
	if( pos == 5 ) cout << "YES" <<endl;
	else	cout << "NO" << endl;
	return 0;
}
