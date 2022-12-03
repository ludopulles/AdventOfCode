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
	int occ[256];

	int result = 0;

	while (getline(cin, line), cin) {
		int n = line.size() / 2;

		fill_n(occ, 256, 0);
		for (int i = 0; i < n; i++) occ[line[i]] = 1;
		for (int i = n; i < n + n; i++) occ[line[i]] |= 2;

		for (char ch = 'a'; ch <= 'z'; ch++) {
			if (occ[ch] == 3) result += ch - 'a' + 1;
			if (occ[ch + 'A' - 'a'] == 3) result += ch - 'a' + 27;
		}
	}

	cout << result << endl;
	return 0;
}
