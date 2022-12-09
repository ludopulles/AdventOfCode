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
	ii pos[10] = {};

	string cmd;
	while (getline(cin, cmd), cin) {
		stringstream ss(cmd);
		char dir;
		int steps;
		ss >> dir >> steps;

		while (steps--) {
			pos[0].x += dx[dir];
			pos[0].y += dy[dir];

			for (int i = 0; i < 9; i++) {
				if (abs(pos[i+1].x - pos[i].x) >= 2 || abs(pos[i+1].y - pos[i].y) >= 2) {
					pos[i+1].x += sgn(pos[i].x - pos[i+1].x);
					pos[i+1].y += sgn(pos[i].y - pos[i+1].y);
				}
			}
			// cout << hx << "," << hy << " -> " << tx << "," << ty << endl;
			seen.insert(pos[9]);
		}
	}

	cout << seen.size() << endl;

	return 0;
}
