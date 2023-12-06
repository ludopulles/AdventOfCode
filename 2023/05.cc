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
		res = 10LL * res + (s[pos++] - '0');
	return sgn * res;
}

ll parse_int(const string &s) {
	int pos = 0;
	return parse_int(s, pos);
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


vector<vector<tuple<ll, ll, ll>>> maps;

int main() {
	ll sumA = 0, sumB = 0;

	string seeds, line;
	getline(cin, seeds);
	vector<string> seedsA = split_str(seeds.substr(7), " ");
	vector<ll> seedsI;
	transform(all(seedsA), back_inserter(seedsI), [](string s) { return (ll) parse_int(s); });

	getline(cin, line);
	assert(line == "");

	while (getline(cin, line), cin) {
		// line = "A-to-B map"
		vector<tuple<ll, ll, ll>> map;
		while (getline(cin, line), line != "") {
			vector<string> parts = split_str(line, " ");
			map.emplace_back(parse_int(parts[0]), parse_int(parts[1]), parse_int(parts[2]));
		}
		maps.push_back(map);
	}

	assert(maps.size() == 7U);

	sumA = LLONG_MAX;
	for (ll seed : seedsI) {
		ll cur_id = seed;
		for (int i = 0; i < 7; i++) {
			ll next_id = cur_id;
			for (auto [a, b, c] : maps[i]) {
				if (b <= cur_id && cur_id < b + c) {
					next_id = a + (cur_id - b);
					break;
				}
			}
			cout << cur_id << " -> ";
			cur_id = next_id;
		}
		cout << " --> " << cur_id << endl;
		sumA = min(sumA, cur_id);
	}

	cout << "Part A: " << sumA << endl;

	vector<ii> seedPairs;
	for (auto it = seedsI.begin(); it != seedsI.end(); ) {
		ll a = *it++, b = *it++;
		seedPairs.emplace_back(a, b);
	}

	for (int i = 0; i < 7; i++) {
		// make next seed pairs
		vector<ii> newSeedPairs;
		for (auto [a, b, c] : maps[i]) {
			for (auto it = seedPairs.begin(); it != seedPairs.end(); ++it) {
				ll x = it->first, y = it->second;
				ll L = max(b, x), R = min(b + c, x + y);
				if (L < R) {
					newSeedPairs.emplace_back(a + (L - b), R - L);
					it->second = L - x;
					if (R < x + y) seedPairs.emplace_back(R, x + y - R);
				}
			}
		}
		for (auto pr : newSeedPairs) seedPairs.pb(pr);
		// seedPairs = newSeedPairs;
		//

		int j = 0;
		while (j < sz(seedPairs)) {
			if (seedPairs[j].y == 0)
				seedPairs[j] = seedPairs.back(), seedPairs.pop_back();
			else ++j;
		}

	}

	sumB = LLONG_MAX;
	for (auto [a, b] : seedPairs) sumB = min(sumB, a);
	cout << "Part B: " << sumB << endl;
	return 0;
}
