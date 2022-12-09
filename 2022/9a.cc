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

set<ii> seen;

map<char, int> dx = {{'R',1}, {'L',-1}, {'U',0}, {'D',0}};
map<char, int> dy = {{'R',0}, {'L',0}, {'U',1}, {'D',-1}};

int sgn(int x) { return (x>0) - (x<0); }

int main() {
	int hx = 0, hy = 0;
	int tx = 0, ty = 0;

	string cmd;
	while (getline(cin, cmd), cin) {
		stringstream ss(cmd);
		char dir;
		int steps;
		ss >> dir >> steps;

		while (steps--) {
			hx += dx[dir];
			hy += dy[dir];

			if (abs(tx - hx) >= 2) {
				tx += sgn(hx - tx);
				ty += sgn(hy - ty);
			} else if (abs(ty - hy) >= 2) {
				tx += sgn(hx - tx);
				ty += sgn(hy - ty);
			}
			cout << hx << "," << hy << " -> " << tx << "," << ty << endl;
			seen.emplace(tx, ty);
		}
	}

	cout << seen.size() << endl;

	return 0;
}
