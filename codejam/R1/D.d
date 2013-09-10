import std.stdio, std.string, std.conv;
import std.algorithm, std.array, std.bigint, std.math, std.range;
import core.thread;

//	Input
string[] tokens;
int tokenId = 0;
string readToken() { for (; tokenId == tokens.length; ) tokens = readln.split, tokenId = 0; return tokens[tokenId++]; }
int readInt() { return to!int(readToken); }
long readLong() { return to!long(readToken); }

//	chmin/chmax
void chmin(T)(ref T t, T f) { if (t > f) t = f; }
void chmax(T)(ref T t, T f) { if (t < f) t = f; }

//	Pair
struct Pair(S, T) {
	S x; T y;
	int opCmp(ref const Pair p) const { return (x < p.x) ? -1 : (x > p.x) ? +1 : (y < p.y) ? -1 : (y > p.y) ? +1 : 0; }
	string toString() const { return "(" ~ to!string(x) ~ ", " ~ to!string(y) ~ ")"; }
}
auto pair(S, T)(S x, T y) { return Pair!(S, T)(x, y); }

//	Array
int binarySearch(T)(T[] as, bool delegate(T) test) {
	int low = -1, upp = as.length; for (; low + 1 < upp; ) { int mid = (low + upp) >> 1; (test(as[mid]) ? low : upp) = mid; } return upp;
}
int lowerBound(T)(T[] as, T val) { return as.binarySearch((T a){ return (a <  val); }); }
int upperBound(T)(T[] as, T val) { return as.binarySearch((T a){ return (a <= val); }); }
T[] unique(T)(T[] as) { T[] bs; foreach (a; as) if (bs == null || bs[$ - 1] != a) bs ~= a; return bs; }


int gcd(int a, int b) { return (b != 0) ? gcd(b, a % b) : a; }

void prepare() {
	
}

class Solver : Thread {
	int caseId;
	this(int caseId) {
		this.caseId = caseId;
		super(&main);
	}
	void main() {
		try {
			run;
			stderr.writeln("DONE  Case #", caseId);
		} catch (Throwable e) {
			stderr.writeln("ERROR Case #", caseId, ": ", e.msg);
		} finally {
			stderr.flush;
		}
	}
	
	int M, N;
	int D;
	string[] A;
	bool[][] B;
	int SX, SY;
	int ans;
	
	int Q;
	
	bool checkSpecial(int dx, int dy) {
		int cnt = 0;
		for (int x = SX, y = SY; A[x][y] != '#'; x += dx, y += dy) {
			++cnt;
		}
		return (cnt * 2 - 1 <= D);
	}
	bool check(int dx, int dy) {
		if (dx == 0 || dy == 0) {
			return checkSpecial(dx, dy);
		}
// writeln("check dx = ",dx,", dy = ",dy);
		Q = abs(dx) * abs(dy);
		int n = cast(int)(sqrt((4.0 * D * D * dx * dx * dy * dy) / (dx * dx + dy * dy))) + 5;
		for (; 1L * n * n * (dx * dx + dy * dy) > 4L * D * D * dx * dx * dy * dy; --n) {}
// writeln(" n = ",n);
		int x = (SX * 2 + 1) * Q, y = (SY * 2 + 1) * Q;
		int vx = dx, vy = dy;
		foreach (i; 0 .. n) {
// writeln(" (",x,", ",y,"); (",vx,", ",vy,")");
			//	bounce
			int s(int r) { return (r < 0) ? -1 : 0; }
			if (x % Q == 0 && y % Q == 0) {
				//	corner
				bool cellF = B[x / Q + s(+vx)][y / Q + s(+vy)];
				bool cellX = B[x / Q + s(+vx)][y / Q + s(-vy)];
				bool cellY = B[x / Q + s(-vx)][y / Q + s(+vy)];
				if (cellF) {
					if (!cellX && !cellY) {
						//	disappear
// writeln(" disappear at ",x," ",y);
						return false;
					}
					if (cellX) {
						vx = -vx;
					}
					if (cellY) {
						vy = -vy;
					}
				}
			} else if (x % Q == 0) {
				//	horizontal edge
				if (B[x / Q + s(+vx)][y / Q]) {
					vx = -vx;
				}
			} else if (y % Q == 0) {
				//	vertical edge
				if (B[x / Q][y / Q + s(+vy)]) {
					vy = -vy;
				}
			}
			//	proceed
			x += vx;
			y += vy;
			//	hit
			if (x == (SX * 2 + 1) * Q && y == (SY * 2 + 1) * Q) {
// writeln(" hit!");
				return true;
			}
		}
		return false;
	}
	
	void run() {
		foreach (x; 0 .. M) foreach (y; 0 .. N) if (A[x][y] == 'X') {
			SX = x;
			SY = y;
		}
		assert(A[SX][SY] == 'X');
		B = new bool[][](M * 2, N * 2);
		foreach (x; 0 .. M * 2) foreach (y; 0 .. N * 2) {
			B[x][y] = (A[x / 2][y / 2] == '#');
		}
// foreach(bs;B){foreach(b;bs)write(b?'#':'.');writeln();}
		foreach (dx; -D .. D + 1) foreach (dy; -D .. D + 1) if (abs(gcd(dx, dy)) == 1) {
			if (dx * dx + dy * dy <= D * D) {
				if (check(dx, dy)) {
					++ans;
				}
			}
		}
	}
	
	void runSmall() {
		foreach (x; 0 .. M) foreach (y; 0 .. N) if (A[x][y] == 'X') {
			SX = x;
			SY = y;
		}
		assert(A[SX][SY] == 'X');
		int x0 = SX * 2 - 1;
		int y0 = SY * 2 - 1;
		int x1 = (M - 2) * 2 - x0;
		int y1 = (N - 2) * 2 - y0;
// writeln(x0," ",y0," ",x1," ",y1);
		long[] xs, ys;
		foreach (e; -50 .. +50 + 1) foreach (f; -50 .. +50 + 1) if (e || f) {
			long x, y;
			x += (x0 + x1) * (abs(e) / 2);
			if (e & 1) x += (e < 0) ? x0 : x1;
			y += (y0 + y1) * (abs(f) / 2);
			if (f & 1) y += (f < 0) ? y0 : y1;
			x *= (e < 0) ? -1 : +1;
			y *= (f < 0) ? -1 : +1;
			if (x * x + y * y <= D * D) {
// writeln(e," ",f," : ",x," ",y);
				xs ~= x;
				ys ~= y;
			}
		}
		foreach (i; 0 .. xs.length) {
			bool ok = true;
			foreach (j; 0 .. xs.length) {
				if (xs[i] * ys[j] == ys[i] * xs[j] && xs[i] * xs[j] + ys[i] * ys[j] > 0) {
					if (xs[i] * xs[i] + ys[i] * ys[i] > xs[j] * xs[j] + ys[j] * ys[j]) {
						ok = false;
						break;
					}
				}
			}
			if (ok) {
// writeln(xs[i]," ",ys[i]);
				++ans;
			}
		}
	}
	
	void input() {
		M = readInt;
		N = readInt;
		D = readInt;
		A = new string[M];
		foreach (x; 0 .. M) {
			A[x] = readToken;
		}
	}
	
	void output() {
		writeln("Case #", caseId, ": ", ans);
		stdout.flush;
	}
}

void main(string[] args) {
	bool parallel = false;
	foreach (arg; args) if (arg == "-p") parallel = true;
	prepare;
	auto solvers = new Solver[readInt];
	foreach (caseId, ref solver; solvers) solver = new Solver(caseId + 1);
	if (parallel) {
		foreach (solver; solvers) solver.input, solver.start;
		foreach (solver; solvers) solver.join, solver.output;
	} else {
		foreach (caseId, solver; solvers) {
			solver.input;
			solver.run;
			solver.output;
			stderr.writeln("DONE  Case #", caseId + 1);
			stderr.flush;
		}
	}
}

