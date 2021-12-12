#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())

map<char,char> M = { {'(',')'}, {'[',']'}, {'{','}'}, {'<','>'} };
map<char, int> S = { {')',3}, {']',57}, {'}',1197}, {'>',25137} };

int main() {
	string line;
	ll res = 0;
	while (getline(cin, line)) {
		vector<char> opening;
		for (char ch : line) {
			if (M.find(ch) != M.end())
				opening.push_back(M[ch]);
			else if (ch == opening.back())
				opening.pop_back();
			else {
				res += S[ch];
				break;
			}
		}
	}

	cout << res << endl;
	return 0;
}
