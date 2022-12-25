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
	getline(cin, line);

	int a, b;
	for (a = 4; sz(set<int>(begin(line) + a - 4, begin(line) + a)) < 4; a++);
	for (b = 14; sz(set<int>(begin(line) + b - 14, begin(line) + b)) < 14; b++);

	printf("Part A: %d\n", a);
	printf("Part B: %d\n", b);
	return 0;
}
