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

vector<ll> parse_ints(vector<string> &v) {
	vector<ll> res;
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
vector< pair<string, ll> > hands;

int get_hand(const string &s) {
	map<char, int> freq;
	for (char ch : s) freq[ch]++;

	vi v;
	for (auto [ch, f] : freq) v.pb(f);
	sort(all(v));
	if (v == vi{ 5 }) return 7; // five of a kind
	if (v == vi{ 1, 4 }) return 6; // four of a kind
	if (v == vi{ 2, 3 }) return 5; // full house
	if (v.back() == 3) return 4; // three of a kind
	if (sz(v) >= 2 && v.back() == 2 && v[sz(v) - 2] == 2) return 3; // two pair
	if (v.back() == 2) return 2; // two pair
	if (v.back() == 1) return 1; // one pair
	return 0;
}

bool sort_by_value(const pair<string, ll> &a, const pair<string, ll> &b) {
	int va = get_hand(a.x), vb = get_hand(b.x);
	if (va != vb) return va < vb;
	return a.x < b.x;
}


int get_hand_part2(const string &s) {
	map<char, int> freq;
	int nrJ = 0;
	for (char ch : s) {
		if (ch == '!') nrJ++;
		else freq[ch]++;
	}

	vi v;
	for (auto [ch, f] : freq) v.pb(f);
	sort(all(v));

	if (v.empty()) return 7; // five of a kind with jokers.

	v.back() += nrJ;

	if (v.back() == 5) return 7; // five of a kind
	if (v.back() == 4) return 6; // four of a kind
	if (v.back() == 3 && sz(v) >= 2 && v[sz(v) - 2] == 2) return 5; // full house
	if (v.back() == 3) return 4; // three of a kind
	if (sz(v) >= 2 && v.back() == 2 && v[sz(v) - 2] == 2) return 3; // two pair
	if (v.back() == 2) return 2; // two pair
	if (v.back() == 1) return 1; // one pair
	return 0;
}

// 'J' gets replaced by 'b'!!!
bool sort_by_value_part2(const pair<string, ll> &a, const pair<string, ll> &b) {
	int va = get_hand_part2(a.x), vb = get_hand_part2(b.x);
	if (va != vb) return va < vb;
	return a.x < b.x;
}


int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) {
		string hand = line.substr(0, 5);
		ll val = parse_int(line.substr(6));

		char chnr = 'a';
		for (char ch : "TJQKA") {
			for (char &t : hand) if (t == ch) t = chnr;
			chnr++;
		}

		hands.eb(hand, val);
	}

	sort(all(hands), sort_by_value);
	ll idx = 1;
	for (auto [h, v] : hands) sumA += (idx++) * v;
	cout << "Part A: " << sumA << endl;

	for (auto &[hand, val]: hands) {
		for (char &t : hand) if (t == 'b') t = '!';
	}

	sort(all(hands), sort_by_value_part2);
	idx = 1;
	for (auto [h, v] : hands) {
		cout << h << " ";
		sumB += (idx++) * v;
	}
	cout << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
