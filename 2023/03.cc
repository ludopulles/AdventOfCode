#include "header.h"

int H, W;
vector<string> grid;
map<ii, vector<ll>> nums;

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
				for (ii gear : gears) nums[gear].push_back(num);
			}
		}
	}

	for (auto [loc, list] : nums) {
		if (list.size() == 2) sumB += list[0] * list[1];
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
