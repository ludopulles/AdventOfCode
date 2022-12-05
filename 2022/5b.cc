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

vector<char> stacks[9];

int main() {
	string line;
	while (getline(cin, line), line[1] != '1') {
		for (int idx = 0, loc = 1; idx < 9 && loc < line.size(); idx++, loc += 4) {
			if (line[loc] != ' ') stacks[idx].pb(line[loc]);
		}
	}

	REP(i, 9) reverse(all(stacks[i]));

	getline(cin, line);
	while (getline(cin, line), cin) {
		stringstream ss(line);
		string tmp;
		int A, B, C;
		ss >> tmp >> A >> tmp >> B >> tmp >> C;
		B--; C--;

		for (int i = 0; i < A; i++) {
			stacks[C].pb(stacks[B][stacks[B].size() - A + i]);
		}
		for (int i = 0; i < A; i++) {
			stacks[B].pop_back();
		}
	}

	REP(i, 9) {
		if (stacks[i].empty()) printf(" ");
		else printf("%c", stacks[i].back());
	}
	printf("\n");

	return 0;
}
