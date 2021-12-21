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

const int N = 1000;

bool A[512], grid[2][N][N] = {};

int main() {
	string line;
	getline(cin, line);
	REP(i, 512) A[i] = (line[i] == '#');

	getline(cin, line);
	assert(line == "");

	for (int mid = (N-100)/2, r = mid; getline(cin, line); r++)
		REP(c, sz(line)) grid[0][r][mid+c] = (line[c] == '#');

	for (int step = 1; step <= 50; step++) {
		int to = step&1, fr = 1-to;

		REP(i, N)
			grid[to][i][0] = grid[to][i][N-1] = grid[to][0][i] = grid[to][N-1][i] = (grid[fr][0][0] ? A[511] : A[0]);
		rep(r, 1, N-1) rep(c, 1, N-1) {
			int nr = 0;
			for (int x = r-1; x <= r+1; x++)
				for (int y = c-1; y <= c+1; y++)
					nr = (nr<<1) | grid[fr][x][y];
			grid[to][r][c] = A[nr];
		}

		int tot = 0;
		REP(r, N) REP(c, N) tot += grid[to][r][c];
		cout << step << ": " << tot << endl;

		/* rep(r, (N-100)/2 - 3, (N-70)/2 - 3) {
			rep(c, (N-100)/2 - 3, (N-70)/2 - 3)
				cout << grid[fr][r][c];
			cout << endl;
		} */
	}

	return 0;
}
