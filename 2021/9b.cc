#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())

vi parse(string line) {
	for (char &ch : line)
		if (ch == ',') ch = ' ';
	stringstream ss(line);
	vi v;
	ll x;
	while (ss >> x)
		v.push_back(x);
	return v;
}

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

int h, w, H[100][100];
bool seen[100][100] = {};

void floodfill(int x, int y, int &cursize) {
	cursize++;
	seen[x][y] = true;

	REP(d, 4) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (0 <= nx && nx < h && 0 <= ny && ny < w && !seen[nx][ny] && H[nx][ny] != 9)
			floodfill(nx, ny, cursize);
	}
}

int main() {
	vector<string> grid;
	string line;
	while (getline(cin, line))
		grid.push_back(line);

	h = grid.size();
	w = grid[0].size();
	REP(i, h) REP(j, w) H[i][j] = grid[i][j] - '0';

	vector<ll> sizes;
	REP(i, h) REP(j, w) {
		if (seen[i][j] || H[i][j] == 9) continue;
		int cs = 0;
		floodfill(i, j, cs);
		sizes.push_back(cs);
	}

	sort(sizes.begin(), sizes.end());

	int m = sizes.size();
	ll res = sizes[m-3] * sizes[m-2] * sizes[m-1];
	cout << res << endl;

	return 0;
}
