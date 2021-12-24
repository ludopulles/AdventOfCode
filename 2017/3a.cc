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
	int N;
	cin >> N;

	int x = 0, y = 0;
	int num = 1, len = 1;
	bool rightup = true;
	while (num < N) {
		for (int i = 0; num < N && i < len; i++) {
			x += rightup ? 1 : -1;
			num++;
		}
		for (int i = 0; num < N && i < len; i++) {
			y += rightup ? 1 : -1;
			num++;
		}
		rightup = !rightup;
		len++;
	}
	cout << x << " " << y << endl;
	cout << (abs(x) + abs(y)) << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
