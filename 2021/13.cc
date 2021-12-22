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

bool C[100][100] = {};

int main() {
	string line;

	map<ii, int> pts;
	while (getline(cin, line), line != "") {
		replace(all(line), ',', ' ');
		stringstream ss(line);
		ll x, y;
		ss >> x >> y;
		pts[ii(x, y)]++;
	}

	vector<pair<char, int>> folds;
	while (getline(cin, line)) {
		replace(all(line), '=', ' ');
		stringstream ss(line);
		string t; char dir; int num;
		ss >> t >> t >> dir >> num;
		folds.eb(dir, num);
	}

	for (auto [d,L] : folds) {
		map<ii, int> npts;
		for (auto [p, n] : pts) {
			ii q(p);
			if (d == 'x' && q.x > L) q.x = 2*L - q.x;
			if (d == 'y' && q.y > L) q.y = 2*L - q.y;
			npts[q] += n;
		}
		pts = npts;
		cout << "Point count: " << pts.size() << endl;
	}

	for (auto [p, n] : pts)
		C[p.y][p.x] = true;
	
	REP(i, 7) { 
		REP(j, 40) {
			if (C[i][j]) cout << '!';
			else cout << ' ';
		}
		cout << endl;
	}

	return 0;
}
