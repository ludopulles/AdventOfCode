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

	vi values;
	values.pb(1);
	values.pb(1);

	while (getline(cin, line), cin) {
		if (line[0] == 'n') {
			values.pb(values.back());
		} else {
			stringstream ss(line);
			string tmp;
			int val;
			ss >> tmp >> val;

			assert(tmp == "addx");
			values.pb(values.back());
			values.pb(values.back() + val);
		}
	}

	// for (int t = 0; t <= 40; t++) cerr << t << ": " << values[t] << endl;

	ll ans = 0;
	for (int time = 20; time <= 220; time += 40) {
		// cerr << time << ": " << values[time] << endl;
		ans += time * values[time];
	}

	cout << ans << endl;
	return 0;
}
