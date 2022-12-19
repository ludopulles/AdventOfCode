#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

ll parseInt(const string &s, int &pos) {
	assert(pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9')));

	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

int R00, R01, R02, R12, R03, R23;
int MAXORE;

struct State {
	int a[4], r[4];

	State(int _a1, int _a2, int _a3, int _a4, int _r1, int _r2, int _r3, int _r4) {
		a[0] = _a1; a[1] = _a2; a[2] = _a3; a[3] = _a4;
		r[0] = _r1; r[1] = _r2; r[2] = _r3; r[3] = _r4;

		if (r[0] >= MAXORE && a[0] >= MAXORE) a[0] = 100;
	}

	vector<State> neighbours() const
	{
		vector<State> res;

		// greedy:
		if (a[0] >= R03 && a[2] >= R23) {
			res.eb(
				a[0] + r[0] - R03, a[1] + r[1], a[2] + r[2] - R23, a[3] + r[3],
				r[0], r[1], r[2], r[3] + 1
			);
			return res;
		}

		// Always build something when there is enough ore...
		if (a[0] + r[0] < 2 * MAXORE) {
			res.eb(
				a[0] + r[0], a[1] + r[1], a[2] + r[2], a[3] + r[3],
				r[0], r[1], r[2], r[3]
			);
		}

		// If we have >= MAXORE ore miners, don't make more because it isn't useful.
		if (a[0] >= R00 && r[0] < MAXORE) {
			// Make an ore miner!
			res.eb(
				a[0] + r[0] - R00, a[1] + r[1], a[2] + r[2], a[3] + r[3],
				r[0] + 1, r[1], r[2], r[3]
			);
		}

		if (a[0] >= R01) {
			// Make a clay miner!
			res.eb(
				a[0] + r[0] - R01, a[1] + r[1], a[2] + r[2], a[3] + r[3],
				r[0], r[1] + 1, r[2], r[3]
			);
		}

		if (a[0] >= R02 && a[1] >= R12) {
			// Make an obsidian miner!
			res.eb(
				a[0] + r[0] - R02, a[1] + r[1] - R12, a[2] + r[2], a[3] + r[3],
				r[0], r[1], r[2] + 1, r[3]
			);
		}
		return res;
	}
};

bool operator<(const State &s, const State &r) {
	REP(i, 4) if (s.a[i] != r.a[i]) return s.a[i] < r.a[i];
	REP(i, 4) if (s.r[i] != r.r[i]) return s.r[i] < r.r[i];
	return false;
}

bool operator==(const State &s, const State &r) {
	REP(i, 4) if (s.a[i] != r.a[i]) return false;
	REP(i, 4) if (s.r[i] != r.r[i]) return false;
	return true;
}

namespace std {
	template<> struct hash<State> { public:
		size_t operator()(const State &s) const {
			size_t x = 0;
			REP(i, 4) x ^= hash<int>()(s.a[i]) + 0x9e3779b9 + (x<<6) + (x>>2);
			REP(i, 4) x ^= hash<int>()(s.r[i]) + 0x9e3779b9 + (x<<6) + (x>>2);
			return x;
		}
	};
}


pair<int, int> solve(bool andB) {
	unordered_set<State> cur, nxt;

	int ansA = 0;

	cur.emplace(0,0,0,0, 1,0,0,0);
	for (int t = 1; t <= (andB ? 32 : 24); t++) {
		for (const State &s : cur) {
			for (State ss : s.neighbours()) nxt.insert(ss);
		}

		cur.clear();
		cur = nxt;

		if (t == 24) {
			for (const State &s : cur)
				ansA = max(ansA, s.a[3]);
		}
	}

	int ansB = 0;
	for (const State &s : cur)
		ansB = max(ansB, s.a[3]);
	return make_pair(ansA, ansB);
}

void parse(int nr, string &line)
{
	int pos = 10, id;

	assert(line.starts_with("Blueprint "));
	id = parseInt(line, pos);

	assert(id == nr);

	assert(line.substr(pos, 23) == ": Each ore robot costs ");

	R00 = parseInt(line, pos += 23);
	assert(line.substr(pos, 28) == " ore. Each clay robot costs ");
	R01 = parseInt(line, pos += 28);

	assert(line.substr(pos, 32) == " ore. Each obsidian robot costs ");
	R02 = parseInt(line, pos += 32);
	assert(line.substr(pos, 9) == " ore and ");
	R12 = parseInt(line, pos += 9);
	assert(line.substr(pos, 30) == " clay. Each geode robot costs ");
	R03 = parseInt(line, pos += 30);
	assert(line.substr(pos, 9) == " ore and ");
	R23 = parseInt(line, pos += 9);
	assert(line.substr(pos, 10) == " obsidian.");

	MAXORE = max({R00, R01, R02, R03});
}


int main() {
	string line;
	int nr = 0;
	ll partA = 0, partB = 1;
	while (getline(cin, line), cin) {
		parse(++nr, line);

		auto [resA, resB] = solve(nr <= 3);
		partA += nr * resA;
		if (nr <= 3) {
			partB *= resB;
			printf("Line %d: %d, %d\n", nr, resA, resB);
		} else {
			printf("Line %d: %d\n", nr, resA);
		}

		// if (nr >= 3) break;
	}

	printf("Part A: %lld\n", partA);
	printf("Part B: %lld\n", partB);
	return 0;
}
