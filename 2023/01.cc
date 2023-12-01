#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
#define pb push_back
#define eb emplace_back
#define x first
#define y second

bool is_num(const string &s, int &pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

const string spelled[9] = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main() {
	string line;

	int sumA = 0;
	int sumB = 0;
	while (getline(cin, line), cin) {
		int n = (int) line.size();

		int fd = -1, ld = -1;

		for (int i = 0; i < n; i++) {
			if ('0' <= line[i] && line[i] <= '9') {
				fd = line[i] - '0';
				break;
			}
		}

		for (int i = n; i --> 0; ) {
			if ('0' <= line[i] && line[i] <= '9') {
				ld = line[i] - '0';
				break;
			}
		}

		sumA += fd*10 + ld;

		fd = ld = -1;
		for (int i = 0; i < n; i++) {
			if ('0' <= line[i] && line[i] <= '9') {
				fd = line[i] - '0';
				break;
			}
			for (int j = 0; j < 9; j++) {
				if (i + (int) spelled[j].size() < n && line.substr(i, spelled[j].size()) == spelled[j]) {
					fd = j + 1; break;
				}
			}
			if (fd != -1) break;
		}

		for (int i = n; i > 0; i--) {
			if ('0' <= line[i-1] && line[i-1] <= '9') {
				ld = line[i-1] - '0';
				break;
			}
			// cout << i << endl;
			for (int j = 0; j < 9; j++) {
				if (i - (int) spelled[j].size() >= 0 && line.substr(i - spelled[j].size(), spelled[j].size()) == spelled[j]) {
					ld = j + 1; break;
				}
			}
			if (ld != -1) break;
		}

		sumB += fd*10 + ld;
	}

	cout << sumA << endl;
	cout << sumB << endl;

	return 0;
}
