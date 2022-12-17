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

const ll GOAL = 1000000000000LL;

vii shapes[5] = {
	vii{{0,0},{1,0},{2,0},{3,0}},
	vii{{1,0},{1,1},{1,2},{0,1},{2,1}},
	vii{{0,0},{1,0},{2,0},{2,1},{2,2}},
	vii{{0,0},{0,1},{0,2},{0,3}},
	vii{{0,0},{0,1},{1,0},{1,1}}
};

vector<bool> G[7];
int H = 0;

bool T(int x, int y) { return y < sz(G[x]) && G[x][y]; }
void S(int x, int y) {
	while (sz(G[x]) <= y) G[x].pb(false), H = max(H, sz(G[x]));
	G[x][y] = true;
}

bool shapeCanMove(int sh, int x, int y) {
	for (auto [xx,yy] : shapes[sh])
		if (y + yy < 0 || x + xx < 0 || x + xx >= 7 || T(x + xx, y + yy)) return false;
	return true;
}

int main() {
	int pos = 0;
	string line;
	getline(cin, line);

	ll lastH = 0;

	vi heights;
	ll period = -1, inc = -1;
	for (int i = 0; i < 100'000; i++) {
		heights.pb(H);

		if (i == 2022) {
			printf("Part 1: %lld\n\n", H);
		}

		if (i > 50'000) {
			int p = 1;
			while (true) {
				ll D = heights[i] - heights[i-p];
				bool valid = true;
				rep(j, 1, 20) if (heights[i - j*p] != heights[i] - j*D) valid = false;
				if (valid) break;
				p++;
			}

			if (4*p < i) {
				period = p;
				inc = heights[i] - heights[i - p];

				while (i % period != GOAL % period) i--;

				ll R = (GOAL - i) / period;
				printf("Period:   %lld\n", period);
				printf("Increase: %lld\n", inc);
				printf("Answer:   %lld\n", heights[i] + R * inc);
				return 0;
			}
		}

		int curx = 2, cury = H + 3;
		do {
			// Move the rock
			if (pos == sz(line)) pos = 0;
			if (line[pos++] == '<') {
				if (shapeCanMove(i % 5, curx - 1, cury)) { curx--; }
			} else if (shapeCanMove(i % 5, curx + 1, cury)) { curx++; }
		} while (shapeCanMove(i % 5, curx, --cury));
		cury++;

		for (auto [x,y] : shapes[i % 5]) {
			S(curx + x, cury + y);
		}
	}

	return 0;
}
