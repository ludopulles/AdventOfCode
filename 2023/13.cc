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

vector<vector<string>> grid;

vector<string> T(const vector<string> &g) {
	vector<string> r(sz(g[0]));
	REP(i, sz(g[0])) {
		string S(sz(g), '.');
		REP(j, sz(g)) S[j] = g[j][i];
		r[i] = S;
	}
	return r;
}

int solveA(const vector<string> &g) {
	for (int i = 0; i + 1 < sz(g); i++) {
		bool good = true;
		for (int j = i, k = j + 1; j >= 0 && k < sz(g); j--, k++)
			if (g[j] != g[k]) { good = false; break; }
		if (good) return 100 * (i + 1);
	}

	auto gT = T(g);
	for (int i = 0; i + 1 < sz(gT); i++) {
		bool good = true;
		for (int j = i, k = j + 1; j >= 0 && k < sz(gT); j--, k++)
			if (gT[j] != gT[k]) { good = false; break; }
		if (good) return (i + 1);
	}

	return 0;
}

int solveB(const vector<string> &g) {
	for (int i = 0; i + 1 < sz(g); i++) {
		int nr_errs = 0;
		for (int j = i, k = j + 1; j >= 0 && k < sz(g); j--, k++)
			if (g[j] != g[k]) {
				REP(l, sz(g[0])) nr_errs += g[j][l] != g[k][l];
				if (nr_errs > 1) break;
			}
		if (nr_errs == 1) return 100 * (i + 1);
	}

	auto gT = T(g);
	for (int i = 0; i + 1 < sz(gT); i++) {
		int nr_errs = 0;
		for (int j = i, k = j + 1; j >= 0 && k < sz(gT); j--, k++)
			if (gT[j] != gT[k]) {
				REP(l, sz(gT[0])) nr_errs += gT[j][l] != gT[k][l];
				if (nr_errs > 1) break;
			}
		if (nr_errs == 1) return (i + 1);
	}
	return 0;
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	vector<string> curgrid;
	while (getline(cin, line), cin) {
		if (line == "") {
			grid.pb(curgrid);
			curgrid.clear();
		} else {
			curgrid.pb(line);
		}
	}
	grid.pb(curgrid);


	for (auto &g : grid) {
		ll inc = solveA(g);
		if (inc <= 0) {
			cout << "PROBLEM: " << endl;
			for (string &s : g) cout << s << endl;
		}

		assert(inc > 0);
		sumA +=inc;
		// cerr << sz(g) << "x" << sz(g[0]) << " NOW: " << solveA(g) << endl;

		inc = solveB(g);
		assert(inc > 0);
		sumB += inc;
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
