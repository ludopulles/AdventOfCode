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

int H, W;
vector<string> grid;
map<ii, vector<ll>> numbers;

int main() {
	string line;
	while (getline(cin, line), cin) {
		grid.push_back(line);
	}

	H = sz(grid);
	W = sz(grid[0]);

	ll sumA = 0, sumB = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; ) {
			if (!is_num(grid[row], col) || grid[row][col] == '-') {
				col++;
				continue;
			}

			int oldcol = col;
			ll num = parse_int(grid[row], col);

			set<char> touches;
			vector<ii> gears;
			for (int r = row - 1; r <= row + 1; r++) {
				for (int c = oldcol - 1; c <= col; c++) {
					if (0 <= r && r < H && 0 <= c && c < W && grid[r][c] != '.' && (grid[r][c] < '0' || grid[r][c] > '9')) {
						touches.insert(grid[r][c]);
						if (grid[r][c] == '*') gears.emplace_back((ll) r, (ll) c);
					}
				}
			}
			if (!touches.empty()) {
				sumA += num;
				for (ii gear : gears) numbers[gear].push_back(num);
			}
		}
	}

	for (auto [loc, list] : numbers) {
		if (list.size() == 2) sumB += list[0] * list[1];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
