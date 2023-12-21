#include "header.h"

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	vector<int> ncards;
	while (getline(cin, line), cin) {
		auto [game, scard] = split_at(line, ": ");
		auto [winning, having] = split_at(scard, " | ");

		vector<string> _wins = split_str(winning, " ");
		set<string> wins = set<string>(all(_wins));
		wins.erase("");

		int nfound = 0;
		for (string have : split_str(having, " ")) {
			if (have == "") continue;
			nfound += wins.find(have) != wins.end();
		}
		ncards.pb(nfound);

		if (nfound) sumA += 1 << (nfound - 1);
	}

	vector<int> nwins(sz(ncards), 0);
	for (int i = sz(ncards) - 1; i >= 0; i--) {
		nwins[i] = 1;
		if (ncards[i]) {
			for (int j = 1; j <= ncards[i]; j++)
				nwins[i] += nwins[i + j];
		}
		sumB += nwins[i];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
