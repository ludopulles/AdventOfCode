#include "header.h"

#define W (2200)
bool border[W][W] = {}, seen[W][W] = {};
map<char, int> dx = {{'U',-1},{'R',0},{'L', 0},{'D',1}};
map<char, int> dy = {{'U', 0},{'R',1},{'L',-1},{'D',0}};

void dfs(int x, int y) {
	if (border[x][y]) return;

	seen[x][y] = true;
	if (x > 0 && !seen[x-1][y]) dfs(x - 1, y);
	if (x + 1 < W && !seen[x+1][y]) dfs(x + 1, y);
	if (y > 0 && !seen[x][y-1]) dfs(x, y - 1);
	if (y + 1 < W && !seen[x][y+1]) dfs(x, y + 1);
}

int main() {
	ll sumA = 0, sumB = 0;
	string line;
	ll x1 = W/2, y1 = 0, x2 = 0, y2 = 0;
	vii poly;

	while (getline(cin, line), cin) {
		vector<string> parts = split_str(line, " ");
		char mov = parts[0][0];
		ll num1 = parse_int(parts[1]);
		string col = parts[2].substr(2, sz(parts[2]) - 3);

		while (num1 --> 0) {
			x1 += dx[mov];
			y1 += dy[mov];
			border[x1][y1] = true;
		}

		ll num2;
		stringstream ss;
		ss << hex << col.substr(0, 5);
		ss >> num2;

		// 0: R, 1: D, 2: L, 3: U
		if (col[5] == '0' || col[5] == '2')
			y2 += col[5] == '0' ? num2 : -num2;
		else
			x2 += col[5] == '1' ? num2 : -num2;
		poly.eb(x2, y2);
	}

	dfs(0, 0);
	REP(i, W) REP(j, W) sumA += !seen[i][j];
	cout << "Part A: " << sumA << endl;

	REP(i, W) REP(j, W) border[i][j] = false;
	REP(i, W) REP(j, W) seen[i][j] = false;

	set<ll> compx, compy;
	for (auto [x, y] : poly)
		rep(_, -1, 2) compx.insert(x + _), compy.insert(y + _);
	map<ll, int> remapx, remapy;
	ll lx = *compx.begin() - 1, ly = *compy.begin() - 1;
	vi wx, wy;
	for (ll x : compx) remapx.emplace(x, sz(remapx)), wx.pb(x - lx), lx = x;
	for (ll y : compy) remapy.emplace(y, sz(remapy)), wy.pb(y - ly), ly = y;

	x2 = remapx[0], y2 = remapy[0];
	for (int i = 0; i < sz(poly); i++) {
		poly[i].x = remapx[poly[i].x], poly[i].y = remapy[poly[i].y];

		while (x2 < poly[i].x) border[x2++][y2] = true;
		while (x2 > poly[i].x) border[x2--][y2] = true;
		while (y2 < poly[i].y) border[x2][y2++] = true;
		while (y2 > poly[i].y) border[x2][y2--] = true;
	}
	dfs(0, 0);
	REP(i, W) REP(j, W) if (!seen[i][j]) sumB += wx[i] * wy[j];

	cout << "Part B: " << sumB << endl;
	return 0;
}
