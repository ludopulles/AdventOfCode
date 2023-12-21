#include "header.h"

const int MAXN = 100;
int nnodes = 0, broadcaster;

string nodes[MAXN];
char type[MAXN];
vector<string> toS[MAXN];
vi to[MAXN];

map<string, int> lookup;
bool state[MAXN] = {}, partB;
map<int, bool> wason[MAXN];

int lowsent = 0, highsent = 0, idxGH;

void sendPulse() {
	queue<tuple<int,int,int>> q;
	q.emplace(broadcaster, broadcaster, false);

	while (!q.empty()) {
		auto [fr, idx, isHigh] = q.front(); q.pop();
		if (isHigh) highsent++;
		else lowsent++;

		if (idx == nnodes) continue;

		if (idx == broadcaster) {
			for (int t : to[idx]) q.emplace(idx, t, isHigh);
		} else if (type[idx] == '%') {
			if (!isHigh) {
				bool send = state[idx] = !state[idx];
				for (int t : to[idx]) q.emplace(idx, t, send);
			}
		} else { assert(type[idx] == '&');
			bool send = true;
			wason[idx][fr] = isHigh;
			for (auto [loc, val] : wason[idx]) send &= val;
			for (int t : to[idx]) q.emplace(idx, t, !send);
		}
	}
}

bool sendPartPulse(int bnode, int enode) {
	queue<tuple<int,int,int>> q;
	q.emplace(broadcaster, bnode, false);
	bool sent = false;
	while (!q.empty()) {
		auto [fr, idx, isHigh] = q.front(); q.pop();
		if (idx == enode) { sent |= !isHigh; continue; }
		if (type[idx] == '%') {
			if (!isHigh) {
				bool send = state[idx] = !state[idx];
				for (int t : to[idx]) q.emplace(idx, t, send);
			}
		} else { assert(type[idx] == '&');
			bool send = true;
			wason[idx][fr] = isHigh;
			for (auto [loc, val] : wason[idx]) send &= val;
			for (int t : to[idx]) q.emplace(idx, t, !send);
		}
	}
	return sent;
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

	partB = lookup.find("gh") != lookup.end();
	idxGH = partB ? lookup["gh"] : -1;
	nodes[nnodes] = "???";
	broadcaster = lookup["broadcaster"];
	REP(i, nnodes) for (const string &s : toS[i]) {
		if (lookup.find(s) == lookup.end()) to[i].pb(nnodes);
		else to[i].pb(lookup[s]), wason[lookup[s]][i] = false;
	}

	// Part A:
	REP(_, 1000) sendPulse();
	sumA = lowsent * highsent;
	cout << "Part A: " << sumA << endl;

	// Part B:
	if (!partB) return 0;
	REP(i, nnodes) state[i] = false;
	REP(i, nnodes) for (const string &s : toS[i])
		if (lookup.find(s) != lookup.end()) wason[lookup[s]][i] = false;

	sumB = 1LL;
	for (ll bnode : to[broadcaster]) {
		ll enode = -1;
		vi canReach = {bnode};
		for (int i = 0; i < sz(canReach); i++) {
			if (sz(to[canReach[i]]) == 1 && to[canReach[i]][0] == idxGH) {
				enode = canReach[i];
				continue;
			}

			for (auto j : to[canReach[i]])
				if (find(all(canReach), j) == canReach.end()) canReach.pb(j);
		}

		ll its1 = 0, its2 = 0;
		do { its1++; } while (!sendPartPulse(bnode, enode));
		do { its2++; } while (!sendPartPulse(bnode, enode));
		assert(its1 == its2 && gcd(sumB, its1) == 1);
		sumB *= its1;
	}

	cout << "Part B: " << sumB << endl;
	return 0;
}
