#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
#define pb push_back
#define eb emplace_back
#define x first
#define y second

namespace std { template<class T1, class T2>
struct hash<pair<T1,T2>> { public:
	size_t operator()(const pair<T1,T2> &p) const {
		size_t x = hash<T1>()(p.x), y = hash<T2>()(p.y);
		return x ^ (y + 0x9e3779b9 + (x<<6) + (x>>2));
	}
}; }

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

vi parse_ints(const vector<string> &v) {
	vi res;
	transform(all(v), back_inserter(res), [](string s) { return (ll) parse_int(s); });
	return res;
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

vector<string> split_str(const string &s, char c) { return split_str(s, string(1, c)); }
pair<string, string> split_at(const string &s, char c) { return split_at(s, string(1, c)); }
