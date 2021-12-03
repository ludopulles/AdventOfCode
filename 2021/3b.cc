#include<bits/stdc++.h>
using namespace std;

int conv(const string &s) {
	int res = 0;
	for (char ch : s)
		res = 2*res + (ch - '0');
	return res;
}

int O2(vector<string> &list, int idx, bool most) {
	if (list.size() == 1) return conv(list[0]);

	int nr1 = 0;
	for (string &s : list)
		nr1 += s[idx] == '1';
	char match = ((nr1 >= list.size() - nr1) == most) ? '1' : '0';
	vector<string> nlist;
	for (string &s : list)
		if (s[idx] == match)
			nlist.push_back(s);
	return O2(nlist, idx+1, most);
}

int main() {
	freopen("input/3", "r", stdin);
	vector<string> in;
	string line;
	while (cin >> line) {
		in.emplace_back(line);
	}

	cout << (O2(in,0,true) * O2(in,0,false)) << endl;
	return 0;
}
