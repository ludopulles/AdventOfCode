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

vi items[8];
string ops[8];
int op_val[8], divnr[8], nlooked[8] = {}, ifT[8], ifF[8];

int main() {
	string line;
	int nmonkeys = 0;
	while (getline(cin, line), cin) {
		getline(cin, line);
		line = line.substr(18);
		for (char &ch : line) if (ch == ',') ch = ' ';
		stringstream ss(line);
		for (int x; ss >> x, ss; ) items[nmonkeys].pb(x);

		getline(cin, line);
		ops[nmonkeys] = line.substr(19);

		if (ops[nmonkeys].back() != 'd') {
			ss = stringstream(line.substr(25));
			ss >> op_val[nmonkeys];
		}

		getline(cin, line);
		ss = stringstream(line.substr(21));
		ss >> divnr[nmonkeys];
		getline(cin, line);
		ifT[nmonkeys] = line[29] - '0';
		getline(cin, line);
		ifF[nmonkeys] = line[30] - '0';
		assert(ifT[nmonkeys] != nmonkeys && ifF[nmonkeys] != nmonkeys);

		getline(cin, line);
		nmonkeys++;
	}


	for (int round = 1; round <= 20; round++) {
		for (int m = 0; m < nmonkeys; m++) {
			nlooked[m] += items[m].size();
			for (ll preval : items[m]) {
				// apply the operation
				ll val;
				if (ops[m] == "old * old")
					val = preval * preval;
				else if (ops[m][4] == '*')
					val = preval * op_val[m];
				else val = preval + op_val[m];
				val /= 3;
				if (val % divnr[m] == 0)
					items[ifT[m]].pb(val);
				else
					items[ifF[m]].pb(val);
			}
			items[m].clear();
		}
	}

	for (int m = 0; m < nmonkeys; m++)
		cerr << nlooked[m] << " ";
	cerr << endl;

	return 0;
}
