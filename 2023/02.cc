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

bool is_num(const string &s, int &pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parseInt(const string &s, int &pos) {
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

int main() {
	string line, _;
	int sumA = 0, sumB = 0;

	while (getline(cin, line), cin) {
		int id;
		auto V = split_str(line, ": ");
		stringstream ss(V[0]); ss >> _ >> id;
		line = V[1];

		map<string, int> maxtaken;
		for (string draws : split_str(line, "; ")) {
			map<string, int> taken;
			for (string nr_col : split_str(draws, ", ")) {
				stringstream ss(nr_col);
				int nr; string col;
				ss >> nr >> col;
				taken[col] += nr;
			}

			for (auto [col, nr] : taken)
				maxtaken[col] = max(maxtaken[col], nr);
		}

		if (maxtaken["red"] <= 12 && maxtaken["green"] <= 13 && maxtaken["blue"] <= 14)
			sumA += id;

		sumB += maxtaken["red"] * maxtaken["green"] * maxtaken["blue"];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;

	return 0;
}
