#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)

vi parse(string line) {
	for (char &ch : line)
		if (ch == ',') ch = ' ';
	stringstream ss(line);
	vi v;
	ll x;
	while (ss >> x)
		v.push_back(x);
	return v;
}


int main() {
	string line;
	getline(cin, line);

	vi xs = parse(line);
	sort(xs.begin(), xs.end());
	int n = xs.size();

	ll mcost = LLONG_MAX;
	for (ll x = xs[0]; x < xs[n-1]; x++) {
		ll cost = 0;
		for (ll y : xs) {
			ll dx = abs(y-x);
			cost += dx*(dx+1)/2;
		}
		mcost = min(mcost, cost);
	}

	cout << mcost << endl;
	return 0;
}
