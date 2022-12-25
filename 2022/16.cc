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
vi cache2;

int search2(int timeLeft, int v) {
	int best = 0;
	for (ll w : pts) if (!activated[w] && timeLeft > D[v][w]) {
		activated[w] = true;
		int alt = search2(timeLeft - D[v][w] - 1, w);
		best = max(best, (int) FR[w] * (timeLeft - D[v][w] - 1) + alt);
		activated[w] = false;
	}
	return best;
}

int search1(int timeLeft, int v) {
	int bitmask = 0;
	for (ll w : pts) bitmask = (bitmask << 1) | activated[w];
	int best = cache2[bitmask] >= 0 ? cache2[bitmask] : cache2[bitmask] = search2(26, lookup["AA"]);
	
	for (ll w : pts) if (!activated[w] && timeLeft > D[v][w]) {
		activated[w] = true;
		int alt = search1(timeLeft - D[v][w] - 1, w);
		best = max(best, (int) FR[w] * (timeLeft - D[v][w] - 1) + alt);
		activated[w] = false;
	}
	return best;
}

int main() {
	for (string line; getline(cin, line); ) {
		int valve = get_index(line, 6), pos = 23;
		FR[valve] = parseInt(line, pos);
		if (FR[valve] != 0) pts.pb(valve);

		if (line[pos + 8] == 's') pos++;
		for (pos += 24; pos < sz(line); pos += 4) {
			int to_valve = get_index(line, pos);
			G[valve].pb(to_valve);
		}
	}

	printf("Non zero valves: %d\n", sz(pts));
	cache2.resize(1 << sz(pts), -1);

	assert(sz(lookup) < 60);
	REP(i, 60) REP(j, 60) D[i][j] = INT_MAX / 3;
	REP(i, sz(lookup)) {
		D[i][i] = 0;
		for (ll j : G[i]) D[i][j] = 1;
	}

	REP(k, 60) REP(i, 60) REP(j, 60) {
		D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	}

	printf("Part A: %d\n", search2(30, lookup["AA"]));
	printf("Part B: %d\n", search1(26, lookup["AA"]));
	return 0;
}
