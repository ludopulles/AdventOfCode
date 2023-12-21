#include "header.h"

string route;
unordered_map<string, string> L, R;
vector<unordered_map<string, pair<string, ll>>> to_next_Z;

pair<string, ll> num_steps(const int i, const string &s) {
	if (to_next_Z[i].find(s) == to_next_Z[i].end()) {
		int idxRoute = i, steps = 0;
		string cur = s;
		// set<pair<string, ll>> visited;
		do {
			// if (visited.find(make_pair(cur, idxRoute)) != visited.end()) break;
			// visited.emplace(cur, idxRoute);
			cur = (route[idxRoute] == 'L' ? L : R)[cur];
			steps++;
			if (++idxRoute == sz(route)) idxRoute = 0;
		} while (cur[2] != 'Z');

		assert(cur[2] == 'Z');
		to_next_Z[i][s] = make_pair(cur, steps);
	}
	return to_next_Z[i][s];
}


int main() {
	ll sumA = 0, sumB = 0;
	vector<string> nodes, curnodes;
	string line;

	getline(cin, route);
	getline(cin, line);
	while (getline(cin, line), cin) {
		string fr = line.substr(0, 3), toL = line.substr(7, 3), toR = line.substr(12, 3);
		nodes.pb(fr);
		if (fr[2] == 'A') curnodes.pb(fr);
		L[fr] = toL;
		R[fr] = toR;
	}

	if (find(all(nodes), "AAA") != nodes.end()) {
		string cur = "AAA";
		int idxRoute = 0;
		while (cur != "ZZZ") {
			if (route[idxRoute] == 'L') cur = L[cur];
			else cur = R[cur];
			sumA++;

			if (++idxRoute == sz(route)) idxRoute = 0;
		}

		cout << "Part A: " << sumA << endl;
	}

	to_next_Z.resize(sz(route));

	sumB = 1;
	for (string cur : curnodes) {
		int st = 0;
		while (to_next_Z[st % sz(route)].find(cur) == to_next_Z[st % sz(route)].end()) {
			auto [nxt, add] = num_steps(st % sz(route), cur);
			cur = nxt;
			st += add;
		}

		auto [nxt, add] = to_next_Z[st % sz(route)][cur];

		assert(cur == nxt);
		assert(st % add == 0);
		sumB = sumB / gcd(sumB, add) * add;
	}

	cout << "Part B: " << sumB << endl;
	return 0;
}
