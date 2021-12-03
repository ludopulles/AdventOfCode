#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("input/3", "r", stdin);
	vector<string> in;
	string line;
	while (cin >> line) {
		in.emplace_back(line);
	}

	int res = 0, N = in[0].size();
	for (int i=0; i<N; i++) {
		int occ = 0;
		for (auto j : in) occ += j[i] == '1';
		if (occ > in.size()/2) res |= 1 << (N-1-i);
	}
	cout << (res * ((1<<N)-1-res)) << endl;
	return 0;
}
