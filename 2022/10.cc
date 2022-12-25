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

	ll ans = 0;
	for (int time = 20; time <= 220; time += 40) {
		ans += time * values[time];
	}

	printf("Part A: %lld\n", ans);

	vector<bool> grid(6 * 40 + 1, false);

	for (int time = 1; time <= 240; time++) {
		if (abs(((time-1) % 40) - values[time]) <= 1) {
			grid[time] = true;
		}
	}

	printf("Part B:\n");
	for (int row = 1, pos = 1; row <= 6; row++) {
		for (int col = 1; col <= 40; col++, pos++) {
			printf("%c", grid[pos] ? '#' : ' ');
		}
		printf("\n");
	}
	return 0;
}
