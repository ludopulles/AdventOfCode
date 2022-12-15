#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
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

vii S;
vi D;
map<int, vi> B;

int main() {
	string line;
	while (getline(cin, line), cin) {
		int pos = 12;
		int x = parseInt(line, pos);
		pos += 4;
		int y = parseInt(line, pos);
		S.eb(x, y);

		pos += 25;
		int xx = parseInt(line, pos);
		pos += 4;
		int yy = parseInt(line, pos);

		D.eb(abs(xx - x) + abs(yy - y));
		B[yy].pb(xx);
	}

	for (auto &[i, v] : B) {
		sort(begin(v), end(v));
		v.resize(unique(all(v)) - begin(v));
	}

	ll miny = INT_MAX, maxy = INT_MIN;
	REP(i, sz(S))
		miny = min(miny, S[i].y - D[i]),
		maxy = max(maxy, S[i].y + D[i]);

	ll total = 0;
	rep(y, miny, maxy + 1) {
		vii evts;
		REP(i, sz(S)) {
			if (S[i].y - D[i] <= y && y <= S[i].y + D[i]) {
				int minx = S[i].x - D[i] + abs(y - S[i].y);
				int maxx = S[i].x + D[i] - abs(y - S[i].y);
				evts.eb(minx, 0);
				evts.eb(maxx, 1);
			}
		}

		sort(begin(evts), end(evts));

		int currow = 0, cur_cnt = 0, lstx = INT_MIN;
		for (auto [x, inc] : evts) {
			if (cur_cnt == 0) lstx = x;

			if (inc == 0) cur_cnt++;
			else cur_cnt--;

			if (cur_cnt == 0) {
				// printf("At y = %d: [%d, %d]\n", y, lstx, x),
				currow += (x - lstx) + 1;
			}
		}

		currow -= sz(B[y]);

		// printf("%d: (%d-%d=) %d\n", y, currow + sz(B[y]), sz(B[y]), currow);
		total += currow;

		if (y == 10 || y == 2000000) {
			printf("%d: %lld\n", y, currow);
		}
	}

	printf("%lld\n", total);
	return 0;
}
