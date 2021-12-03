#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("input/1", "r", stdin);
	vector<int> v;
	int n, res = 0;
	while (cin >> n)
		v.push_back(n);

	for (int i=0; i + 3 < v.size(); i++)
		res += v[i+3] > v[i];
	cout << res << endl;
	return 0;
}
