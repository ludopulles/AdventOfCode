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
	int ret = 0;
	string line;
	while (getline(cin, line), cin) {
		stringstream ss(line);
		string word;
		set<string> words;
		bool pass = true;
		while (ss >> word) {
			if (words.find(word) != words.end()) pass = false;
			words.insert(word);
		}
		ret += pass;
	}
	cout << ret << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();
	return 0;
}
