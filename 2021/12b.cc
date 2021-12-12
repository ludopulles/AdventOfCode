#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()

bool is_small(string name) {
	for (char ch : name)
		if ('A' <= ch && ch <= 'Z') return false;
	return true;
}

ll dfs(const string &cur, set<string> &seen, map<string,set<string>> &G, bool vis2) {
	if (cur == "end") return 1;

	ll res = 0;
	for (const string &nxt : G[cur]) {
		if (!is_small(nxt)) {
			res += dfs(nxt, seen, G, vis2);
		} else if (seen.find(nxt) == seen.end()) {
			seen.insert(nxt);
			res += dfs(nxt, seen, G, vis2);
			seen.erase(nxt);
		} else if (nxt != "start" && vis2) {
			res += dfs(nxt, seen, G, false);
		}
	}
	return res;
}

int main() {
	string line;

	map<string, set<string>> G;
	while (getline(cin, line)) {
		replace(all(line), '-', ' ');
		stringstream ss(line);
		string a, b;
		ss >> a >> b;
		G[a].insert(b);
		G[b].insert(a);
	}

	set<string> seen;
	seen.insert("start");
	cout << dfs("start", seen, G, true) << endl;

	return 0;
}
