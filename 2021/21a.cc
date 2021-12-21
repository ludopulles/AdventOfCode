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

int mod10(int n) { return (n %= 10) ? n : 10; }

int main() {
	ii startPos(0, 0);

	string line;
	getline(cin, line);
	startPos.x = line.back() - '0';
	getline(cin, line);
	startPos.y = line.back() - '0';

	ii score(0, 0);

	int ans = 0;
	for (int i=1; ; i += 6) {
		startPos.x = mod10(startPos.x + 3*i + 3);
		if ((score.x += startPos.x) >= 1000) {
			ans = (i+2) * score.y;
			break;
		}

		startPos.y = mod10(startPos.y + 3*i + 12);
		if ((score.y += startPos.y) >= 1000) {
			ans = (i+5) * score.x;
			break;
		}
	}

	cout << ans << endl;
	return 0;
}
