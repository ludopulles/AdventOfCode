#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

int main() {
	int partA = 0, partB = 0;
	for (string line; getline(cin, line); ) {
		int a[4] = { 0, 0, 0, 0 }, idx = 0;
		for (char ch : line) {
			if (ch == '-' || ch == ',') idx++;
			else a[idx] = a[idx] * 10 + (ch - '0');
		}

		partA += (a[0] <= a[2] && a[3] <= a[1]) || (a[2] <= a[0] && a[1] <= a[3]);
		partB += a[1] >= a[2] && a[0] <= a[3];
	}

	printf("Part A: %d\n", partA);
	printf("Part B: %d\n", partB);
	return 0;
}
