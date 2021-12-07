#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())

vi parse(string line) {
	for (char &ch : line)
		if (ch == ',') ch = ' ';
	stringstream ss(line);
	vi v;
	ll x;
	while (ss >> x)
		v.push_back(x);
	return v;
}


int main() {
	string line;
	getline(cin, line);
	vi xs = parse(line);


	return 0;
}
