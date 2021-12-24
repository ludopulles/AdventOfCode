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
	vector<string> A;
	int a = 0, b = 0;
	string s;
	while(cin >> s) A.pb(s);

	int len = (int) A[0].size();
	int n = (int) A.size();
	REP(i, n) {
		REP(j, i) {
			int ndiff = 0;
			REP(k, len) {
				if (A[i][k] != A[j][k] && ++ndiff > 1) break;
			}
			if (ndiff == 1) {
				cout << A[i] << endl << A[j] << endl;
			}
		}
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
