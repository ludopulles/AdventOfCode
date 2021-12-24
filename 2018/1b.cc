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
	vi v;
	{ int x; while(cin>>x) v.pb(x); }

	set<int> S;
	int r = 0, i = 0, n = (int) v.size();
	while (true) {
		if (S.find(r) != S.end()) {
			cout << r << endl;
			return;
		}
		S.insert(r);
		int x = v[i++];
		if (i == n) i = 0;
		r += x;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
