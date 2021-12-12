#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())

int turn_on[10] = {
	0b1110111, // 0
	0b0010010, // 1
	0b1011101, // 2
	0b1011011, // 3
	0b0111010, // 4
	0b1101011, // 5
	0b1101111, // 6
	0b1010010, // 7
	0b1111111, // 8
	0b1111011  // 9
};

vi inv(vi pi) {
	int n = pi.size();
	vi res(n, 0);
	REP(i, n)
		res[pi[i]] = i;
	return res;
}

int apply(int mask, vi pi) {
	int res = 0;
	for (int i=0; i<7; i++)
		if ((mask>>i)&1)
			res |= 1<<pi[i];
	return res;
}

set<int> fillWith(int a, int b, int c) {
	set<int> res;
	res.insert(a); res.insert(b); res.insert(c);
	return res;
}

// acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf

ll run() {
	int hints[10], nums[4];

	string s;
	if (!(cin >> s)) return -1;

	REP(i, 10) {
		hints[i] = 0;
		for (char ch : s)
			hints[i] |= 1 << (ch - 'a');
		cin >> s;
	}
	assert(s == "|");
	REP(i, 4) {
		cin >> s;
		nums[i] = 0;
		for (char ch : s)
			nums[i] |= 1 << (ch - 'a');
	}

	sort(hints, hints + 10, [] (int a, int b) -> bool {
		int pa = __builtin_popcount(a);
		int pb = __builtin_popcount(b);
		return pa < pb;
	});

	// hints[0] <=> 1
	// hints[1] <=> 7
	// hints[2] <=> 4
	// hints[9] <=> 8
	// hints[3,4,5] <=> 2,3,5
	// hints[6,7,8] <=> 0,6,9
	vi pi(7, 0);
	REP(i, 7) pi[i] = i;

	ll res = 0;
	int nr_works = 0;
	do {
		if (apply(turn_on[1], pi) != hints[0]) continue;
		if (apply(turn_on[7], pi) != hints[1]) continue;
		if (apply(turn_on[4], pi) != hints[2]) continue;
		if (apply(turn_on[8], pi) != hints[9]) continue;

		int h2 = apply(turn_on[2], pi);
		int h3 = apply(turn_on[3], pi);
		int h5 = apply(turn_on[5], pi);
		if (fillWith(h2, h3, h5) != fillWith(hints[3], hints[4], hints[5])) continue;
		int h0 = apply(turn_on[0], pi);
		int h6 = apply(turn_on[6], pi);
		int h9 = apply(turn_on[9], pi);
		if (fillWith(h0, h6, h9) != fillWith(hints[6], hints[7], hints[8])) continue;

		nr_works++;

		for (int x : pi) cout << x << " ";
		cout << endl;

		// Works!
		REP(i, 4) {
			int nmatch = 0, val = -1;
			REP(dig, 10)
				if (apply(turn_on[dig], pi) == nums[i]) {
					nmatch++; val = dig;
				}
			assert(nmatch == 1);
			if (val == 1 || val == 4 || val == 7 || val == 8)
				res++;
		}
	} while (next_permutation(pi.begin(), pi.end()));

	assert( nr_works == 1 );

	return res;
}

int main() {
	ll res = 0;

	while (true) {
		ll inc = run();
		if (inc < 0) break;
		res += inc;
	}
	cout << res << endl;

	return 0;
}
