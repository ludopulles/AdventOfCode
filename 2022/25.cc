#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
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

vector<string> input;

ll to_num(string &line) {
	ll res = 0;
	for (char ch : line) {
		res *= 5;
		if (ch >= '0' && ch <= '2') res += (ch - '0');
		else if (ch == '-') res--;
		else { assert(ch == '='); res -= 2; }
	}
	return res;
}

string to_snafu(ll num) {
	string res;
	while (num != 0) {
		int dig = (int)(num % 5);
		if (dig < 0) dig += 5;
		num = (num - dig) / 5;

		if (dig <= 2) res.pb(dig + '0');
		else if (dig == 3) res.pb('='), num++;
		else if (dig == 4) res.pb('-'), num++;
	}
	reverse(all(res));
	return res;
}

int main() {
	string line;
	while (getline(cin, line), cin) {
		input.pb(line);
	}

	ll sumA = 0;
	for (string &s : input) {
		sumA += to_num(s);
		// printf("%s -> %lld\n", s.c_str(), to_num(s));
	}

	cout << "Part A: " << sumA << " = " << to_snafu(sumA) << endl;

	return 0;
}
