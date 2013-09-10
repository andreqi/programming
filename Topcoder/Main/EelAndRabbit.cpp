// BEGIN CUT HERE

// END CUT HERE
#line 5 "EelAndRabbit.cpp"
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

bool in(pair<int64,int64> x , int64 timer){
	return x.fst <= timer and timer <= x.snd;
}

class EelAndRabbit {
	public:
	int getmax(vector <int> l, vector <int> t) {
		vector< pair<int64, int64> > seg;
		set <int64> val;
		int64 T = 0;
		rep (i, l.size()) T = max(T, (int64)max((int64)t[i],(int64)t[i] + (int64)l[i]));
		rep (i, l.size()) {
			int64 head = T - (int64)t[i];
			int64 tail = T - (int64)t[i] - (int64)l[i];
			seg.push_back(mp(tail,head));
			val.insert(head);
			val.insert(tail);
		}
		vector <int64> idx = vector<int64> (all(val));
		int maxi = 0;
		rep (i, idx.size()){
			repn(j, i, idx.size()){
				int ans = 0;
				rep (k, seg.size()){
					if (in(seg[k],idx[i]) or in(seg[k],idx[j])) ans++;
				}
				maxi = max(maxi, ans);
			}
		}
		cout << endl;
		return maxi;
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
			int l[]                   = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000};
			int t[]                   = {2, 6, 3, 7, 0, 1000000000, 1000000000};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int l[]                   = {1, 1, 1};
			int t[]                   = {2, 0, 4};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int l[]                   = {1};
			int t[]                   = {1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int l[]                   = {8, 2, 1, 10, 8, 6, 3, 1, 2, 5};
			int t[]                   = {17, 27, 26, 11, 1, 27, 23, 12, 11, 13};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
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

