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

const int maxn = 1000;

int vals[2 * maxn][2 * maxn] = {};

int dx[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
int dy[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };

void run()
{
	int target;
	cin >> target;

	int x = maxn, y = maxn;
	int num = 1, len = 1;
	bool rightup = true;

	vals[x][y] = 1;

	bool stop = false;
	while (!stop) {
		for (int i = 0; i < len; i++) {
			x += rightup ? 1 : -1;
			num++;

			vals[x][y] = 0;
			for (int d = 0; d < 8; d++) {
				vals[x][y] += vals[x + dx[d]][y + dy[d]];
			}
			cerr << num << ": " << vals[x][y] << endl;
			if (vals[x][y] >= target) { stop = true; break; }
		}
		if (stop) break;
		for (int i = 0; i < len; i++) {
			y += rightup ? 1 : -1;
			num++;

			vals[x][y] = 0;
			for (int d = 0; d < 8; d++)
				vals[x][y] += vals[x + dx[d]][y + dy[d]];
			cerr << num << ": " << vals[x][y] << endl;
			if (vals[x][y] >= target) { stop = true; break; }
		}
		rightup = !rightup;
		len++;
	}
	// cout << x << " " << y << endl;
	// cout << (abs(x) + abs(y)) << endl;
	cout << vals[x][y] << " " << x << " " << y << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
