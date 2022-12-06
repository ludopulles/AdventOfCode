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

	while (getline(cin, line), cin) {
		for (int i = 14; i <= line.size(); i++) {
			set<int> S;
			for (int j = i - 14; j < i; j++) S.insert(line[j]);
			if (S.size() == 14) {
				cout << i << endl;
				break;
			}
		}
	}

	return 0;
}
