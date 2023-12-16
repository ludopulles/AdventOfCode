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

/**************************************************************************************************
 * Code for today is below:
 *************************************************************************************************/

vector<string> grid;
int H, W;
vector<vector<bool>> seen[4], energized;

int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

void dfs(int i, int j, int dir) {
	if (i < 0 || i >= H || j < 0 || j >= W)
		return;
	if (seen[dir][i][j]) return;
	seen[dir][i][j] = true;

	energized[i][j] = true;

	if (grid[i][j] == '.') {
		dfs(i + dx[dir], j + dy[dir], dir);
	} else if (grid[i][j] == '/') {
		dfs(i + dx[3 - dir], j + dy[3 - dir], 3 - dir);
	} else if (grid[i][j] == '\\') {
		dfs(i + dx[dir ^ 1], j + dy[dir ^ 1], dir ^ 1);
	} else if (grid[i][j] == '|') {
		if (dx[dir] == 0) dfs(i - 1, j, 3), dfs(i + 1, j, 1);
		else dfs(i + dx[dir], j + dy[dir], dir);
	} else if (grid[i][j] == '-') {
		if (dy[dir] == 0) dfs(i, j - 1, 2), dfs(i, j + 1, 0);
		else dfs(i + dx[dir], j + dy[dir], dir);
	} 
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);
	H = sz(grid); W = sz(grid[0]);
	energized.assign(H, vector<bool>(W, false));
	REP(i, 4) seen[i].assign(H, vector<bool>(W, false));

	dfs(0, 0, 0);

	REP(i, H) REP(j, W) sumA += energized[i][j];

	cout << "Part A: " << sumA << endl;

	REP(i, H) {
		ll cur = 0;
		energized.assign(H, vector<bool>(W, false));
		REP(x, 4) seen[x].assign(H, vector<bool>(W, false));
		dfs(i, 0, 0);
		REP(i, H) REP(j, W) cur += energized[i][j];
		sumB = max(sumB, cur);

		cur = 0;
		energized.assign(H, vector<bool>(W, false));
		REP(x, 4) seen[x].assign(H, vector<bool>(W, false));
		dfs(i, W-1, 2);
		REP(i, H) REP(j, W) cur += energized[i][j];
		sumB = max(sumB, cur);
	}

	REP(j, W) {
		ll cur = 0;
		energized.assign(H, vector<bool>(W, false));
		REP(x, 4) seen[x].assign(H, vector<bool>(W, false));
		dfs(0, j, 1);
		REP(i, H) REP(j, W) cur += energized[i][j];
		sumB = max(sumB, cur);

		cur = 0;
		energized.assign(H, vector<bool>(W, false));
		REP(x, 4) seen[x].assign(H, vector<bool>(W, false));
		dfs(H - 1, j, 3);
		REP(i, H) REP(j, W) cur += energized[i][j];
		sumB = max(sumB, cur);
	}

	cout << "Part B: " << sumB << endl;
	return 0;
}
