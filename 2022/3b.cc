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

		fill_n(occ, 256, 0);
		for (char ch : line) occ[ch] |= 1;
		getline(cin, line);
		for (char ch : line) occ[ch] |= 2;
		getline(cin, line);
		for (char ch : line) occ[ch] |= 4;

		for (char ch = 'a'; ch <= 'z'; ch++)
			if (occ[ch] == 7) {
				result += ch - 'a' + 1;
			}
		for (char ch = 'A'; ch <= 'Z'; ch++)
			if (occ[ch] == 7) {
				result += ch - 'A' + 27;
			}
	}

	cout << result << endl;
	return 0;
}
