#include "header.h"

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
