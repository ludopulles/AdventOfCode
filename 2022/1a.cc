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

	vector<vi> items;
	vi cur;
	while (getline(cin, line), cin) {
		if (line.empty()) {
			// end of current 
			items.pb(cur);
			cur.clear();
			continue;
		}

		int x;
		stringstream ss(line);
		ss >> x;
		cur.pb(x);
	}

	int res = 0;
	for (vi v : items) {
		int s = accumulate(all(v), 0);
		res = max(res, s);
	}
	cout << res << endl;

	return 0;
}
