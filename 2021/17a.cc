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

	int fire_x = 0;
	while (fire_x * (fire_x+1) / 2 < x0) fire_x++;
	assert(fire_x * (fire_x+1)/2 <= x1);

	for (int yup = 0; ; yup++) {
		int cury = 0, vely = yup, steps = 0;
		while (cury > y1) {
			cury += vely;
			vely--;
			steps++;
		}
		if (cury >= y0) {
			cerr << "Valid: " << yup << endl;
			cerr << "max Height: " << (yup*(yup+1)/2) << endl;
		}
	}

	return 0;
}
