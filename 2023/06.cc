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

ll parse_int(const string &s) { int pos = 0; return parse_int(s, pos); }

vector<ll> parse_ints(const vector<string> &v) {
	vector<ll> res;
	transform(all(v), back_inserter(res), [](string s) { return (ll) parse_int(s); });
	return res;
}

vector<string> split_str(string s, string split) {
	size_t pos = 0, newpos = 0, n = split.size();
	vector<string> result;
	while ((newpos = s.find(split, pos)) != string::npos) {
		if (pos < newpos)
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

string replaceAll(const string &s, const string &from, const string &to) {
	string res;
	assert(from != "");
	size_t pos = 0, newpos;
	while ((newpos = s.find(from, pos)) != string::npos) {
		res += s.substr(pos, newpos - pos) + to;
		pos = newpos + from.size();
	}
	return res + s.substr(pos);
}

ll solveTask(ll t, ll d) {
	ll t1 = ceill((t - sqrtl(t*t - 4*d)) / 2);
	ll t2 = floorl((t + sqrtl(t*t - 4*d)) / 2);
	if (t1 * (t - t1) == d) ++t1;
	if (t2 * (t - t2) == d) --t2;
	return t2 - t1 + 1;
}

int main() {
	ll sumA = 1, sumB = 0;

	string line1, line2;
	getline(cin, line1);
	getline(cin, line2);

	vector<ll> times = parse_ints(split_str(line1.substr(11), " "));
	vector<ll> dists = parse_ints(split_str(line2.substr(11), " "));

	for (int i = 0; i < sz(times); i++) {
		ll t = times[i], d = dists[i];
		sumA *= solveTask(t, d);
	}

	sumB = solveTask(parse_int(replaceAll(line1.substr(11), " ", "")),
					 parse_int(replaceAll(line2.substr(11), " ", "")));

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
