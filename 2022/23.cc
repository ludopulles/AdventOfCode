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

bool is_num(const string &s, int &pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

namespace std { template<class T1, class T2>
struct hash<pair<T1,T2>> { public:
	size_t operator()(const pair<T1,T2> &p) const {
		size_t x = hash<T1>()(p.x), y = hash<T2>()(p.y);
		return x ^ (y + 0x9e3779b9 + (x<<6) + (x>>2));
	}
}; }

vector<ii> pts;

int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

bool simulate(int dir0) {
	unordered_set<ii> taken(all(pts));
	unordered_map<ii, pair<int, ii>> proposed;

	bool res = false; // nothing changed
	REP(i, sz(pts)) {
		int x = pts[i].x, y = pts[i].y, dir = dir0;
		ii nxt_pt = ii(x, y);

		bool has_neighbour = false;
		for (int xd = -1; xd <= 1; xd++) for (int yd = -1; yd <= 1; yd++)
			if ((xd != 0 || yd != 0) && taken.find(ii(x + xd, y + yd)) != taken.end()) {
				has_neighbour = true;
				break;
			}

		if (!has_neighbour) continue;
		res = true;

		REP(j, 4) {
			if (taken.find(ii(x + dx[dir], y + dy[dir])) == taken.end() &&
				taken.find(ii(x + dx[dir] + dy[dir], y + dy[dir] + dx[dir])) == taken.end() && 
				taken.find(ii(x + dx[dir] - dy[dir], y + dy[dir] - dx[dir])) == taken.end()) {
				// Move this way.
				nxt_pt = ii(x + dx[dir], y + dy[dir]);
				break;
			}
			if (++dir == 4) dir = 0;
		}

		if (proposed.find(nxt_pt) != proposed.end()) {
			// Reset the position of this elf as well as the proposed one.
			pts[proposed[nxt_pt].first] = proposed[nxt_pt].second;
			// Don't change anything to this point
		} else {
			// Change this point to the new point
			proposed[nxt_pt] = make_pair(i, pts[i]);
			pts[i] = nxt_pt;
		}
	}
	return res;
}

int main() {
	string line;
	for (int x = 0; getline(cin, line), cin; x++) {
		for (int y = 0; y < sz(line); y++) {
			if (line[y] == '#') pts.eb(x, y);
		}
	}

	int iterations = 0, dir0 = 0;
	while (simulate(dir0)) {
		if (++iterations == 10) {
			vi xs, ys;
			for (auto [x,y] : pts) xs.pb(x), ys.pb(y);

			int W = *max_element(all(xs)) - *min_element(all(xs)) + 1;
			int H = *max_element(all(ys)) - *min_element(all(ys)) + 1;
			printf("%d x %d = %d\n", W, H, W * H);
			printf("Part A: %d\n", W * H - sz(pts));
		}

		if (++dir0 == 4) dir0 = 0;
	}

	printf("Part B: %d\n", iterations + 1);

	return 0;
}
