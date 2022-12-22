#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define rep(i,a,b) for (auto i = (a); i < (b); ++i)
#define REP(i,n) rep(i,0,n)
#define sz(v) ((int) (v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

typedef ll T;

struct Node {
	char op;
	string lop, rop;

	T val;
};


map<string, Node> nodes;

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

T operate(char op, T L, T R) {
	if (op == '+') return L + R;
	if (op == '-') return L - R;
	if (op == '*') return L * R;
	if (op == '/') { assert(L % R == 0); return L / R; }
	assert(false);
}

T dfs(string name) {
	// assert(nodes.find(name) != nodes.end());
	Node &node = nodes[name];

	if (node.op == ' ')
		return node.val;

	node.val = operate(node.op, dfs(node.lop), dfs(node.rop));
	return node.val;
}

T evalF(T inp) {
	nodes["humn"].val = inp;
	return dfs(nodes["root"].lop) - dfs(nodes["root"].rop);
}

bool has_humn(string name) {
	Node &node = nodes[name];
	return name == "humn" || (node.op != ' ' && (has_humn(node.lop) || has_humn(node.rop)));
}

T solve(string name, T x) {
	if (name == "humn") return x;
	Node &node = nodes[name];
	assert(node.op != ' ' && has_humn(name));

	if (has_humn(node.lop)) {
		T y, z = nodes[node.rop].val;
		printf("Solve: %lld = ? %c %lld\n", x, node.op, z);

		switch (node.op) {
		case '+': y = x - z; break;
		case '-': y = x + z; break;
		case '*': assert(x % z == 0); y = x / z; break;
		case '/': y = x * z; break;
		default: assert(false);
		}
		return solve(node.lop, y);
	} else {
		T y, z = nodes[node.lop].val;
		printf("Solve: %lld = %lld %c ?\n", x, z, node.op);

		switch (node.op) {
		case '+': y = x - z; break;
		case '-': y = z - x; break;
		case '*': assert(x % z == 0); y = x / z; break;
		case '/': assert(z % x == 0); y = z / x; break;
		default: assert(false);
		}
		return solve(node.rop, y);
	}
}

T binary_search() {
	T lo = -1e18, hi = 1e18;
	// printf("%lld -> %f\n", (ll) lo, evalF(lo));
	// printf("%lld -> %f\n", (ll) hi, evalF(hi));

	if (evalF(lo) > evalF(hi)) swap(lo, hi);

	REP(i, 100) {
		T mid = (lo + hi) / 2.0;
		T em = evalF(mid);
		// printf("We have %f (%f) -> %f\n", mid, abs(hi - lo), em);
		if (em < 0) lo = mid;
		else hi = mid;
	}

	// printf("%lld -> %f\n", (ll) lo, evalF(lo));
	// printf("%lld -> %f\n", (ll) hi, evalF(hi));
	return (lo + hi) / 2.0;
}

int main() {
	string line;
	while (getline(cin, line), cin) {
		string name = line.substr(0, 4);
		if ((line[6] < '0' || line[6] > '9') && line[6] != '-') {
			nodes[ name ] = Node{ line[11], line.substr(6, 4), line.substr(13, 4), (T) LLONG_MAX};
		} else {
			int pos = 6;
			ll val = parseInt(line, pos);

			// assert(nodes.find(name) == nodes.end());
			nodes[ name ] = Node{' ',"","", (T) val};
		}
	}

	T solA = dfs("root");

	Node rt = nodes["root"];
	string part = has_humn(rt.lop) ? rt.lop : rt.rop;
	T solve_value = nodes[has_humn(rt.lop) ? rt.rop : rt.lop].val;
	T solB = solve(part, solve_value);

	printf("\n");
	printf("Part A: %lld\n", (ll) solA);
	printf("Part B: %lld\n", (ll) solB);
	return 0;
}
