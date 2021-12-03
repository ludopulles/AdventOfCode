#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("input/2", "r", stdin);
	string s;
	int depth = 0, pos = 0, dx;
	while (cin >> s >> dx) {
		if (s[0] == 'f') pos += dx;
		if (s[0] == 'u') depth -= dx;
		if (s[0] == 'd') depth += dx;
	}
	cout << (depth * pos) << endl;
	return 0;
}
