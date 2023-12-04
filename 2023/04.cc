#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
#define pb push_back
#define eb emplace_back
#define x first
#define y second

bool is_num(const string &s, int pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parse_int(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

vector<string> split_str(string s, string split) {
	size_t pos = 0, newpos = 0, n = split.size();
	vector<string> result;
	while ((newpos = s.find(split, pos)) != string::npos) {
		result.push_back(s.substr(pos, newpos - pos));
		pos = newpos + n;
	}
	if (pos < s.size()) result.push_back(s.substr(pos));
	return result;
}

pair<string, string> split_at(string s, string split) {
	size_t pos = s.find(split, 0);
	assert(pos != string::npos);

	return make_pair(s.substr(0, pos), s.substr(pos + split.size()));
}



int main() {
	ll sumA = 0, sumB = 0;

	string line;
	vector<int> ncards;
	while (getline(cin, line), cin) {
		auto [game, scard] = split_at(line, ": ");
		auto [winning, having] = split_at(scard, " | ");

		vector<string> _wins = split_str(winning, " ");
		set<string> wins = set<string>(all(_wins));
		wins.erase("");

		int nfound = 0;
		for (string have : split_str(having, " ")) {
			if (have == "") continue;
			nfound += wins.find(have) != wins.end();
		}
		ncards.pb(nfound);

		if (nfound) sumA += 1 << (nfound - 1);
	}

	vector<int> nwins(sz(ncards), 0);
	for (int i = sz(ncards) - 1; i >= 0; i--) {
		nwins[i] = 1;
		if (ncards[i]) {
			for (int j = 1; j <= ncards[i]; j++)
				nwins[i] += nwins[i + j];
		}
		sumB += nwins[i];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
