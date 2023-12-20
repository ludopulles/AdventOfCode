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

vi parse_ints(const vector<string> &v) {
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
const int MAXN = 100;
int nnodes = 0, broadcaster;

string nodes[MAXN];
char type[MAXN];
vector<string> toS[MAXN];
vi to[MAXN];

map<string, int> lookup;
bool state[MAXN] = {};
map<int, bool> wason[MAXN];

int lowsent = 0, highsent = 0;

bool sendPulse() {
	queue<tuple<int,int,int>> q;
	q.emplace(broadcaster, broadcaster, false);

	bool saw_rx = false;

	while (!q.empty()) {
		auto [fr, idx, isHigh] = q.front(); q.pop();
		// cerr << nodes[fr] << " -" << (isHigh ? "high" : "low") << "-> " << nodes[idx] << endl;
		if (isHigh) highsent++;
		else lowsent++;

		if (idx == nnodes) {
			if (!isHigh && idx == lookup["rx"]) saw_rx = true;
			continue;
		}

		if (idx == lookup["broadcaster"]) {
			for (int t : to[idx]) q.emplace(idx, t, isHigh);
		} else if (type[idx] == '%') {
			if (!isHigh) {
				bool send = state[idx] = !state[idx];
				for (int t : to[idx]) q.emplace(idx, t, send);
			}
		} else {
			bool send = true;
			wason[idx][fr] = isHigh;
			for (auto [loc, val] : wason[idx]) send &= val;
			for (int t : to[idx]) q.emplace(idx, t, !send);
		}
	}
	return saw_rx;
}

vi lows, highs;
map<vector<bool>, ll> state_map;

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) {
		auto [pre, post] = split_at(line, " -> ");
		type[nnodes] = pre[0];
		for (string sto : split_str(post, ", ")) toS[nnodes].pb(sto);
		nodes[nnodes] = pre.substr(pre != "broadcaster");
		lookup[nodes[nnodes]] = nnodes;
		nnodes++;
	}
	broadcaster = lookup["broadcaster"];
	REP(i, nnodes) for (const string &s : toS[i]) {
		if (lookup.find(s) == lookup.end()) to[i].pb(nnodes);
		else to[i].pb(lookup[s]), wason[lookup[s]][i] = false;
	}

	ll fst_rx = LLONG_MAX;
	// ll cyc_start = -1;
	REP(_, 1000) {
		if (sendPulse())
			fst_rx = min(fst_rx, (ll) _ + 1);
/*
		REP(i, nnodes) {
			if (type[i] == '%') cerr << state[i];
			else if (type[i] == '&') for (auto [j, v] : wason[i]) cerr << v;
		}
		cerr << endl;

		vector<bool> cur;
		REP(i, nnodes) {
			if (type[i] == '%') cur.pb(state[i]);
			else if (type[i] == '&') for (auto [j, v] : wason[i]) cur.pb(v);
		}

		lows.pb(lowsent);
		highs.pb(highsent);
		if (state_map.find(cur) != state_map.end()) {
			cyc_start = state_map.find(cur)->y;
			break;
		}
		state_map[cur] = sz(lows) - 1; */
	}

	// cout << "Cycle length: " << sz(lows) << " but precycle is " << cyc_start << endl;
	// cout << "Low: " << lowsent << ", high: " << highsent << endl;

	sumA = lowsent * highsent;
	cout << "Part A: " << sumA << endl;

	assert(fst_rx == LLONG_MAX);
	fst_rx = 1000;
	while (!sendPulse()) fst_rx++;
	sumB = fst_rx;
	cout << "Part B: " << sumB << endl;
	return 0;
}
