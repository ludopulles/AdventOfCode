#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;

#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

map<string, int> lookup;
vvi G;
vi FR;

int D[60][60];

int get_index(const string &s, int pos) {
	string S("X", 2);
	S[0] = s[pos];
	S[1] = s[pos + 1];
	if (lookup.find(S) == end(lookup)) {
		G.pb(vi());
		FR.pb(0);
		lookup[S] = sz(G) - 1;
	}
	return lookup[S];
}

vi pts;
bool activated[60] = {};

ll search2(int timeLeft, int v) {
	ll best = 0;
	for (int w : pts) if (!activated[w] && timeLeft > D[v][w]) {
		activated[w] = true;
		ll alt = search2(timeLeft - D[v][w] - 1, w);
		best = max(best, FR[w] * (timeLeft - D[v][w] - 1) + alt);
		activated[w] = false;
	}
	return best;
}

ll search1(int timeLeft, int v) {
	ll best = search2(26, lookup["AA"]);
	for (int w : pts) if (!activated[w] && timeLeft > D[v][w]) {
		activated[w] = true;
		ll alt = search1(timeLeft - D[v][w] - 1, w);
		best = max(best, FR[w] * (timeLeft - D[v][w] - 1) + alt);
		activated[w] = false;
	}
	return best;
}

int main() {
	string line;

	while (getline(cin, line), cin) {
		int valve = get_index(line, 6), pos = 23;
		FR[valve] = parseInt(line, pos);
		if (FR[valve] != 0) pts.pb(valve);

		if (line[pos + 8] == 's') pos++;
		pos += 24;
		while (pos < sz(line)) {
			int to_valve = get_index(line, pos);
			pos += 4;
			G[valve].pb(to_valve);
		}
	}

	assert(sz(lookup) < 60);
	REP(i, 60) REP(j, 60) D[i][j] = INT_MAX / 3;
	REP(i, sz(lookup)) {
		D[i][i] = 0;
		for (ll j : G[i]) D[i][j] = 1;
	}

	REP(k, 60) REP(i, 60) REP(j, 60) {
		D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	}

	ll maxScore = search1(26, lookup["AA"]);
	cout << maxScore << endl;

	return 0;
}
