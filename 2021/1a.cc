#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("input/1", "r", stdin);
	int last = INT_MAX, n, res = 0;
	while (cin >> n) {
		if (n > last)
			res++;
		last = n;
	}
	cout << res << endl;
	return 0;
}
