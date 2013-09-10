// BEGIN CUT HERE

// END CUT HERE
#line 5 "ShoutterDiv1.cpp"
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

class ShoutterDiv1 {
	public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
		
	}
};


// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string s1000[]            = {"22", "2"};
			string s100[]             = {"00", "0"};
			string s10[]              = {"11", "1"};
			string s1[]               = {"21", "4"};
			string t1000[]            = {"22", "2"};
			string t100[]             = {"00", "0"};
			string t10[]              = {"11", "1"};
			string t1[]               = {"43", "6"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s1000[]            = {"00"};
			string s100[]             = {"00"};
			string s10[]              = {"00"};
			string s1[]               = {"13"};
			string t1000[]            = {"00"};
			string t100[]             = {"00"};
			string t10[]              = {"00"};
			string t1[]               = {"24"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s1000[]            = {"0000"};
			string s100[]             = {"0000"};
			string s10[]              = {"0000"};
			string s1[]               = {"1234"};
			string t1000[]            = {"0000"};
			string t100[]             = {"0000"};
			string t10[]              = {"0000"};
			string t1[]               = {"2345"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s1000[]            = {"0000000000"};
			string s100[]             = {"0000000000"};
			string s10[]              = {"0000000000"};
			string s1[]               = {"7626463146"};
			string t1000[]            = {"0000000000"};
			string t100[]             = {"0000000000"};
			string t10[]              = {"0000000000"};
			string t1[]               = {"9927686479"};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string s100[]             = {"00000000000000000000000000000000000000000000000000"};
			string s10[]              = {"50353624751857130208544645495168271486083954769538"};
			string s1[]               = {"85748487990028258641117783760944852941545064635928"};
			string t1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string t100[]             = {"00000000000000000000000000000000000000000000000000"};
			string t10[]              = {"61465744851859252308555855596388482696094965779649"};
			string t1[]               = {"37620749792666153778227385275518278477865684777411"};
			int expected__            = 333;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE

