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
	vi xs; int x;
	while (cin >> x) xs.pb(x);
	
	int N = xs.size();
	int cur = 0;
	int steps = 0;
	while (0 <= cur && cur < N) {
		int inc = xs[cur];
		xs[cur] += inc >= 3 ? -1 : 1;
		cur += inc;
		steps++;
	}
	cout << steps << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
