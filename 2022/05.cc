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

vector<char> stacksA[9], stacksB[9];

int main() {
	string line;
	int nstacks = 0;
	while (getline(cin, line) && line[1] != '1') {
		nstacks = 0;
		for (int loc = 1; nstacks < 9 && loc < sz(line); nstacks++, loc += 4) {
			if (line[loc] != ' ') stacksA[nstacks].pb(line[loc]);
		}
	}
	getline(cin, line);

	REP(i, nstacks) reverse(all(stacksA[i])), stacksB[i] = stacksA[i];

	vector<tuple<int,int,int>> moves;

	while (getline(cin, line)) {
		stringstream ss(line);
		string tmp;
		int A, B, C;
		ss >> tmp >> A >> tmp >> B >> tmp >> C;
		moves.eb(A, B - 1, C - 1);
	}

	for (auto [A,B,C] : moves) {
		REP(i, A) {
			stacksA[C].pb(stacksA[B].back());
			stacksA[B].pop_back();
		}

		stacksB[C].insert(stacksB[C].end(), stacksB[B].end() - A, stacksB[B].end());
		stacksB[B].resize(sz(stacksB[B]) - A);
	}

	printf("Part A: ");
	REP(i, nstacks) printf("%c", stacksA[i].back());
	printf("\n");

	printf("Part B: ");
	REP(i, nstacks) printf("%c", stacksB[i].back());
	printf("\n");


	return 0;
}
