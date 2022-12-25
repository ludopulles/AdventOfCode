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
	vi itemsA[8], itemsB[8];
	string ops[8];
	ll op_val[8], divnr[8], nlooked[8] = {}, ifT[8], ifF[8], N = 0, bigmod = 1;
	for (string line; getline(cin, line); ) {
		getline(cin, line);
		line = line.substr(18);
		for (char &ch : line) if (ch == ',') ch = ' ';
		stringstream ss(line);
		for (int x; ss >> x, ss; ) itemsA[N].pb(x);

		getline(cin, line);
		ops[N] = line.substr(19);

		if (ops[N].back() != 'd') {
			ss = stringstream(line.substr(25));
			ss >> op_val[N];
		}

		getline(cin, line);
		ss = stringstream(line.substr(21));
		ss >> divnr[N];
		getline(cin, line);
		ifT[N] = line[29] - '0';
		getline(cin, line);
		ifF[N] = line[30] - '0';
		assert(ifT[N] != N && ifF[N] != N);

		getline(cin, line);
		N++;
	}
	REP(i, N) itemsB[i] = itemsA[i];

	for (int round = 1; round <= 20; round++) {
		for (int m = 0; m < N; m++) {
			nlooked[m] += itemsA[m].size();
			for (ll preval : itemsA[m]) {
				// apply the operation
				ll val = preval + op_val[m];
				if (ops[m] == "old * old") val = preval * preval;
				else if (ops[m][4] == '*') val = preval * op_val[m];

				val /= 3;
				if (val % divnr[m] == 0) itemsA[ifT[m]].pb(val);
				else itemsA[ifF[m]].pb(val);
			}
			itemsA[m].clear();
		}
	}

	sort(nlooked, nlooked + N);
	printf("Part A: %lld\n", nlooked[N - 2] * nlooked[N - 1]);

	memset(nlooked, 0, sizeof nlooked);
	for (int m = 0; m < N; m++) bigmod *= divnr[m];

	for (int round = 1; round <= 10'000; round++) {
		for (int m = 0; m < N; m++) {
			nlooked[m] += itemsB[m].size();
			for (ll preval : itemsB[m]) {
				// apply the operation
				ll val = preval + op_val[m];
				if (ops[m] == "old * old") val = preval * preval;
				else if (ops[m][4] == '*') val = preval * op_val[m];

				val %= bigmod;
				if (val % divnr[m] == 0) itemsB[ifT[m]].pb(val);
				else itemsB[ifF[m]].pb(val);
			}
			itemsB[m].clear();
		}
	}

	sort(nlooked, nlooked + N);
	printf("Part B: %lld\n", nlooked[N - 2] * nlooked[N - 1]);
	return 0;
}
