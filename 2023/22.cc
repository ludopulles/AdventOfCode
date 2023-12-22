#include "header.h"

struct point { ll x, y, z; };

bool operator<(const point &a, const point &b) {
	if (a.z != b.z) return a.z < b.z;
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

struct Cube {
	ll x, y, z, u, v, w;

	vector<point> allPoints() const {
		assert((x == u) + (y == v) + (z == w) >= 2);
		assert(x <= u && y <= v && z <= w);

		vector<point> res;
		rep(i, x, u + 1) rep(j, y, v + 1) rep(k, z, w + 1)
			res.pb(point{ i, j, k });
		return res;
	}

};

bool operator<(const Cube &a, const Cube &b) { return a.z < b.z; }
ostream& operator<<(ostream &out, const Cube &c) {
	out << c.x << ',' << c.y << ',' << c.z;
	out << " ~ ";
	out << c.u << ',' << c.v << ',' << c.w;
	return out;
}

bool canDrop(const Cube &c, const map<point, int> &taken) {
	if (c.z <= 1) return false;
	rep(j, c.x, c.u + 1) rep(k, c.y, c.v + 1)
		if (taken.find(point{ j, k, c.z - 1}) != taken.end())
			return false;
	return true;
}

int main() {
	ll sumA = 0, sumB = 0;

	vector<Cube> cubes;
	string line;
	while (getline(cin, line), cin) {
		auto [A, B] = split_at(line, '~');
		vi as = parse_ints(split_str(A, ','));
		vi bs = parse_ints(split_str(B, ','));

		cubes.pb(Cube{ as[0], as[1], as[2], bs[0], bs[1], bs[2] });

		assert((as[0] == bs[0]) + (as[1] == bs[1]) + (as[2] == bs[2]) >= 2);
		sumA += abs(as[0] - bs[0]) + abs(as[1] - bs[1]) + abs(as[2] - bs[2]);
	}

	int N = sz(cubes);

	vector<set<int>> leaningOn(N), supports(N);

	vi falling;
	REP(i, N) falling.pb(i);
	set<int> isSingle;
	sort(all(falling), [&] (int a, int b) { return cubes[a] < cubes[b]; });
	map<point, int> taken;
	for (int i : falling) {
		while (canDrop(cubes[i], taken)) --cubes[i].z, --cubes[i].w;

		rep(j, cubes[i].x, cubes[i].u + 1) rep(k, cubes[i].y, cubes[i].v + 1) {
			point P{ j, k, cubes[i].z - 1};
			if (taken.find(P) != taken.end())
				leaningOn[i].insert(taken[P]),
				supports[taken[P]].insert(i);
		}

		for (const point &p : cubes[i].allPoints()) taken[p] = i;
	}

	REP(i, N) if (sz(leaningOn[i]) == 1)
		isSingle.insert(*leaningOn[i].begin());

	sumA = N - sz(isSingle);
	cout << "Part A: " << sumA << endl;

	for (int i : isSingle) {

		sumB--;

		vi supportedBy(N);
		REP(j, N) supportedBy[j] = sz(leaningOn[j]);

		vi Q = { i };
		while (!Q.empty()) {
			ll cur = Q.back();
			Q.pop_back();
			sumB++;
			for (ll to : supports[cur]) if (--supportedBy[to] == 0) {
				Q.pb(to);
			}
		}
	}

	cout << "Part B: " << sumB << endl;
	return 0;
}
