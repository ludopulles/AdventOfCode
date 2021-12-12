#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)

vi parse(string line) {
	replace(line.begin(), line.end(), ',', ' ');
	stringstream ss(line);
	vi v;
	for (ll x; ss >> x; v.push_back(x));
	return v;
}

int main() {
	string line;
	getline(cin, line);

	vi xs = parse(line);
	sort(xs.begin(), xs.end());

	ll cost = 0;
	for (int i=0, j=xs.size()-1; i<j; i++, j--)
		cost += xs[j] - xs[i];
	cout << cost << endl;
	return 0;
}
