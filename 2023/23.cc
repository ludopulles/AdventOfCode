#include "header.h"

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

vector<string> grid;
int H, W;

ll D[141][141];
ii prv[141][141];

vii crossings;
ll crossing[141][141];
vii dists[4];

ll curbest;
vi curseq;

void longest_path(vector<bool> &used, vi &seq, int idx, ll cur_len) {
	seq.pb(idx);
	if (crossings[idx].x == H-1) {
		curbest = max(curbest, cur_len);
		curseq = seq;
	} else {
		ll res = 0LL;
		REP(dir, 4) if (dists[dir][idx].x >= 0 && !used[dists[dir][idx].x]) {
			used[dists[dir][idx].x] = true;
			longest_path(used, seq, dists[dir][idx].x, dists[dir][idx].y + cur_len);
			used[dists[dir][idx].x] = false;
		}
	}
	seq.pop_back();
}

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
			ll x = cur.x + dx[dir];
			ll y = cur.y + dy[dir];
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


	REP(i, H) REP(j, W) if (grid[i][j] != '#') {
		crossing[i][j] = -1;
		if (i == 0 || i == H-1) { crossing[i][j] = sz(crossings), crossings.eb(i, j); continue; }

		int num_around = (grid[i][j-1] != '#') + (grid[i][j+1] != '#') + (grid[i-1][j] != '#') + (grid[i+1][j] != '#');
		if (num_around >= 3) {
			crossing[i][j] = sz(crossings);
			crossings.eb(i, j);
		}
	}

	REP(dir, 4) {
		dists[dir].resize(sz(crossings));
		REP(i, sz(crossings)) {
			ii cr = crossings[i];
			ii cur = cr, nxt(cr.x + dx[dir], cr.y + dy[dir]);
			if (nxt.x < 0 || nxt.x >= H || grid[nxt.x][nxt.y] == '#') {
				dists[dir][i] = make_pair(-1LL, LLONG_MAX);
				continue;
			}

			ll len = 1, d;
			while (crossing[nxt.x][nxt.y] == -1) {
				for (d = 0; d < 4; d++) {
					ii nxt2(nxt.x + dx[d], nxt.y + dy[d]);
					if (grid[nxt2.x][nxt2.y] != '#' && nxt2 != cur)
						{ cur = nxt, nxt = nxt2, len++; break; }
				}
				assert(d < 4);
			}
			dists[dir][i] = make_pair(crossing[nxt.x][nxt.y], len);
		}
	}

	vector<bool> used(sz(crossings), false);
	vi seq;
	used[0] = true;
	longest_path(used, seq, 0, 0);
	sumB = curbest;
	cout << "Part B: " << sumB << endl;
	return 0;
}
