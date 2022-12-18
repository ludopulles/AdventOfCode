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
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

struct Pt {
	int x, y, z;
	Pt() : x(0), y(0), z(0) {}
	Pt(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

bool operator==(const Pt &a, const Pt &b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

namespace std {
template<> struct hash<Pt> {
public:
	size_t operator()(const Pt &p) const {
		size_t x = hash<int>()(p.x), y = hash<int>()(p.y), z = hash<int>()(p.z);
		x ^= y + 0x9e3779b9 + (x<<6) + (x>>2);
		x ^= z + 0x9e3779b9 + (x<<6) + (x>>2);
		return x;
	}
};
}

vector<Pt> pts;
unordered_set<Pt> points;

const int B = 24;
bool col[B][B][B] = {};

void mark(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 || x >= B || y >= B || z >= B) return;
	if (points.find(Pt(x,y,z)) != points.end() || col[x][y][z]) return;

	col[x][y][z] = true;

	mark(x - 1, y, z);
	mark(x + 1, y, z);
	mark(x, y - 1, z);
	mark(x, y + 1, z);
	mark(x, y, z - 1);
	mark(x, y, z + 1);
}

int main() {
	string line;

	int minx = INT_MAX, maxx = INT_MIN;
	int miny = INT_MAX, maxy = INT_MIN;
	int minz = INT_MAX, maxz = INT_MIN;

	while (getline(cin, line), cin) {
		int pos = 0, x, y, z;
		x = parseInt(line, pos); pos++;
		y = parseInt(line, pos); pos++;
		z = parseInt(line, pos);

		pts.eb(x, y, z);
		points.emplace(x, y, z);

		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
		minz = min(minz, z);
		maxz = max(maxz, z);
	}

	// Part A:
	ll numx = 0, numy = 0, numz = 0;
	for (auto [x,y,z] : pts) {
		if (points.find(Pt(x - 1, y, z)) == points.end()) numx++;
		if (points.find(Pt(x + 1, y, z)) == points.end()) numx++;
		if (points.find(Pt(x, y - 1, z)) == points.end()) numy++;
		if (points.find(Pt(x, y + 1, z)) == points.end()) numy++;
		if (points.find(Pt(x, y, z - 1)) == points.end()) numz++;
		if (points.find(Pt(x, y, z + 1)) == points.end()) numz++;
	}

	printf("Part A: %lld\n", numx + numy + numz);

	// Part B:
	mark(0, 0, 0);

	REP(x, B) REP(y, B) REP(z, B) if (!col[x][y][z] && points.find(Pt(x,y,z)) == points.end()) {
		pts.eb(x, y, z);
		points.emplace(x, y, z);
	}

	numx = 0, numy = 0, numz = 0;
	for (auto [x,y,z] : pts) {
		if (points.find(Pt(x - 1, y, z)) == points.end()) numx++;
		if (points.find(Pt(x + 1, y, z)) == points.end()) numx++;
		if (points.find(Pt(x, y - 1, z)) == points.end()) numy++;
		if (points.find(Pt(x, y + 1, z)) == points.end()) numy++;
		if (points.find(Pt(x, y, z - 1)) == points.end()) numz++;
		if (points.find(Pt(x, y, z + 1)) == points.end()) numz++;
	}
	printf("Part B: %lld\n", numx + numy + numz);

	return 0;
}
