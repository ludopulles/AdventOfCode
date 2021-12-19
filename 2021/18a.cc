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

const int MAXN = 1000 * 1000;

int V[MAXN], P[MAXN], L[MAXN], R[MAXN], nnodes = 0;

void setNode(int i, int v, int l, int r) {
	V[i] = v;
	L[i] = l;
	R[i] = r;
	if (l >= 0) P[L[i]] = i;
	if (r >= 0) P[R[i]] = i;
}

int makeNode(int v, int l, int r) {
	setNode(nnodes, v, l, r);
	return nnodes++;
}

int parse(string &line, int &pos) {
	if ('0' <= line[pos] && line[pos] <= '9') {
		int num = 0;
		while ('0' <= line[pos] && line[pos] <= '9') {
			num = 10*num + (line[pos++] - '0');
		}
		return makeNode(num, -1, -1);
	} else {
		assert(line[pos++] == '[');
		int l = parse(line, pos);
		assert(line[pos++] == ',');
		int r = parse(line, pos);
		assert(line[pos++] == ']');
		return makeNode(-1, l, r);
	}
}

int findLeft(int v) {
	if (P[v] < 0) return -1;
	if (L[P[v]] == v) return findLeft(P[v]);
	assert(R[P[v]] == v);
	int w = L[P[v]];
	while (V[w] < 0) w = R[w];
	return w;
}

int findRight(int v) {
	if (P[v] < 0) return -1;
	if (R[P[v]] == v) return findRight(P[v]);
	assert(L[P[v]] == v);
	int w = R[P[v]];
	while (V[w] < 0) w = L[w];
	return w;
}

bool s_explosion(int v, int d) {
	if (V[v] >= 0) return false;
	if (d < 4) return s_explosion(L[v], d+1) || s_explosion(R[v], d+1);

	assert(V[L[v]] >= 0 && V[R[v]] >= 0); // terminal nodes
	int vL = V[L[v]], vR = V[R[v]];

	V[v] = 0; L[v] = R[v] = -1;
	// do not cleanly remove the left and right child.

	int wl = findLeft(v);
	if (wl >= 0) V[wl] += vL;
	int wr = findRight(v);
	if (wr >= 0) V[wr] += vR;
	return true;
}

bool s_split(int v) {
	if (V[v] < 0) return s_split(L[v]) || s_split(R[v]);
	if (V[v] < 10) return false;

	setNode(v, -1, makeNode(V[v]/2, -1, -1), makeNode((V[v]+1)/2, -1, -1));
	return true;
}

ostream& printTree(ostream &out, int v) {
	if (V[v] >= 0) return out << V[v];
	return printTree(printTree(out << '[', L[v]) << ',', R[v]) << ']';
}

ll magn(int v) {
	return V[v] >= 0 ? V[v] : 3*magn(L[v]) + 2*magn(R[v]);
}

void reduce(int root) {
	while (s_explosion(root, 0) || s_split(root));
		// printTree(cout, root) << endl;
}

int main() {
	fill_n(P, MAXN, -1);

	string line;
	getline(cin, line);
	int pos = 0, root2;
	int root = parse(line, pos);
	while (getline(cin, line)) {
		pos = 0;
		root2 = parse(line, pos);

		root = makeNode(-1, root, root2);
		printTree(cout, root) << endl;
		reduce(root);
		printTree(cout, root) << endl;
	}

	cout << magn(root) << endl;

	return 0;
}
