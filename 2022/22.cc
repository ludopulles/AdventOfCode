#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

bool is_num(const string &s, int &pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

const int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

int nrows, ncols;
vector<string> grid;
string instructions;

bool empty(int x, int y) {
	return x < 0 || x >= sz(grid) || y < 0 || y >= sz(grid[x]) || grid[x][y] == ' ';
}

ll solveA() {
	int x = 0, y = 0, f = 0;
	while (grid[x][y] == ' ') y++;

	int pos = 0;
	while (pos != sz(instructions)) {
		if (is_num(instructions, pos)) {
			int num = parseInt(instructions, pos);
			while (num --> 0) {
				// make a step
				int nx = x + dx[f], ny = y + dy[f];

				if (dx[f] > 0 && empty(nx, ny)) {
					nx = 0;
					while (empty(nx, ny)) nx++;
				} else if (dx[f] < 0 && empty(nx, ny)) {
					nx = nrows - 1;
					while (empty(nx, ny)) nx--;
				}

				if (dy[f] > 0 && empty(nx, ny)) {
					ny = 0;
					while (empty(nx, ny)) ny++;
				} else if (dy[f] < 0 && empty(nx, ny)) {
					ny = ncols - 1;
					while (empty(nx, ny)) ny--;
				}

				if (grid[nx][ny] == '#') break;
				x = nx;
				y = ny;
			}
		} else {
			if (instructions[pos] == 'R') {
				if (++f == 4) f = 0;
			} else if (instructions[pos] == 'L') {
				if (--f == -1) f = 3;
			} else assert(false);
			pos++;
		}
	}

	return 1004 + f + 4 * y + 1000 * x;
}

tuple<int,int,int> goOffEdge(int x, int y, int f) {
	//  AB
	//  C
	// ED
	// F
	assert(empty(x + dx[f], y + dy[f]));

	if (x == 0 && 50 <= y && y < 100 && f == 3)
		return make_tuple(100 + y, 0, 0); // A -> F
	if (y == 0 && 150 <= x && x < 200 && f == 2)
		return make_tuple(0, x - 100, 1); // F -> A

	if (x == 0 && 100 <= y && y < 150 && f == 3)
		return make_tuple(199, y - 100, 3); // B -> F
	if (x == 199 && 0 <= y && y < 50 && f == 1)
		return make_tuple(0, y + 100, 1); // F -> B

	if (y == 149 && 0 <= x && x < 50 && f == 0)	
		return make_tuple(149 - x, 99, 2); // B -> D
	if (y == 99 && 100 <= x && x < 150 && f == 0)
		return make_tuple(149 - x, 149, 2); // D -> B

	if (x == 49 && 100 <= y && y < 150 && f == 1)
		return make_tuple(y - 50, 99, 2); // B -> C
	if (y == 99 && 50 <= x && x < 100 && f == 0)
		return make_tuple(49, x + 50, 3); // C -> B

	if (x == 149 && 50 <= y && y < 100 && f == 1)
		return make_tuple(100 + y, 49, 2); // D -> F
	if (y == 49 && 150 <= x && x < 200 && f == 0)
		return make_tuple(149, x - 100, 3); // F -> D

	if (y == 0 && 100 <= x && x < 150 && f == 2)
		return make_tuple(149 - x, 50, 0); // E -> A
	if (y == 50 && 0 <= x && x < 50 && f == 2)
		return make_tuple(149 - x, 0, 0); // A -> E

	if (x == 100 && 0 <= y && y < 50 && f == 3)
		return make_tuple(50 + y, 50, 0); // E -> C
	if (y == 50 && 50 <= x && x < 100 && f == 2)
		return make_tuple(100, x - 50, 1); // C -> E
	
	assert(false);
}

ll solveB() {
	REP(x, nrows) REP(y, ncols) REP(f, 4) if (!empty(x, y) && empty(x + dx[f], y + dy[f])) {
		int nx, ny, nf;
		tie(nx, ny, nf) = goOffEdge(x, y, f);
		tie(nx, ny, nf) = goOffEdge(nx, ny, (nf + 2) % 4);
		assert(nx == x && ny == y && (nf + 2) % 4 == f);
	}

	int x = 0, y = 0, f = 0;
	while (grid[x][y] == ' ') y++;

	int pos = 0;
	while (pos != sz(instructions)) {
		if (is_num(instructions, pos)) {
			int num = parseInt(instructions, pos);
			while (num --> 0) {
				// printf("(%d, %d) facing %d\n", x, y, f);
				// make a step
				int nx = x + dx[f], ny = y + dy[f], nf = f;
				if (empty(nx, ny)) {
					tie(nx, ny, nf) = goOffEdge(x, y, f);
				}

				if (grid[nx][ny] == '#') break;
				x = nx;
				y = ny;
				f = nf;
			}
		} else {
			// printf("(%d, %d) facing %d\n", x, y, f);
			if (instructions[pos] == 'R') {
				if (++f == 4) f = 0;
			} else if (instructions[pos] == 'L') {
				if (--f == -1) f = 3;
			} else assert(false);
			pos++;
		}
	}

	return 1004 + f + 4 * y + 1000 * x;
}

int main() {
	string line;
	while (getline(cin, line), line != "") grid.pb(line);
	getline(cin, instructions);

	nrows = sz(grid);
	ncols = sz(grid[0]);

	printf("Part A: %lld\n", solveA());
	printf("Part B: %lld\n", solveB());

	return 0;
}
