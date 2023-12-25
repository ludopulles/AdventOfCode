#include "header.h"

vector<string> grid;
int H, W;

ll D[141][141];
ii prv[141][141];

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);
	H = sz(grid); W = sz(grid[0]);

	ii start{0, 1}, end{H-1, W-2};

	REP(i, H) REP(j, W) D[i][j] = LLONG_MAX;

	queue<ii> q({start});

	D[start.x][start.y] = 0;
	prv[start.x + 1][start.y] = ii(start.x + 1, start.y);
	while (!q.empty()) {
		ii cur = q.front(); q.pop();
		REP(dir, 4) {
			ll x = cur.x + vi{0, 1, 0, -1}[dir];
			ll y = cur.y + vi{1, 0, -1, 0}[dir];
			if (x < 0 || x >= W || grid[x][y] == '#') continue;
			if (ii(x, y) == prv[cur.x][cur.y]) continue;

			if (grid[cur.x][cur.y] == '>' && dir != 0) continue;
			if (grid[cur.x][cur.y] == 'v' && dir != 1) continue;
			if (grid[cur.x][cur.y] == '<' && dir != 2) continue;
			if (grid[cur.x][cur.y] == '^' && dir != 3) continue;

			D[x][y] = D[cur.x][cur.y] + 1;
			prv[x][y] = cur;
			q.emplace(x, y);
		}
	}

	sumA = D[end.x][end.y];

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
