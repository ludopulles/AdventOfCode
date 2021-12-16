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

	map<pair<char, char>, char> ops;
	for (string fr, arr, to; cin >> fr >> arr >> to; ) {
		pair<char, char> pr(fr[0], fr[1]);
		assert(ops.find(pr) == ops.end());
		ops[pr] = to[0];
	}

	map<pair<char, char>, ll> v, nv;
	for (int i=0; i+1 < sz(line); i++)
		v[make_pair(line[i], line[i+1])] += 1LL;
	v[make_pair(line.back(), '\0')] = 1;

	for (int i = 1; i <= 50; i++) {
		for (auto [pr,nr] : v) {
			if (ops.find(pr) == ops.end())
				nv[pr] += nr;
			else {
				char mid = ops[pr];
				nv[make_pair(pr.x, mid)] += nr;
				nv[make_pair(mid, pr.y)] += nr;
			}
		}

		v = nv;
		nv.clear();

		map<char, ll> perChar;
		for (auto [pr,nr] : v) perChar[pr.x] += nr;

		ll s = 0, maxV = -1, minV = LLONG_MAX;
		for (auto [c,nr] : perChar) {
			s += nr;
			maxV = max(maxV, nr);
			minV = min(minV, nr);
		}
		cout << i << ": " << s << " " << (maxV - minV) << endl;
	}

	return 0;
}
