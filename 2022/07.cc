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

const int MAXFILES = 1'000'000;

int nentries = 1, curfile = 0, parent[MAXFILES] = {};
ll fsize[MAXFILES] = {};

vector<pair<string, int>> subfiles[MAXFILES];

ll calculate_sizes(int file) {
	ll res = 0;
	for (auto [name, idx] : subfiles[file])
		res += calculate_sizes(idx), fsize[file] += fsize[idx];
	if (!subfiles[file].empty() && fsize[file] < 100'000)
		res += fsize[file];
	return res;
}

ll find_smallest(int file) {
	ll res = INT_MAX;
	for (auto [name, idx] : subfiles[file])
		res = min(res, find_smallest(idx));

	if (!subfiles[file].empty() && fsize[0] - fsize[file] <= 40'000'000)
		res = min(res, fsize[file]);
	return res;
}

int main() {
	string line;
	while (getline(cin, line), cin) {
		if (line == "$ ls") {
			continue;
		} else if (line[0] == '$') {
			assert(line[2] == 'c' && line[3] == 'd');
			line = line.substr(5);

			if (line == "/") {
				curfile = 0;
			} else if (line[0] == '.' && line[1] == '.') {
				curfile = parent[curfile];
			} else {
				int idx = -1, nr = 0;
				for (auto [nm, _] : subfiles[curfile]) {
					if (nm == line) { idx = nr; break; }
					nr++;
				}

				if (idx == -1) {
					idx = sz(subfiles[curfile]);
					parent[ nentries ] = curfile;
					subfiles[curfile].eb(line, nentries++);
				}
				curfile = subfiles[curfile][idx].second;
			}

		} else if ('0' <= line[0] && line[0] <= '9') {
			stringstream ss(line);
			string fname;
			int len;
			ss >> len >> fname;

			int idx = -1, nr = 0;
			for (auto [nm, _] : subfiles[curfile]) {
				if (nm == line) { idx = nr; break; }
				nr++;
			}

			assert(idx == -1);
			if (idx == -1) {
				idx = sz(subfiles[curfile]);
				parent[ nentries ] = curfile;
				subfiles[curfile].eb(line, nentries++);
			}
			fsize[subfiles[curfile][idx].second] = len;
		} else {
			assert(line[0] == 'd' && line[1] == 'i' && line[2] == 'r');
			line = line.substr(4);

			int idx = -1, nr = 0;
			for (auto [nm, _] : subfiles[curfile]) {
				if (nm == line) { idx = nr; break; }
				nr++;
			}

			assert(idx == -1);
			if (idx == -1) {
				idx = sz(subfiles[curfile]);
				parent[ nentries ] = curfile;
				subfiles[curfile].eb(line, nentries++);
			}
		}
	}

	printf("Part A: %lld\n", calculate_sizes(0));
	printf("Part B: %lld\n", find_smallest(0));
	return 0;
}
