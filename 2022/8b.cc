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

int main() {
	string line;
	while (getline(cin, line), cin)
		grid.pb(line);

	int H = grid.size(), W = grid[0].size();

	int ans = 0;
	REP(i, H) REP(j, W) {
		int len = 1;
		REP(dir, 4) {
			int dx = vi{ 0, 1, 0, -1 }[dir];
			int dy = vi{ 1, 0, -1, 0 }[dir];

			int x = i + dx, y = j + dy;
			int nr = 0;
			while (0 <= x && x < H && 0 <= y && y < W) {
				nr++;
				if (grid[x][y] >= grid[i][j]) break;
				x += dx; y += dy;
			}
			len *= nr;
		}

		// cerr << len << endl;
		ans = max(ans, len);
	}

	cout << ans << endl;

	return 0;
}
