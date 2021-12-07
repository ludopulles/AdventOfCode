#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)

ll nfish[1000][9] = {};

int main() {
	string line;
	getline(cin, line);

	for (char ch : line) {
		if ('1' <= ch && ch <= '9')
			nfish[0][ch - '0']++;
	}

	rep(d, 1, 257) {
		rep(i, 0, 8)
			nfish[d][i] = nfish[d-1][i+1];
		nfish[d][6] += nfish[d-1][0];
		nfish[d][8] += nfish[d-1][0];
	}

	REP(d, 11) {
		REP(i, 9) cerr << nfish[d][i] << " ";
		cerr << endl;
	}
	ll res = 0;
	REP(i, 9) res += nfish[256][i];
	cout << res << endl;
	return 0;
}
