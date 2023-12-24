#include "header.h"

typedef long double ld;
#define EPS (1e-10)

ll LEFT, RIGHT;

struct pt { ll x, y, z; };
struct pt2 { ll x, y; };

typedef pair<ld, ld> ptd;

pt read_pt(const string &s) {
	vi v = parse_ints(split_str(s, ", "));
	return pt{ v[0], v[1], v[2] };
}

pt operator-(const pt &a, const pt &b) { return pt{ a.x - b.x, a.y - b.y, a.z - b.z }; }
pt2 cast(const pt &p) { return pt2{ p.x, p.y }; }

pt2 operator+(const pt2 &a, const pt2 &b) { return pt2{ a.x + b.x, a.y + b.y }; }
pt2 operator-(const pt2 &a, const pt2 &b) { return pt2{ a.x - b.x, a.y - b.y }; }
pt2 operator*(const pt2 &a, ll sc) { return pt2{ a.x * sc, a.y * sc }; }
ptd operator*(const pt2 &a, ld sc) { return make_pair(a.x * sc, a.y * sc); }
ptd operator*(const ptd &a, ld sc) { return make_pair(a.x * sc, a.y * sc); }

ptd operator+(const ptd &a, const ptd &b) { return ptd{ a.x + b.x, a.y + b.y }; }
ptd operator-(const ptd &a, const ptd &b) { return ptd{ a.x - b.x, a.y - b.y }; }

ld operator^(const pt2 &a, const pt2 &b) { return (ld)a.x * b.y - (ld)a.y * b.x; }
ld operator*(const pt2 &a, const pt2 &b) { return (ld)a.x * b.x + (ld)a.y * b.y; }

vector<pt> x, v;

bool linesIntersect(pt2 a, pt2 b, pt2 c, pt2 d) {
	return abs((a-b) ^ (c-d)) > EPS;
}

ptd lineLineIntersection(pt2 a, pt2 b, pt2 c, pt2 d) {
	ld det = (a-b) ^ (c-d);
	assert(abs(det) > EPS);
	return ((c-d)*(a^b) - (a-b)*(c^d)) * (ld(1.0)/det);
}

bool collide2D(int i, int j) {
	pt2 pi = cast(x[i]), qi = pi + cast(v[i]);
	pt2 pj = cast(x[j]), qj = pj + cast(v[j]);
	if (!linesIntersect(pi, qi, pj, qj)) return false;

	auto [Ix, Iy] = lineLineIntersection(pi, qi, pj, qj);
	ld ti = v[i].x != 0 ? (Ix - x[i].x) / v[i].x : (Iy - x[i].y) / v[i].y;;
	ld tj = v[j].x != 0 ? (Ix - x[j].x) / v[j].x : (Iy - x[j].y) / v[j].y;;

	return ti >= 0 && tj >= 0 && (LEFT <= Ix && Ix <= RIGHT && LEFT <= Iy && Iy <= RIGHT);
}

bool collide3D(int i, int j) {
	return false;
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) {
		auto [pos, vel] = split_at(line, " @ ");
		x.pb(read_pt(pos));
		v.pb(read_pt(vel));
	}

	LEFT  = sz(x) >= 100 ? 200000000000000 :  7;
	RIGHT = sz(x) >= 100 ? 400000000000000 : 27;

	REP(i, sz(x)) REP(j, i) {
		if (collide2D(i, j)) {
			sumA++;
			if (collide3D(i, j)) sumB++;
		}
	}

	cout << "Part A: " << sumA << endl;

	pt shift_x = x[0], shift_v = v[0];
	REP(i, sz(x)) x[i] = x[i] - shift_x, v[i] = v[i] - shift_v;

	pt MIN{LLONG_MAX, LLONG_MAX, LLONG_MAX}, MAX{LLONG_MIN, LLONG_MIN, LLONG_MIN};
	REP(i, sz(x)) MIN.x = min(MIN.x, x[i].x);
	REP(i, sz(x)) MIN.y = min(MIN.y, x[i].y);
	REP(i, sz(x)) MIN.z = min(MIN.z, x[i].z);
	REP(i, sz(x)) MAX.x = max(MAX.x, x[i].x);
	REP(i, sz(x)) MAX.y = max(MAX.y, x[i].y);
	REP(i, sz(x)) MAX.z = max(MAX.z, x[i].z);

	cout << "[" << MIN.x << ", " << MAX.x << "]" << endl;
	cout << "[" << MIN.y << ", " << MAX.y << "]" << endl;
	cout << "[" << MIN.z << ", " << MAX.z << "]" << endl;

	cout << "Part B: " << sumB << endl;
	return 0;
}
