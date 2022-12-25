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
	while (getline(cin, line)) {
		if (line.empty()) {
			items.push_back(cur);
			cur.clear();
			continue;
		} else {
			int x;
			stringstream ss(line);
			ss >> x;
			cur.push_back(x);
		}
	}
	items.push_back(cur);

	vi sums;
	for (vi v : items)
		sums.push_back(accumulate(all(v), 0LL));

	sort(all(sums));
	int n = sz(sums);

	printf("Part A: %lld\n", sums[n - 1]);
	printf("Part B: %lld\n", sums[n - 3] + sums[n - 2] + sums[n - 1]);
	return 0;
}
