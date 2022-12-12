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

int main() {
	string line;
	while (getline(cin, line), cin) grid.pb(line);

	nrows = grid.size();
	ncols = grid[0].size();

	REP(x, nrows) REP(y, ncols) {
		if (grid[x][y] == 'S') { grid[x][y] = 'a'; start = ii(x, y); }
		if (grid[x][y] == 'E') { grid[x][y] = 'z'; eind = ii(x, y); }
	}

	D.resize(nrows, vi(ncols, 0));
	D[start.x][start.y] = 0;

	queue<ii> q;
	q.push(start);
	while (!q.empty()) {
		ii cur = q.front();
		q.pop();
		REP(dir, 4) {
			int newx = cur.x + vi{0,1,0,-1}[dir];
			int newy = cur.y + vi{1,0,-1,0}[dir];

			if (newx < 0 || newx >= nrows || newy < 0 || newy >= ncols)
				continue;

			if (D[newx][newy] != 0) continue;
			if (grid[newx][newy] > grid[cur.x][cur.y] + 1) continue;

			D[newx][newy] = D[cur.x][cur.y] + 1;
			q.emplace(newx, newy);
		}
	}

	cout << D[eind.x][eind.y] << endl;

	return 0;
}
