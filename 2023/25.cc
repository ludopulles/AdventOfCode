#include "header.h"

struct Edge { int t; ll c, f; };
struct Dinic {
	vi H, P; vvi E;
	vector<Edge> G;
	Dinic(int n) : H(n), P(n), E(n) {}

	void addEdge(int u, int v, ll c) {
		E[u].pb(G.size()); G.pb({v, c, 0LL});
		E[v].pb(G.size()); G.pb({u, 0LL, 0LL});
	}

	ll dfs(int t, int v, ll f) {
		if (v == t || !f) return f;
		for ( ; P[v] < (int) E[v].size(); P[v]++) {
			int e = E[v][P[v]], w = G[e].t;
			if (H[w] != H[v] + 1) continue;
			ll df = dfs(t, w, min(f, G[e].c - G[e].f));
			if (df > 0) {
				G[e].f += df, G[e ^ 1].f -= df;
				return df;
			}
		} return 0;
	}

	ll maxflow(int s, int t, ll f = 0) {
		while (1) {
			fill(all(H), 0); H[s] = 1;
			queue<int> q; q.push(s);
			while (!q.empty()) {
				int v = q.front(); q.pop();
				for (int w : E[v])
					if (G[w].f < G[w].c && !H[G[w].t])
						H[G[w].t] = H[v] + 1, q.push(G[w].t);
			}
			if (!H[t]) return f;
			fill(all(P), 0);
			while (ll df = dfs(t, s, LLONG_MAX)) f += df;
		}
	}
};

vector<string> names;
map<string, int> lookup;
vvi conn;

void DFS(Dinic &G, vector<bool> &v, int cur) {
	v[cur] = true;
	for (int e : G.E[cur]) {
		const Edge &edge = G.G[e];
		if (edge.f < edge.c && !v[edge.t]) DFS(G, v, edge.t);
	}
}
int main() {
	ll sumA = 0, sumB = 0;
	srand(time(NULL));

	string line;
	while (getline(cin, line), cin) {
		vector<string> vs = split_str(line, " ");

		string fr = vs[0].substr(0, sz(vs[0]) - 1);
		if (lookup.find(fr) == lookup.end())
			names.pb(fr), lookup[fr] = sz(conn), conn.pb(vi());
		for (int i = 1; i < sz(vs); i++) {
			const string &to = vs[i];
			if (lookup.find(to) == lookup.end())
				names.pb(to), lookup[to] = sz(conn), conn.pb(vi());

			conn[lookup[fr]].pb(lookup[to]);
			conn[lookup[to]].pb(lookup[fr]);
		}
	}

	int n = sz(conn), source, sink, flow = 0;
	Dinic G(0);
	do {
		source = rand() % n;
		sink = rand() % n;
		if (source == sink) continue;

		G = Dinic(n);
		// Build G
		REP(i, n) for (int j : conn[i]) G.addEdge(i, j, 1LL);

		flow = G.maxflow(source, sink);
	} while (flow != 3);

	cout << "Splitting in " << names[source] << " and " << names[sink] << endl;
	vector<bool> withSource(n);
	DFS(G, withSource, source);

	int sourceSize = 0;
	REP(i, n) sourceSize += withSource[i];
	sumA = sourceSize * (n - sourceSize);

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
