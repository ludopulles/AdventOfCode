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

typedef pair<int,ii> T;

vector<string> risk;
int D[1000][1000];
ii prv[1000][1000] = {};
bool seen[1000][1000] = {};

int dx[8] = { 0, -1, 0, 1, 1, -1, -1, 1 };
int dy[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };

int main() {
	string line;
	while (getline(cin, line))
		risk.pb(line);
	int d0 = sz(risk), d1 = sz(risk[0]);

	REP(x, d0) REP(y, d1) D[x][y] = INT_MAX;

	priority_queue<T, vector<T>, greater<T>> q;
	q.emplace(D[0][0] = 0, ii(0,0));
	while (!q.empty()) {
		ii loc = q.top().y;
		q.pop();
		if (seen[loc.x][loc.y]) continue;
		seen[loc.x][loc.y] = true;

		REP(d, 4) {
			ii nloc(loc.x + dx[d], loc.y + dy[d]);
			if (0 <= nloc.x && nloc.x < d0 && 0 <= nloc.y && nloc.y < d1) {
				int alt = D[loc.x][loc.y] + risk[nloc.x][nloc.y] - '0';
				if (alt < D[nloc.x][nloc.y])
					q.emplace(D[nloc.x][nloc.y] = alt, nloc),
					prv[nloc.x][nloc.y] = loc;
			}
		}
	}

	REP(x, d0) {
		REP(y, d1)
			cout << D[x][y] << " ";
		cout << endl;
	}

	vector<ii> path;
	for (ii cur(d0-1, d1-1); cur != ii(0, 0); cur = prv[cur.x][cur.y]) {
		path.pb(cur);
	}
	path.eb(0, 0);
	reverse(all(path));

	for (ii p : path)
		cout << p.x << "," << p.y << ": " << D[p.x][p.y] << endl;

	return 0;
}
