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

const int MAX = 21;

// [score1][score2][pos1][pos2]
ll DP1[MAX][MAX][11][11] = {}, DP2[MAX][MAX][11][11] = {};

const ll W[7] = {1,3,6,7,6,3,1};

int main() {
	string line;
	getline(cin, line);
	int bx = line.back() - '0';
	getline(cin, line);
	int by = line.back() - '0';

	DP1[0][0][bx][by] = 1;
	ll p1w = 0, p2w = 0;
	REP(s, MAX+MAX+1) {
		REP(s1, min(MAX, s+1)) {
			int s2 = s - s1;
			if (s2 >= MAX) continue;
			// roll the dices
			rep(p1, 1, 11) rep(p2, 1, 11) for (int d = 3; d <= 9; d++) {
				ll nw = DP1[s1][s2][p1][p2] * W[d-3];
				int np = (p1 + d) % 10;
				if (!np) np = 10;
				int ns = s1 + np;
				if (ns >= MAX) p1w += nw;
				else DP2[ns][s2][np][p2] += nw;
			}
		}
		REP(s2, min(MAX, s+1)) {
			int s1 = s - s2;
			if (s1 >= MAX) continue;
			// roll the dices
			rep(p1, 1, 11) rep(p2, 1, 11) for (int d = 3; d <= 9; d++) {
				ll nw = DP2[s1][s2][p1][p2] * W[d-3];
				int np = (p2 + d) % 10;
				if (!np) np = 10;
				int ns = s2 + np;
				if (ns >= MAX) p2w += nw;
				else DP1[s1][ns][p1][np] += nw;
			}
		}
	}

	cout << p1w << " VS " << p2w << endl;
	return 0;
}
