#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
#define pb push_back
#define eb emplace_back
#define x first
#define y second

vector<string> grid, newgrid;
map<ii, int> dist;

int R, C;

queue<ii> q;

void expand(int x, int y) {
	char cur = grid[x][y];
	int nd = dist[ii(x, y)] + 1;
	// cerr << x << ", " << y << ": " << nd-1 << endl;
	if ((cur == 'S' && x > 0) || cur == '|' || cur == 'L' || cur == 'J') {
		// North
		assert(x > 0);
		char nxt = grid[x - 1][y];
		if ((nxt == '|' || nxt == '7' || nxt == 'F')
				&& dist.find(ii(x - 1, y)) == dist.end()) {
			dist[ii(x - 1, y)] = nd;
			q.emplace(x - 1, y);
		}
	}

	if ((cur == 'S' && x + 1 < R) || cur == '|' || cur == '7' || cur == 'F') {
		// South
		assert(x + 1 < R);
		char nxt = grid[x + 1][y];
		if ((nxt == '|' || nxt == 'L' || nxt == 'J')
				&& dist.find(ii(x + 1, y)) == dist.end()) {
			dist[ii(x + 1, y)] = nd;
			q.emplace(x + 1, y);
		}
	}

	if ((cur == 'S' && y > 0) || cur == '-' || cur == 'J' || cur == '7') {
		// West
		assert(y > 0);
		char nxt = grid[x][y - 1];
		if ((nxt == '-' || nxt == 'L' || nxt == 'F')
				&& dist.find(ii(x, y - 1)) == dist.end()) {
			dist[ii(x, y - 1)] = nd;
			q.emplace(x, y - 1);
		}
	}

	if ((cur == 'S' && y + 1 < C) || cur == '-' || cur == 'L' || cur == 'F') {
		// West
		assert(y + 1 < C);
		char nxt = grid[x][y + 1];
		if ((nxt == '-' || nxt == 'J' || nxt == '7')
				&& dist.find(ii(x, y + 1)) == dist.end()) {
			dist[ii(x, y + 1)] = nd;
			q.emplace(x, y + 1);
		}
	}
}

void expandgrid()
{
	for (int i = 0; i < sz(grid); i++) {
		newgrid.eb(3 * sz(grid[i]), '.');
		newgrid.eb(3 * sz(grid[i]), '.');
		newgrid.eb(3 * sz(grid[i]), '.');

		for (int j = 0; j < sz(grid[i]); j++) {
			char c = dist.find(ii(i, j)) == dist.end() ? '.' : grid[i][j];
			newgrid[3*i + 1][3*j + 1] = c;
			if (c == 'S' || c == '|' || c == 'L' || c == 'J') newgrid[3*i + 0][3*j + 1] = '|';
			if (c == 'S' || c == '|' || c == '7' || c == 'F') newgrid[3*i + 2][3*j + 1] = '|';
			if (c == 'S' || c == '-' || c == 'J' || c == '7') newgrid[3*i + 1][3*j + 0] = '-';
			if (c == 'S' || c == '-' || c == 'L' || c == 'F') newgrid[3*i + 1][3*j + 2] = '-';
		}
	}
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);

	int sx = -1, sy = -1;
	R = sz(grid); C = sz(grid[0]);
	for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (grid[i][j] == 'S') sx = i, sy = j;
	assert(sx >= 0 && sy >= 0);

	dist[ii(sx, sy)] = 0;
	q.emplace(sx, sy);
	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();
		expand(x, y);
	}

	for (auto [loc, d] : dist) sumA = max(sumA, (ll) d);

	cout << "Part A: " << sumA << endl;

	expandgrid();

	q.emplace(0, 0);
	vector<vector<bool>> outside(3*R, vector<bool>(3*C, false));
	outside[0][0] = true;
	while (!q.empty()) {
		// cerr << q.size() << " ";
		auto [x, y] = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = x + vi{ -1, 0, 1, 0 }[dir];
			int ny = y + vi{ 0, 1, 0, -1 }[dir];
			if (0 <= nx && nx < 3*R && 0 <= ny && ny < 3*C && newgrid[nx][ny] == '.' && !outside[nx][ny]) {
				outside[nx][ny] = true;
				q.emplace(nx, ny);
			}
		}
	}

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (newgrid[3*i + 1][3*j + 1] == '.' && !outside[3*i + 1][3*j + 1]) {
				sumB++;
			}

	cout << "Part B: " << sumB << endl;
	return 0;
}
