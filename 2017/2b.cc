#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

void run()
{
	int ret = 0;
	string S;
	while (getline(cin, S), cin) {
		stringstream ss(S);
		vi xs;
		int x;
		while (ss >> x) xs.pb(x);

		int ans = 1;
		for (int i : xs) {
			for (int j : xs) {
				if (i != j && i % j == 0) ans = max(ans, i / j);
			}
		}
		ret += ans;
	}
	cout << ret << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
