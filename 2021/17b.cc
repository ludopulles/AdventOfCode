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

int main() {
	string line;
	getline(cin, line);
	replace(all(line), '=', ' ');
	replace(all(line), '.', ' ');
	replace(all(line), ',', ' ');
	stringstream ss(line.substr(12));
	int x0, x1, y0, y1; char ch;
	ss >> ch >> x0 >> x1 >> ch >> y0 >> y1;

	cout << x0 << " - " << x1 << endl;
	cout << y0 << " - " << y1 << endl;
	cout << endl;

	int fire_x = 0;
	while (fire_x * (fire_x+1) / 2 < x0) fire_x++;
	assert(fire_x * (fire_x+1)/2 <= x1);
	int fire_xp = fire_x;
	while (fire_xp * (fire_xp+1) / 2 <= x1) fire_xp++;
	fire_xp--;

	int maxH = 0;
	for (int yup = 0; yup <= 1000; yup++) {
		int cury = 0, vely = yup, steps = 0;
		while (cury > y1) {
			cury += vely;
			vely--;
			steps++;
		}
		if (cury >= y0) {
			// cerr << "Valid: " << yup << endl;
			// cerr << "max Height: " << (yup*(yup+1)/2) << endl;
			maxH = yup;
		}
	}
	cerr << "xs: " << fire_x << " - " << fire_xp << endl;
	cerr << "max height: " << maxH << endl;

	auto shoot = [&](int vx, int vy) -> bool {
		int x=0, y=0;
		while (y > y0) {
			if (x0 <= x && x <= x1 && y0 <= y && y <= y1)
				return true;
			x += vx; y += vy;
			if (vx) vx--;
			vy--;
		}
		return x0 <= x && x <= x1 && y0 <= y && y <= y1;
	};

	int res = 0;
	for (int x = fire_x; x <= x1; x++) {
		for (int y = y0; y <= maxH; y++) {
	// for (int x = 0; x <= 1000; x++) {
		// for (int y = -1000; y <= 1000; y++) {
			if (shoot(x, y)) {
				res++;
				// cout << x << ", " << y << endl;
			}
		}
	}
	cout << res << endl;

	return 0;
}
