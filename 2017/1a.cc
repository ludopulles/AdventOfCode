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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;
	int N = s.size();
	int sum = 0;
	for (int i = 0; i < N; i++) {
		
		int j = (i + 1) % N;
		if (s[i] == s[j]) {
			sum += s[i] - '0';
		}
	}
	cout << sum << endl;
	return 0;
}
