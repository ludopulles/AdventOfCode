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

vector<bool> bits;

int readBits(int &pos, int n) {
	int res = 0;
	while (n--) res = 2*res + bits[pos++];
	return res;
}

ll parsePackets(int &pos) {
	int version = readBits(pos, 3);
	int type = readBits(pos, 3);
	if (type == 4) { // literal
		ll value = 0;
		while (bits[pos++])
			value = value * 16 + readBits(pos, 4);
		return value * 16 + readBits(pos, 4);
	}

	int topos = INT_MAX, subs = INT_MAX;
	if (bits[pos++])
		subs = readBits(pos, 11);
	else
		topos = readBits(pos, 15) + pos;

	ll answer = 0LL;
	for (int i=0; i < subs && pos < topos; i++) {
		ll v = parsePackets(pos);
		if (i == 0) {
			answer = v;
			continue;
		}
		switch (type) {
		case 0: answer += v; break;
		case 1: answer *= v; break;
		case 2: answer = min(answer, v); break;
		case 3: answer = max(answer, v); break;
		case 5: answer = answer > v; break;
		case 6: answer = answer < v; break;
		case 7: answer = answer == v; break;
		}
	}
	return answer;
}

int main() {
	string line;
	getline(cin, line);
	for (char ch : line) {
		int v = ('A' <= ch && ch <= 'Z') ? (ch-'A'+10) : ch - '0';
		for (int i=3; i >= 0; i--) {
			bits.push_back((v >> i) & 1);
		}
	}

	int _ = 0;
	cout << parsePackets(_) << endl;
	return 0;
}
