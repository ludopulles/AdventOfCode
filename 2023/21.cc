#include "header.h"

/**************************************************************************************************
 * Code for today is below:
 *************************************************************************************************/

vector<string> grid;
ii s;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);

	REP(i, sz(grid)) REP(j, sz(grid[0])) if (grid[i][j] == 'S') s = ii(i, j);

	set<ii> cur = {s}, nxt;

	REP(_, 64) {
		if (_ == 6) {
			cout << "6 steps: " << sz(cur) << endl;
		}

		for (auto [x,y] : cur) {
			REP(dir, 4) {
				int nx = x + dx[dir], ny = y + dy[dir];
				if (0 <= nx && nx < sz(grid) && 0 <= ny && ny < sz(grid[0]) && grid[nx][ny] != '#')
					nxt.emplace(nx, ny);
			}
		}

		cur.swap(nxt);
	}

	sumA = sz(cur);
	cout << "Part A: " << sumA << endl;

	unordered_map<ii, ll> cur2 = {{s,1}}, nxt2;
	REP(_, 64) {
		if (_ == 1 || _ == 6 || _ == 10 || _ == 50 || _ == 100 || _ == 500 || _ == 1000 || _ == 5000) {
			ll res = 0;
			for (auto [pr, num] : cur2) res += num;
			cout << _ << " steps: " << res << endl;
		}

		for (auto [pr, num] : cur2) {
			auto [x,y] = pr;
			REP(dir, 4) {
				int nx = x + dx[dir], ny = y + dy[dir];
				if (nx < 0) nx += sz(grid);
				if (nx >= sz(grid)) nx -= sz(grid);
				if (ny < 0) ny += sz(grid[0]);
				if (ny >= sz(grid[0])) ny -= sz(grid[0]);

				if (grid[nx][ny] != '#') nxt2[ii(nx, ny)] += num;
			}
		}

		cur2.swap(nxt2);
		nxt2.clear();
	}


	cout << "Part B: " << sumB << endl;
	return 0;
}
