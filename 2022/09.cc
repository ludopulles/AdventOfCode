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

ll sgn(ll x) { return (x>0) - (x<0); }

int main() {
	map<char, int> dx = {{'R',1}, {'L',-1}, {'U',0}, {'D',0}};
	map<char, int> dy = {{'R',0}, {'L',0}, {'U',1}, {'D',-1}};
	ii pos[10] = {};
	set<ii> seen2, seen10;
	char dir;
	int steps;

	while (cin >> dir >> steps) {
		while (steps--) {
			pos[0].x += dx[dir];
			pos[0].y += dy[dir];

			REP(i, 9) if (abs(pos[i+1].x - pos[i].x) >= 2 || abs(pos[i+1].y - pos[i].y) >= 2) {
				pos[i+1].x += sgn(pos[i].x - pos[i+1].x);
				pos[i+1].y += sgn(pos[i].y - pos[i+1].y);
			}

			seen2.insert(pos[1]);
			seen10.insert(pos[9]);
		}
	}

	printf("Part A: %d\n", sz(seen2));
	printf("Part B: %d\n", sz(seen10));
	return 0;
}
