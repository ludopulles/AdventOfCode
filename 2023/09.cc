#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) begin(v), end(v)
#define pb push_back
#define eb emplace_back
#define x first
#define y second

bool is_num(const string &s, int pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parse_int(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

ll parse_int(const string &s) { int pos = 0; return parse_int(s, pos); }

vi parse_ints(vector<string> &v) {
	vi res;
	transform(all(v), back_inserter(res), [](string s) { return (ll) parse_int(s); });
	return res;
}

vector<string> split_str(string s, string split) {
	size_t pos = 0, newpos = 0, n = split.size();
	vector<string> result;
	while ((newpos = s.find(split, pos)) != string::npos) {
		result.push_back(s.substr(pos, newpos - pos));
		pos = newpos + n;
	}
	if (pos < s.size()) result.push_back(s.substr(pos));
	return result;
}

pair<string, string> split_at(string s, string split) {
	size_t pos = s.find(split, 0);
	assert(pos != string::npos);

	return make_pair(s.substr(0, pos), s.substr(pos + split.size()));
}

/**************************************************************************************************
 * Code for today is below:
 *************************************************************************************************/
vvi seqs;

bool isconstant(const vi &seq, int i0) {
	for (int i = i0; i + 1 < sz(seq); i++) if (seq[i] != seq[i + 1]) return false;
	return true;
}

void differentiate(vi &seq, int i0) {
	for (int i = sz(seq) - 1; i > i0; i--) seq[i] -= seq[i - 1];
}

void integrate(vi &seq, int i0) {
	for (int i = i0 + 1; i < sz(seq); i++) seq[i] += seq[i - 1];
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) {
		vi nums;
		int pos = 0;
		while (pos < sz(line))
			nums.pb(parse_int(line, pos)), ++pos;
		seqs.pb(nums);
	}

	for (vi seq : seqs) {
		vi curseq = seq;
		int deltas = 0;
		for (; !isconstant(curseq, deltas); ++deltas) {
			differentiate(curseq, deltas); 
		}
		int before = curseq[deltas];
		curseq.pb(curseq[deltas]);
		while (deltas --> 0) {
			before = curseq[deltas] - before;
			// curseq[deltas + 1] += curseq[deltas];
			// curseq[deltas + 2] += curseq[deltas + 1];
			integrate(curseq, deltas);
		}

		sumA += curseq.back();
		sumB += before;
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
