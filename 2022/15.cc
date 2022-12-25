#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
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
map<ll, vi> B;

ll count_row(ll y) {
	vii evts;
	REP(i, sz(S)) {
		if (S[i].y - D[i] <= y && y <= S[i].y + D[i]) {
			evts.eb(S[i].x - D[i] + abs(y - S[i].y), 0);
			evts.eb(S[i].x + D[i] - abs(y - S[i].y), 1);
		}
	}
	sort(all(evts));

	ll currow = 0, cur_cnt = 0, lstx = INT_MIN;
	for (auto [x, dec] : evts) {
		if (cur_cnt == 0) lstx = x;
		cur_cnt += (dec ? -1 : 1);
		if (cur_cnt == 0) currow += (x - lstx) + 1;
	}
	return currow - sz(B[y]);
}

bool taken(ll x, ll y) {
	REP(i, sz(S)) if (abs(x - S[i].x) + abs(y - S[i].y) <= D[i]) return true;
	return false;
}

int main() {
	for (string line; getline(cin, line); ) {
		int pos = 12;
		ll x = parseInt(line, pos), y = parseInt(line, pos += 4);
		ll xx = parseInt(line, pos += 25), yy = parseInt(line, pos += 4);

		S.eb(x, y);
		D.eb(abs(xx - x) + abs(yy - y));
		B[yy].pb(xx);
	}
	ll DIM = (S.size() == 14) ? 20 : 4000000;

	for (auto &[i, v] : B) {
		sort(begin(v), end(v));
		v.resize(unique(all(v)) - begin(v));
	}

	printf("Part A: %lld\n", count_row(DIM / 2));

	set<ll> xplusy, xminy;
	REP(i, sz(S))
		xplusy.insert(S[i].x + S[i].y - D[i] - 1), xminy.insert(S[i].x - S[i].y - D[i] - 1),
		xplusy.insert(S[i].x + S[i].y + D[i] + 1), xminy.insert(S[i].x - S[i].y + D[i] + 1);

	for (ll xpy : xplusy) for (ll xmy : xminy) {
		if ((xpy + xmy) % 2 == 1) continue;
		ll x = (xpy + xmy) / 2, y = (xpy - xmy) / 2;
		if (0 <= x && x <= DIM && 0 <= y && y <= DIM && !taken(x, y)) {
			printf("Part B: %lld\n", DIM * x + y);
		}
	}

	return 0;
}
