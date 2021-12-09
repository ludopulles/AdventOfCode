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

int main() {
	vector<string> grid;
	string line;
	while (getline(cin, line))
		grid.push_back(line);

	int h = grid.size(), w = grid[0].size();

	ll res = 0;
	REP(i, h) REP(j, w) {
		bool is_low = true;
		REP(d, 4) {
			int ni = i + dx[d], nj = j + dy[d];
			if (0 <= ni && ni < h && 0 <= nj && nj < w)
				is_low &= grid[i][j] < grid[ni][nj];
		}
		if (is_low) {
			res += 1 + (grid[i][j] - '0');
		}
	}

	cout << res << endl;

	return 0;
}
