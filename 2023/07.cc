#include "header.h"

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
