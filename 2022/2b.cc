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
	string line;

	int score = 0;

	while (getline(cin, line), cin) {
		int a = line[0] - 'A';
		int c = line[2] - 'X';
		// c = b - a + 4
		// b = c + a - 4
		int b = (c + a + 2) % 3;

		score += 1 + b + 3 * c;
	}

	cout << score << endl;
	return 0;
}
