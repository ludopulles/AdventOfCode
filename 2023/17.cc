#include "header.h"

vector<string> grid;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

ll D[4][11][141][141];

struct Loc {
	ll d, x, y, dir, nrstraight;
};

bool operator<(const Loc &a, const Loc &b) { return a.d > b.d; }

ll solveA() {
	int H = sz(grid), W = sz(grid[0]);

	REP(i, 4) REP(j, 4) REP(k, H) REP(l, W) D[i][j][k][l] = LLONG_MAX;

	D[0][0][0][0] = 0;
	priority_queue<Loc> pq;
	pq.push(Loc{ D[0][0][0][0] = 0, 0, 0, 0, 0 });
	while (!pq.empty()) {
		Loc l = pq.top();
		pq.pop();

		// cerr << l.x << ", " << l.y << ": " << l.d << endl;

		if (l.x == H-1 && l.y == W-1)
			return l.d;

		for (int ndir = 0; ndir < 4; ndir++) if (ndir != (l.dir + 2) % 4) {
			int newstr = ndir == l.dir ? (l.nrstraight + 1) : 0;
			int nx = l.x + dx[ndir], ny = l.y + dy[ndir];
			if (newstr < 3 && 0 <= nx && nx < H && 0 <= ny && ny < W) {
				ll newd = l.d + (grid[nx][ny] - '0');
				if (newd < D[ndir][newstr][nx][ny]) {
					pq.push(Loc{ D[ndir][newstr][nx][ny] = newd, nx, ny, ndir, newstr });
				}
			}
		}
	}
	return -1;
}

ll solveB() {
	int H = sz(grid), W = sz(grid[0]);

	REP(i, 4) REP(j, 11) REP(k, H) REP(l, W) D[i][j][k][l] = LLONG_MAX;

	D[0][0][0][0] = 0;
	priority_queue<Loc> pq;
	pq.push(Loc{ D[0][0][0][0] = 0, 0, 0, 0, 0 });
	pq.push(Loc{ D[1][0][0][0] = 0, 0, 0, 1, 0 });
	while (!pq.empty()) {
		Loc l = pq.top();
		pq.pop();

		// cerr << l.x << ", " << l.y << ": " << l.d << endl;
		if (l.x == H-1 && l.y == W-1 && l.nrstraight >= 3)
			return l.d;

		for (int ndir = 0; ndir < 4; ndir++) if (ndir != (l.dir + 2) % 4) {
			if (l.dir != ndir && l.nrstraight < 3) continue;

			int newstr = ndir == l.dir ? (l.nrstraight + 1) : 0;
			int nx = l.x + dx[ndir], ny = l.y + dy[ndir];
			if (newstr < 10 && 0 <= nx && nx < H && 0 <= ny && ny < W) {
				ll newd = l.d + (grid[nx][ny] - '0');
				if (newd < D[ndir][newstr][nx][ny]) {
					pq.push(Loc{ D[ndir][newstr][nx][ny] = newd, nx, ny, ndir, newstr });
				}
			}
		}
	}
	return -1;
}
int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);

	sumA = solveA();
	cout << "Part A: " << sumA << endl;

	sumB = solveB();
	cout << "Part B: " << sumB << endl;
	return 0;
}
