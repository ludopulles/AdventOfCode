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

struct P {
	int x, y, z;
	P() = default;
	P(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

	strong_ordering operator<=>(const P &rhs) const =default;

	P rotate(int r) const {
		assert(0 <= r && r <= 23);
		int zrot = r / 4, xyrot = r % 4;
		P copy(this->x, this->y, this->z);

		if (zrot < 4)
			REP(_, zrot) tie(copy.x, copy.z) = make_pair(-copy.z, copy.x);
		else if (zrot == 4)
			tie(copy.y, copy.z) = make_pair(copy.z, -copy.y);
		else if (zrot == 5)
			tie(copy.y, copy.z) = make_pair(-copy.z, copy.y);

		REP(_, xyrot) tie(copy.x, copy.y) = make_pair(-copy.y, copy.x);
		return copy;
	}
	P operator+(const P &rhs) const {
		return P(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
	P operator-(const P &rhs) const {
		return P(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}
};


typedef vector<P> S;

S rotate(const S &pts, int r) {
	S res;
	for (P p : pts) res.pb(p.rotate(r));
	return res;
}

vector<S> A;

S parseScanner() {
	string line;
	if (!getline(cin, line))
		return {};

	cout << "Received: " << line << endl;
	assert(line.substr(0, 4) == "--- ");
	S res;
	while (getline(cin, line) && !line.empty()) {
		replace(all(line), ',', ' ');
		stringstream ss(line);
		P pt;
		ss >> pt.x >> pt.y >> pt.z;
		res.pb(pt);
	}
	return res;
}

bool matches(const S &pts, P &center, const set<P> &sol, P &to_point) {
	for (P candidate : sol) {
		int nmatch = 0;
		for (P p : pts) if (sol.find(candidate + (p-center)) != sol.end())
			nmatch++;
		if (nmatch >= 12) {
			to_point = candidate;
			return true;
		}
	}
	return false;
}

int main() {
	for (S v; !(v = parseScanner()).empty(); )
		A.pb(v);
	int ns = A.size();

	set<P> sol;
	for (P p : A[0]) sol.insert(p);

	vector<bool> seen(ns, false);
	seen[0] = true;
	int nseen = 1;

	while (nseen < ns) {
		REP(i, ns) if (!seen[i]) {
			// try to match with current positions
			REP(j, 24) {
				S rots = rotate(A[i], j);
				for (P p : rots) {
					P to_point;
					if (matches(rots, p, sol, to_point)) {
						for (P q : rots) sol.insert(to_point + (q-p));
						nseen++; seen[i] = true;
						break;
					}
				}
				if (seen[i]) break;
			}
		}
	}
	cout << "Total points: " << sol.size() << endl;

	return 0;
}
