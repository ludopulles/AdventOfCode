#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

ll parseInt(const string &s, int &pos) {
	ll res = 0;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return res;
}

vector<vii> paths;

bitset<1000> grid0[1000], grid[1000];

int main() {
	int minX = INT_MAX, maxX = INT_MIN, maxY = 0;

	string line;
	while (getline(cin, line), cin) {
		// parse x,y -> x,y -> x,y ...
		int pos = 0;
		vii path;
		while (pos < sz(line)) {
			int x = parseInt(line, pos);
			assert(line[pos++] == ',');
			int y = parseInt(line, pos);
			pos += 4; // ' -> '

			path.eb(x, y);

			minX = min(minX, x);
			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}
		paths.pb(path);
	}

	REP(i, 1000) grid[i].set(maxY + 2);

	cout << "BOUNDS: x \\in {" << minX << ", " << maxX << "} and y \\in {0, " << maxY << "}" << endl;
	for (vii path : paths) {
		int x0 = path[0].x, y0 = path[0].y;
		grid[x0].set(y0);
		for (auto [x,y] : path) {
			assert(x0 == x || y0 == y);
			while (x0 > x) grid[--x0].set(y0);
			while (x0 < x) grid[++x0].set(y0);
			while (y0 > y) grid[x0].set(--y0);
			while (y0 < y) grid[x0].set(++y0);
		}
	}

	REP(i, 1000) grid0[i] = grid[i];

	int fallen = 0, cx, cy;
	while (true) {
		cx = 500;
		cy = 0;

		if (grid[cx].test(cy))
			break;

		while (true) {
			if (!grid[cx].test(cy+1)) cy++;
			else if (!grid[cx-1].test(cy+1)) cx--, cy++;
			else if (!grid[cx+1].test(cy+1)) cx++, cy++;
			else break;
		}

		grid[cx].set(cy);
		fallen++;
	}

	cout << fallen << endl;

	return 0;
}
