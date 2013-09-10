// BEGIN CUT HERE

// END CUT HERE
#line 5 "InfiniteSoup.cpp"
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
#define clr(x,y) memset(x, (y), sizeof x);
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct Aho {
    static const int CHARSET = 'z' - 'a' + 1;
    static const int NODES = 50 * 30;
    int trie[NODES][CHARSET];
    int tag[NODES];
    int q[NODES];
    int fail[NODES];
    int end;
    void init(){
        end = 1;
        clr(trie[0], -1);
        tag[0] = 0;
    }
    void add(string & str, int id){
        int p = 0;
        rep (i,str.size()) {
            int c = str[i]-'a';
            if (trie[p][c] == -1) {
                clr(trie[end], -1);
                tag[end] = 0;
                trie[p][c] = end++;
            }
            p = trie[p][c];
        }
        tag[p] |= (1 << id);
    }
    void build(){
        int h =0 , t =0 ;
        rep (i, CHARSET) {
            if ( trie[0][i] < 0 ) {
                trie[0][i] = 0;
            } else {
                fail[trie[0][i]] = 0;   
                q[h++] = trie[0][i];
            }
        }
        while (t < h) {
            int p = q[t++];
            tag[p] |= tag[fail[p]];
            rep (i, CHARSET) {
                if (trie[p][i] < 0 ) {
                    trie[p][i] = trie[fail[p]][i];
                } else {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    q[h++] = trie[p][i];
                }
            }
        }
    }
} ac;

class InfiniteSoup {
	public:
	vector <int> countRays(vector <string> g, vector <string> words, int k) {
        ac.init();
        rep (i,words.size()) ac.add(words[i], i);
        ac.build();
        int len = 36*36*3;
        vector<int> ans(words.size());
        repn (i, 0, k + 1) {
            repn (j, 0, k + 1) {
                if (i == 0 and j == 0) continue;
                int gcd = __gcd(i, j);
                if (gcd > 1) continue;
                int x = 0, y = 0, p = 0;
                int mask = 0;
                rep (it, len) {
                    int c = g[x][y] - 'a';
                    int nxt = ac.trie[p][c];
                    mask |= ac.tag[nxt];
                    x += i;
                    y += j;
                    x %= g.size();
                    y %= g[0].size();
                    p = nxt;
                }
                rep (id, words.size()) {
                    ans[id] += ((mask&(1<<id)) != 0);
                } 
            }
        } 
        return ans;
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
	
	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
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
			string g[]                = {"abc","def","ghi"};
			string words[]            = {"abc"};
			int k                     = 2;
			int expected__[]          = {1 };

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string g[]                = {"abc","def","ghi"};
			string words[]            = {"abc"};
			int k                     = 3;
			int expected__[]          = {2 };

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string g[]                = {"abc","def","ghi"};
			string words[]            = {"abc"};
			int k                     = 4;
			int expected__[]          = {3 };

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string g[]                = {"ccbbc","baabc","ccbab","cbcaa","aacab"};
			string words[]            = {"aaccbaaccbaacc","aabbcaabbcaabbc","babccbabccbabc","aaacaaaacaaaaca",
 "abbcaabbcaab","ccbbcccbbcccbbc","bbacabbacab","caacccaacccaac",
 "baaccbaaccbaac","caccbcaccbca"};
			int k                     = 10;
			int expected__[]          = {0, 2, 0, 0, 2, 7, 5, 6, 0, 5 };

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string g[]                = {"abb","bbb","bbb"};
			string words[]            = {"aaa"};
			int k                     = 2;
			int expected__[]          = {0 };

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string g[]                = ;
			string words[]            = ;
			int k                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string g[]                = ;
			string words[]            = ;
			int k                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string g[]                = ;
			string words[]            = ;
			int k                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InfiniteSoup().countRays(vector <string>(g, g + (sizeof g / sizeof g[0])), vector <string>(words, words + (sizeof words / sizeof words[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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

