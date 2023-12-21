#include "header.h"

map<tuple<int,int,int>, ll> mem;

ll rec(const string &s, const vi &lens, int sidx, int lidx, int curlen) {
	if (sidx == sz(s)) {
		if (curlen == lens[lidx] && lidx < sz(lens)) lidx++;
		return sidx == sz(s) && lidx == sz(lens);
	}

	auto key = make_tuple(sidx, lidx, curlen);
	if (mem.find(key) != mem.end())
		return mem[key];

	ll res = 0;
	if (s[sidx] != '#') {
		// stop curlen
		if (curlen == 0)
			res += rec(s, lens, sidx + 1, lidx, 0);
		else if (lidx < sz(lens) && curlen == lens[lidx])
			res += rec(s, lens, sidx + 1, lidx + 1, 0);
	}
	if (s[sidx] != '.' && lidx < sz(lens) && curlen < lens[lidx]) {
		// incremenet curlen
		res += rec(s, lens, sidx + 1, lidx, curlen + 1);
	}
	return mem[key] = res;
}

int main() {
	ll sumA = 0, sumB = 0;
	string line;

	while (getline(cin, line), cin) {
		auto [str, _] = split_at(line, " ");
		vi lens = parse_ints(split_str(_, ","));

		mem.clear();
		sumA += rec(str, lens, 0, 0, 0);

		string str2 = str;
		vi lens2;
		REP(i, 4) str2 += '?', str2 += str;
		REP(i, 5) lens2.insert(lens2.end(), all(lens));

		mem.clear();
		sumB += rec(str2, lens2, 0, 0, 0);
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
