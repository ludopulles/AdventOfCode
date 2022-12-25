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

vector<string> lines;

int main() {
	for (string line; getline(cin, line); lines.pb(line));
		

	int occ[256], partA = 0, partB = 0;
	for (const string &line : lines) {
		int n = sz(line) / 2;

		fill_n(occ, 256, 0);

		for (int i = 0; i < n; i++) occ[(int) line[i]] = 1;
		for (int i = n; i < n + n; i++) occ[(int) line[i]] |= 2;

		for (char ch = 'a'; ch <= 'z'; ch++) {
			if (occ[(int) ch] == 3) partA += ch - 'a' + 1;
			if (occ[(int) (ch + 'A' - 'a')] == 3) partA += ch - 'a' + 27;
		}
	}

	for (int i = 0; i < sz(lines); i += 3) {
		fill_n(occ, 256, 0);
		for (char ch : lines[i + 0]) occ[(int) ch] |= 1;
		for (char ch : lines[i + 1]) occ[(int) ch] |= 2;
		for (char ch : lines[i + 2]) occ[(int) ch] |= 4;

		for (char ch = 'a'; ch <= 'z'; ch++)
			if (occ[(int) ch] == 7) partB += ch - 'a' + 1;
		for (char ch = 'A'; ch <= 'Z'; ch++)
			if (occ[(int) ch] == 7) partB += ch - 'A' + 27;
	}

	printf("Part A: %d\n", partA);
	printf("Part B: %d\n", partB);
	return 0;
}
