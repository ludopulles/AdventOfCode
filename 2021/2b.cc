#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("input/2", "r", stdin);
	string s;
	int aim = 0, depth = 0, pos = 0, dx;
	while (cin >> s >> dx) {
		if (s[0] == 'f') pos += dx, depth += aim * dx;
		if (s[0] == 'u') aim -= dx;
		if (s[0] == 'd') aim += dx;
	}
	cout << (depth * pos) << endl;
	return 0;
}
