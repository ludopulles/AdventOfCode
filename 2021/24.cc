#include<bits/stdc++.h>
#include<compare>
#include<initializer_list>

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

enum OpCode { INP, ADD, MUL, DIV, MOD, EQL };

struct Registers {
	ll v[4];

	Registers() { memset(v, 0, sizeof v); }
	Registers(ll w, ll x, ll y, ll z) {
		v[0] = w;
		v[1] = x;
		v[2] = y;
		v[3] = z;
	}

	strong_ordering operator<=>(const Registers &rhs) const =default;
	inline ll operator[](const int &idx) const { return this->v[idx]; }
};

ostream& tostr(ostream &out, ll N) {
	ll m = 1;
	while (26LL * m <= N) m *= 26LL;
	while (m >= 1) { out << (char)('a' + (N/m)); N %= m; m /= 26; }
	return out;
}

ostream& operator<<(ostream &out, const Registers &r) {
	out << '(' << r[0] << ',' << r[1] << ',' << r[2] << ',';
	tostr(out, r[3]);
	// out << r[3];
	return out << ')';
}

struct Operation {
	OpCode op;
	string var1, var2;

	Operation(const string &line) {
		stringstream ss(line);
		string opname;
		ss >> opname;

		if (opname == "inp") op = INP;
		else if (opname == "add") op = ADD;
		else if (opname == "mul") op = MUL;
		else if (opname == "div") op = DIV;
		else if (opname == "mod") op = MOD;
		else if (opname == "eql") op = EQL;
		else {
			cerr << "Invalid operator name " << opname << endl;
			assert(false);
		}

		if (op == INP)
			ss >> var1;
		else
			ss >> var1 >> var2;
	}
};

Registers execute(const Operation &op, const Registers &r, int inp) {
	if (op.op == INP) {
		return Registers(inp, r[1], r[2], r[3]);
	}

	ll a = op.var1[0] - 'w';
	ll b = 'w' <= op.var2[0] && op.var2[0] <= 'z' ? r[op.var2[0] - 'w'] : atoi(op.var2.c_str());
	ll res[4] = { r[0], r[1], r[2], r[3] };

	if (op.op == ADD) res[a] += b;
	else if (op.op == MUL) res[a] *= b;
	else if (op.op == DIV) res[a] /= b;
	else if (op.op == MOD) res[a] %= b;
	else if (op.op == EQL) res[a] = (res[a] == b);

	return Registers(res[0], res[1], res[2], res[3]);
}

tuple<int,int,int> values[14] = {
	{ 1, 12, 7 },
	{ 1, 11, 15 },
	{ 1, 12, 2 },
	{ 26, -3, 15 },
	{ 1, 10, 14 },
	{ 26, -9, 2 },
	{ 1, 10, 15 },
	{ 26, -7, 1 },
	{ 26, -11, 15 },
	{ 26, -4, 15 },
	{ 1, 14, 12 },
	{ 1, 11, 2 },
	{ 26, -8, 13 },
	{ 26, -10, 13 }
};

ll doFast(int *inp) {
	ll z = 0;
	for (int i=0; i < 14; i++) {
		if ((z%26) + get<1>(values[i]) == inp[i])
			z /= get<0>(values[i]);
		else {
			z = (z / get<0>(values[i])) * 26LL + (inp[i] + get<2>(values[i]));
		}
	}
	return z;
}

ll createNum(const initializer_list<int> &v) {
	ll res = 0LL;
	for (auto it = v.begin(); it != v.end(); ++it)
		res = res * 10 + *it;
	return res;
}

vector<ll> solutions() {
	// creations: 0, 1, 2, 4, 6, 10, 11
	// comparisons: 3, 5, 7, 8, 9, 12, 13
	// d_3 = d_2 - 1
	// d_5 = d_4 + 5
	// d_7 = d_6 + 8
	// d_8 = d_1 + 4
	// d_9 = d_0 + 3
	// d_12 = d_11 - 6
	// d_13 = d_10 + 2

	vector<ll> res;
	rep(d2, 2, 10) rep(d4, 1, 5) rep(d6, 1, 2) rep(d1, 1, 6) rep(d0, 1, 7) rep(d11, 7, 10) rep(d10, 1, 8) {
		res.pb(createNum({d0, d1, d2, d2-1, d4, d4+5, d6, d6+8, d1+4, d0+3, d10, d11, d11-6, d10+2 }));
	}
	return res;
}

int main() {

	vector<Operation> ops;
	string line;
	while (getline(cin, line)) {
		ops.emplace_back(line);
	}

	int r[15] = {}, loc;

	/*
	for (r[0] = 1; r[0] < 10; r[0]++)
	for (r[1] = 1; r[1] < 10; r[1]++)
	for (r[2] = 1; r[2] < 10; r[2]++)
	for (r[3] = 1; r[3] < 10; r[3]++)
	for (r[4] = 1; r[4] < 10; r[4]++)
	for (r[5] = 1; r[5] < 10; r[5]++)
	{ */

	/* for (int rep = 100000; rep--; ) {
		loc = 0;
		REP(i, 14) r[i] = (rand() % 9) + 1;

		if (doFast(r) < 26*26) {
			Registers reg;
			for (const Operation &op : ops) {
				reg = execute(op, reg, r[loc]);
				if (op.op == INP) loc++;
			}
			cout << "Output[";
			REP(i, 14) cout << r[i];
			cout << "]: " << reg << " vs ";
			tostr(cout, doFast(r)) << endl;
		}
	} */

	vector<ll> sols = solutions();
	ll maxX = *max_element(all(sols));
	ll minX = *min_element(all(sols));
	int nsols = sols.size();
	ll sumSol = 0;
	for (ll x : sols) {
		for (ll xx = x, i = 13; i >= 0; i--, xx /= 10) r[i] = xx % 10;
		assert( doFast(r) == 0 );
		cout << x << endl;
		sumSol += x;
	}

	cout << "max: " << maxX << endl;
	cout << "min: " << minX << endl;
	cout << "#sol:" << nsols << endl;
	cout << "sum: " << sumSol << endl;

	return 0;
}
