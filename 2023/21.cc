#include "header.h"
#define SQ(x) ((x) * (x))

vector<string> grid;
ii s;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

int W, H, D[9][150][150];

int smod(int a, int m) { return ((a %= m) < 0) ? (a + m) : a; }

ll num_reachable(int steps) {
	unordered_set<ii> cur = {s}, nxt;
	while (steps--) {
		for (auto [x, y] : cur) {
			REP(dir, 4) {
				int nx = x + dx[dir], ny = y + dy[dir];
				if (grid[smod(nx, H)][smod(ny, W)] != '#') nxt.emplace(nx, ny);
			}
		}

		cur.swap(nxt);
		nxt.clear();
	}

/*
	// Gather statistics...
	map<ii, int> inGrid;
	for (auto [x, y] : cur) {
		int u = (x-smod(x, W)) / W, v = (y - smod(y, H)) / H;
		inGrid[ii(u, v)]++;
	}
	for (auto [pr, n] : inGrid)
		cout << pr.x << ", " << pr.y << ": " << n << endl;
*/

	return sz(cur);
}

ll num_reachable_v2(ll steps) {
	assert(H == W && H % 2 == 1 && s.x == W/2 && s.y == H/2);

	ll q = (steps - (W+1)/2) / W;
	ll r = (steps - (W+1)/2) % W;

	ll use_all[2] = {}, side1[9][2] = {}, side2[9][2] = {}, corner[9] = {};
	REP(j, W) REP(k, H) use_all[(k+j) % 2] += D[0][j][k] < INT_MAX;

	rep(i, 1, 5) REP(p, 2) REP(j, W) REP(k, H) if ((k+j) % 2 == p) {
		side1[i][p] += (D[i][j][k] <= r - (W+1)/2);
		side2[i][p] += (D[i][j][k] <= r + (W+1)/2);
	}

	rep(i, 5, 9) REP(j, W) REP(k, H) if ((k+j) % 2 == 1) {
		corner[i] += (D[i][j][k] <= r);
	}

	// Add interior:
	ll res = use_all[1] * SQ(q) + use_all[0] * SQ(q + 1);
	// Add sides:
	rep(i, 1, 5) res += (q + 0) * side2[i][1] + (q + 1) * side1[i][0];
	// Add corners:
	rep(i, 5, 9) res += corner[i];

	return res;
}

int main() {
	ll sumA = 0, sumB = 0;

	// Read input
	string line;
	while (getline(cin, line), cin) grid.pb(line);
	H = sz(grid); W = sz(grid[0]);
	REP(i, H) REP(j, W) if (grid[i][j] == 'S') s = ii(i, j);

	ii pts[9] = { s,
		ii(0,   0), ii(0,   W-1), ii(H-1,   0), ii(H-1, W-1),
		ii(H/2, 0), ii(H/2, W-1), ii(0,   W/2), ii(H-1, W/2),
	};

	REP(i, 9) {
		REP(j, W) REP(k, H) D[i][j][k] = INT_MAX;
		D[i][pts[i].x][pts[i].y] = 0;
		queue<ii> q({pts[i]});
		while (!q.empty()) {
			auto [x,y] = q.front(); q.pop();
			REP(dir, 4) {
				ll nx = x + dx[dir], ny = y + dy[dir];
				if (0 <= nx && nx < H && 0 <= ny && ny < W && grid[nx][ny] != '#' && D[i][nx][ny] == INT_MAX) {
					D[i][nx][ny] = D[i][x][y] + 1;
					q.emplace(nx, ny);
				}
			}
		}
	}

	REP(i, W) REP(j, H) sumA += (D[0][i][j] <= 64 && D[0][i][j] % 2 == 64 % 2);
	assert(sumA == num_reachable(64));
	cout << "Part A: " << sumA << endl;

	ll N = 26501365;

	sumB = num_reachable_v2(N);
	cout << "Part B: " << sumB << endl;
	return 0;
}
