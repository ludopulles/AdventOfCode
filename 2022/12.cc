#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

vector<string> grid;

int nrows, ncols;
ii start, eind;

vector<vi> D;
queue<ii> q;

ll calc_dist() {
	while (!q.empty()) {
		ii cur = q.front();
		q.pop();
		REP(dir, 4) {
			int nx = cur.x + vi{0,1,0,-1}[dir], ny = cur.y + vi{1,0,-1,0}[dir];
			if (nx < 0 || nx >= nrows || ny < 0 || ny >= ncols ||
					D[nx][ny] >= 0 || grid[nx][ny] > grid[cur.x][cur.y] + 1)
				continue;

			D[nx][ny] = D[cur.x][cur.y] + 1;
			q.emplace(nx, ny);
		}
	}
	return D[eind.x][eind.y];
}

int main() {
	for (string line; getline(cin, line); ) grid.pb(line);

	nrows = grid.size();
	ncols = grid[0].size();

	REP(x, nrows) REP(y, ncols) {
		if (grid[x][y] == 'S') { grid[x][y] = 'a'; start = ii(x, y); }
		if (grid[x][y] == 'E') { grid[x][y] = 'z'; eind = ii(x, y); }
	}

	D.resize(nrows, vi(ncols, -1));
	D[start.x][start.y] = 0;

	q.push(start);

	printf("Part A: %lld\n", calc_dist());

	D.assign(nrows, vi(ncols, -1));
	REP(x, nrows) REP(y, ncols) if (grid[x][y] == 'a')
		D[x][y] = 0, q.emplace(x, y);

	printf("Part B: %lld\n", calc_dist());
	return 0;
}
