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

namespace std { template<class T1, class T2>
struct hash<pair<T1,T2>> { public:
	size_t operator()(const pair<T1,T2> &p) const {
		size_t x = hash<T1>()(p.x), y = hash<T2>()(p.y);
		return x ^ (y + 0x9e3779b9 + (x<<6) + (x>>2));
	}
}; }

bool is_num(const string &s, int &pos) {
	return pos < sz(s) && (s[pos] == '-' || ('0' <= s[pos] && s[pos] <= '9'));
}

ll parseInt(const string &s, int &pos) {
	ll res = 0, sgn = 1;
	if (pos < sz(s) && s[pos] == '-') sgn = -1, pos++;
	while (pos < sz(s) && '0' <= s[pos] && s[pos] <= '9')
		res = 10 * res + (s[pos++] - '0');
	return sgn * res;
}

vector<string> grid;
int nr, nc;

int smod(int x, int m) {
	return (x %= m) < 0 ? x+m : x;
}

bool blizzard(int t, int x, int y) {
	// printf("Checking %d, %d, %d\n", t, x, y);
	int x_up = 1 + smod(x + t - 1, nr - 2), y_up = 1 + smod(y + t - 1, nc - 2);
	int x_dw = 1 + smod(x - t - 1, nr - 2), y_dw = 1 + smod(y - t - 1, nc - 2);

	return grid[x_up][y] == '^' || grid[x_dw][y] == 'v' || grid[x][y_up] == '<' || grid[x][y_dw] == '>';
}

int time_to_move(ii from, ii to, int t0) {
	vector<unordered_set<ii>> pos; // All positions
	pos.eb();
	pos[0].insert(from);

	int time = 0;
	while (pos[time].find(to) == pos[time].end()) {
		/* printf("Time %d:\n", t0 + time);
		REP(x, nr) {
			REP(y, nc) {
				if (grid[x][y] == '#') printf("#");
				else if (pos[time].find(ii(x, y)) != pos[time].end()) printf("x");
				else {
					// Is there a blizzard?
					int nb = 0, t = time + t0;
					char dir = '-';

					int x_up = 1 + smod(x + t - 1, nr - 2), y_up = 1 + smod(y + t - 1, nc - 2);
					int x_dw = 1 + smod(x - t - 1, nr - 2), y_dw = 1 + smod(y - t - 1, nc - 2);

					if (grid[x_up][y] == '^') dir = '^', nb++;
					if (grid[x_dw][y] == 'v') dir = 'v', nb++;
					if (grid[x][y_up] == '<') dir = '<', nb++;
					if (grid[x][y_dw] == '>') dir = '>', nb++;

					if (nb == 0) printf(".");
					else if (nb >= 2) printf("%d", nb);
					else printf("%c", dir);
				}
			}
			printf("\n");
		} */

		unordered_set<ii> new_pos;
		for (auto [x,y] : pos[time]) {
			REP(dir, 5) {
				int nx = x + vi{ 0, 1, 0, -1, 0 }[dir];
				int ny = y + vi{ 0, 0, 1, 0, -1 }[dir];
				if ((nx == 0 && ny == 1) || (nx == nr - 1 && ny == nc - 2)) {
					new_pos.emplace(nx, ny);
				} else if (0 < nx && nx < nr - 1 && 0 < ny && ny < nc - 1 && !blizzard(t0 + time + 1, nx, ny)) {
					new_pos.emplace(nx, ny);
				}
			}
		}

		pos.eb(new_pos);
		time++;
	}


	return time;
}

int main() {
	string line;
	while (getline(cin, line), cin) {
		grid.pb(line);
	}

	nr = sz(grid), nc = sz(grid[0]);

	ii start(0, 1), eind(nr - 1, nc - 2);

	int t1 = time_to_move(start, eind, 0);
	printf("Part A: %d\n", t1);
	int t2 = time_to_move(eind, start, t1);
	int t3 = time_to_move(start, eind, t1 + t2);
	printf("Part B: %d (%d + %d + %d)\n", t1 + t2 + t3, t1, t2, t3);
	return 0;
}
