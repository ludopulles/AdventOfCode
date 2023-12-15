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

/**************************************************************************************************
 * Code for today is below:
 *************************************************************************************************/

int HASH(const string &s) {
	int res = 0;
	for (char ch : s) res = ((res + ch) * 17) % 256;
	return res;
}

vector<pair<string, int>> hashmap[256];

void erase_entry(const string &label) {
	int h = HASH(label);
	for (int i = 0; i < sz(hashmap[h]); i++) {
		if (hashmap[h][i].x == label) {
			hashmap[h].erase(hashmap[h].begin() + i);
			break;
		}
	}
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	getline(cin, line);

	for (string part : split_str(line, ",")) {
		sumA += HASH(part);

		if (part.back() == '-') {
			string label = part.substr(0, part.size() - 1);
			erase_entry(label);
		} else {
			auto v = split_str(part, "=");
			string label = v[0];
			int num = parse_int(v[1]);
			int h = HASH(label), found = false;
			for (int i = 0; i < sz(hashmap[h]); i++) {
				if (hashmap[h][i].x == label) {
					hashmap[h][i].y = num; found = true;
					break;
				}
			}
			if (!found) hashmap[HASH(label)].eb(label, num);
		}
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
