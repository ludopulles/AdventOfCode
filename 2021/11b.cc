#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define pb push_back
#define eb emplace_back
#define x first
#define y second

vector<vi> grid;

int main() {
	string line;
	while (getline(cin, line)) {
		vi nrs;
		for (char ch : line) nrs.push_back(ch - '0');
		grid.pb(nrs);
	}
	int w = grid.size(), h = grid[0].size();

	for (int i=1; ; i++) {
		queue<ii> q;
		REP(j, w) REP(k, h) {
			if (++grid[j][k] == 10)
				q.emplace(j, k);
		}

		while (!q.empty()) {
			ii cur = q.front();
			q.pop();
			rep(dj, -1, 2) rep(dk, -1, 2) if (dj!=0 || dk!=0) {
				int nj = cur.x + dj, nk = cur.y + dk;
				if (0 <= nj && nj < w && 0 <= nk && nk < h) {
					if (++grid[nj][nk] == 10)
						q.emplace(nj, nk);
				}
			}
		}

		int nflash = 0;
		REP(j, w) REP(k, h)
			if (grid[j][k] >= 10) grid[j][k] = 0, nflash++;
		if (nflash == w*h) {
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}
