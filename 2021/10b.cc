#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())

map<char,char> M = { {'(',')'}, {'[',']'}, {'{','}'}, {'<','>'} };
map<char, int> S = { {')',1}, {']',2}, {'}',3}, {'>',4} };

int main() {
	string line;
	vi v;
	while (getline(cin, line)) {
		vector<char> opening;
		char invChar = '\0';
		for (char ch : line) {
			if (M.find(ch) != M.end())
				opening.push_back(M[ch]);
			else if (ch == opening.back()) {
				opening.pop_back();
			else {
				invChar = ch;
				break;
			}
		}
		if (!invChar) {
			reverse(opening.begin(), opening.end());
			ll inc = 0;
			for (char ch : opening) inc = 5*inc + S[ch];
			v.push_back(inc);
		}
	}

	sort(v.begin(), v.end());
	cout << v[v.size()/2] << endl;
	return 0;
}
