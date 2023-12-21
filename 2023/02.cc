#include "header.h"

int main() {
	string line, _;
	int sumA = 0, sumB = 0;

	while (getline(cin, line), cin) {
		int id;
		auto V = split_str(line, ": ");
		stringstream ss(V[0]); ss >> _ >> id;
		line = V[1];

		map<string, int> maxtaken;
		for (string draws : split_str(line, "; ")) {
			map<string, int> taken;
			for (string nr_col : split_str(draws, ", ")) {
				ss = stringstream(nr_col);
				int nr; string col;
				ss >> nr >> col;
				taken[col] += nr;
			}

			for (auto [col, nr] : taken)
				maxtaken[col] = max(maxtaken[col], nr);
		}

		if (maxtaken["red"] <= 12 && maxtaken["green"] <= 13 && maxtaken["blue"] <= 14)
			sumA += id;

		sumB += maxtaken["red"] * maxtaken["green"] * maxtaken["blue"];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;

	return 0;
}
