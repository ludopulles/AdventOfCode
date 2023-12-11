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

vector<string> grid;

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) grid.pb(line);

	int H = sz(grid), W = sz(grid[0]);
	vi emptyRow = {0}, emptyCol = {0};
	REP(i, H) {
		bool empty = true; REP(j, W) empty &= grid[i][j] == '.';
		emptyRow.pb(emptyRow.back() + empty);
	}
	REP(j, W) {
		bool empty = true; REP(i, H) empty &= grid[i][j] == '.';
		emptyCol.pb(emptyCol.back() + empty);
	}

	vii pos;
	REP(i, H) REP(j, W) if (grid[i][j] != '.') pos.eb(i, j);

	for (ii p : pos) for (ii q : pos) {
		if (q == p) break;

		sumA += abs(q.x - p.x) + abs(emptyRow[p.x] - emptyRow[q.x]);
		sumA += abs(q.y - p.y) + abs(emptyCol[p.y] - emptyCol[q.y]);
	}

	cout << "Part A: " << sumA << endl;

	for (ii p : pos) for (ii q : pos) {
		if (q == p) break;

		sumB += abs(q.x - p.x) + 999999 * abs(emptyRow[p.x] - emptyRow[q.x]);
		sumB += abs(q.y - p.y) + 999999 * abs(emptyCol[p.y] - emptyCol[q.y]);
	}
	cout << "Part B: " << sumB << endl;
	return 0;
}
