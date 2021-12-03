#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, a = 0;
	while (cin >> n) {
		for (int m = n; (m = m/3-2) > 0; )
			a += m;
	}
	cout << a << endl;
	return 0;
}
