#include "header.h"

typedef long double ld;

// ================================================================================
struct pt { ll x, y, z; };
typedef pair<ld, ld> ptd;

ostream& operator<<(ostream &out, const pt &p) { return out << '(' << p.x << ',' << p.y << ',' << p.z << ')'; }
ostream& operator<<(ostream &out, const ii &p) { return out << '(' << p.x << ',' << p.y << ')'; }

pt read_pt(const string &s) {
	vi v = parse_ints(split_str(s, ", "));
	return pt{ v[0], v[1], v[2] };
}

pt operator-(const pt &a, const pt &b) { return pt{ a.x - b.x, a.y - b.y, a.z - b.z }; }
pt operator+(const pt &a, const pt &b) { return pt{ a.x + b.x, a.y + b.y, a.z + b.z }; }
ii cast(const pt &p) { return ii{ p.x, p.y }; }

ii operator+(const ii &a, const ii &b) { return ii{ a.x + b.x, a.y + b.y }; }
ii operator-(const ii &a, const ii &b) { return ii{ a.x - b.x, a.y - b.y }; }
ii operator*(const ii &a, ll sc) { return ii{ a.x * sc, a.y * sc }; }
ptd operator*(const ii &a, ld sc) { return make_pair(a.x * sc, a.y * sc); }
ptd operator*(const ptd &a, ld sc) { return make_pair(a.x * sc, a.y * sc); }
pt operator*(const pt &a, ll sc) { return pt{a.x * sc, a.y * sc, a.z * sc}; }

ptd operator+(const ptd &a, const ptd &b) { return ptd{ a.x + b.x, a.y + b.y }; }
ptd operator-(const ptd &a, const ptd &b) { return ptd{ a.x - b.x, a.y - b.y }; }

ll operator^(const ii &a, const ii &b) { return a.x * b.y - a.y * b.x; }
ll operator*(const ii &a, const ii &b) { return a.x * b.x + a.y * b.y; }

bool linesIntersect(ii a, ii b, ii c, ii d) {
	return ((a-b) ^ (c-d)) != 0;
}

ptd lineLineIntersection(ii a, ii b, ii c, ii d) {
	ld det = (a-b) ^ (c-d);
	assert(det != 0);
	return ((c-d)*(a^b) - (a-b)*(c^d)) * (ld(1.0)/det);
}

// ================================================================================
vector<pt> x, v;
int n;
ll LEFT, RIGHT;

bool collide2D(int i, int j) {
	ii pi = cast(x[i]), qi = pi + cast(v[i]);
	ii pj = cast(x[j]), qj = pj + cast(v[j]);
	if (!linesIntersect(pi, qi, pj, qj)) return false;

	auto [Ix, Iy] = lineLineIntersection(pi, qi, pj, qj);
	ld ti = v[i].x != 0 ? (Ix - x[i].x) / v[i].x : (Iy - x[i].y) / v[i].y;;
	ld tj = v[j].x != 0 ? (Ix - x[j].x) / v[j].x : (Iy - x[j].y) / v[j].y;;

	return ti >= 0 && tj >= 0 && (LEFT <= Ix && Ix <= RIGHT && LEFT <= Iy && Iy <= RIGHT);
}

// ================================================================================
ll psqrt(ll x) {
	ll n = floor(sqrt(x));
	while ((n + 1) * (n + 1) <= x) n++;
	return n;
}

bool operator==(const pt &a, const pt &b) { return a.x == b.x && a.y == b.y && a.z == b.z; }

bool test_velocity(const pt vg, pt &xg) {
	ii v0 = cast(v[0] - vg), v1 = cast(v[1] - vg);
	ll det = v0 ^ v1;
	if (det == 0) return false;

	ii inter = v0 * (cast(x[1]) ^ v1) - v1 * (cast(x[0]) ^ v0);
	if (inter.x % det != 0 || inter.y % det != 0) return false;
	inter = ii(inter.x / det, inter.y / det);

	REP(i, 2) {
		pt vi = v[i] - vg;
		if (vi.x != 0 && (inter.x - x[i].x) % vi.x != 0) return false;
		if (vi.y != 0 && (inter.y - x[i].y) % vi.y != 0) return false;
	}
	ll t0 = v0.x != 0 ? (inter.x - x[0].x) / v0.x : (inter.y - x[0].y) / v0.y;
	ll t1 = v1.x != 0 ? (inter.x - x[1].x) / v1.x : (inter.y - x[1].y) / v1.y;

	if (t0 < 0) return false;
	if (t1 < 0) return false;

	xg = pt{ inter.x, inter.y, x[0].z + t0 * (v[0] - vg).z };
	if (xg.z != x[1].z + t1 * (v[1] - vg).z)
		return false;

	rep(i, 2, n) {
		pt vi = v[i] - vg;
		if (vi.x != 0 && (xg.x - x[i].x) % vi.x != 0) return false;
		if (vi.y != 0 && (xg.y - x[i].y) % vi.y != 0) return false;
		if (vi.z != 0 && (xg.z - x[i].z) % vi.z != 0) return false;

		ll ti = vi.x != 0 ? ((xg.x - x[i].x) / vi.x)
			:  (vi.y != 0 ? ((xg.y - x[i].y) / vi.y)
			:               ((xg.z - x[i].z) / vi.z));

		pt loc = x[i] + vi * ti;
		if (!(loc == xg)) return false;
	}

	return true;
}

// ================================================================================
int main() {
	ll sumA = 0;

	string line;
	while (getline(cin, line), cin) {
		auto [pos, vel] = split_at(line, " @ ");
		x.pb(read_pt(pos));
		v.pb(read_pt(vel));
	}
	n = sz(x);

	LEFT  = n >= 100 ? 200000000000000 :  7;
	RIGHT = n >= 100 ? 400000000000000 : 27;

	REP(i, n) REP(j, i)
		sumA += collide2D(i, j);
	cout << "Part A: " << sumA << endl;

	pt loc;
	for (ll normsq = 0;; normsq++) {
		ll vx0 = psqrt(normsq);
		for (ll vx = -vx0; vx <= vx0; vx++) {
			ll vy0 = psqrt(normsq - vx * vx);
			for (ll vy = -vy0; vy <= vy0; vy++) {
				ll vz2 = normsq - vx * vx - vy * vy;
				ll usvz = psqrt(vz2);
				if (usvz * usvz != vz2) continue;
				for (ll vz : {-usvz, usvz}) {
					pt v{vx, vy, vz};
					if (test_velocity(v, loc)) {
						cout << "Solution: " << loc << " @ " << v << endl;
						return 0;
					}
				}
			}
		}
	}

	return 0;
}
