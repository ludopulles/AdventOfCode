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
	int a = 0, b = 0;
	string s;
	while(cin >> s) {
		vi cnt(256, 0);
		for (char ch : s) cnt[ch]++;
		REP(i, 256) if (cnt[i] == 2) { a++; break; }
		REP(i, 256) if (cnt[i] == 3) { b++; break; }
	}
	cout << (a * b) << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
