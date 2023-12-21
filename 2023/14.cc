#include "header.h"

ll eval(const vector<string> &grid) {
	ll res = 0;
	for (int row = 0; row < sz(grid); row++) {
		for (int col = 0; col < sz(grid[row]); col++) {
			if (grid[row][col] == 'O')
				res += sz(grid) - row;
		}
	}
	return res;
}

ll partA(vector<string> grid) {
	for (int row = 0; row < sz(grid); row++) {
		for (int col = 0; col < sz(grid[row]); col++) {
			if (grid[row][col] != 'O') continue;

			// move up
			int r = row;
			while (r > 0 && grid[r - 1][col] == '.' && grid[r][col] == 'O') {
				swap(grid[r - 1][col], grid[r][col]);
				r--;
			}
		}
	}

	return eval(grid);
}

void rotateRound(vector<string> &grid) {
	for (int row = 0; row < sz(grid); row++) {
		for (int col = 0; col < sz(grid[row]); col++) {
			if (grid[row][col] != 'O') continue;
			int r = row; // move up
			while (r > 0 && grid[r - 1][col] == '.' && grid[r][col] == 'O') {
				swap(grid[r - 1][col], grid[r][col]); r--;
			}
		}
	}

	for (int row = 0; row < sz(grid); row++) {
		for (int col = 0; col < sz(grid[row]); col++) {
			if (grid[row][col] != 'O') continue;
			int c = col; // move left
			while (c > 0 && grid[row][c - 1] == '.' && grid[row][c] == 'O') {
				swap(grid[row][c - 1], grid[row][c]); c--;
			}
		}
	}

	for (int row = sz(grid) - 1; row >= 0; row--) {
		for (int col = 0; col < sz(grid[row]); col++) {
			if (grid[row][col] != 'O') continue;
			int r = row; // move down
			while (r + 1 < sz(grid) && grid[r + 1][col] == '.' && grid[r][col] == 'O') {
				swap(grid[r + 1][col], grid[r][col]); r++;
			}
		}
	}

	for (int row = 0; row < sz(grid); row++) {
		for (int col = sz(grid[row]) - 1; col >= 0; col--) {
			if (grid[row][col] != 'O') continue;
			int c = col; // move right
			while (c + 1 < sz(grid[row]) && grid[row][c + 1] == '.' && grid[row][c] == 'O') {
				swap(grid[row][c + 1], grid[row][c]); c++;
			}
		}
	}
}

ll partB(vector<string> grid) {
	vector<vector<string>> seq;
	map<vector<string>, int> lookup;

	while (lookup.find(grid) == lookup.end()) {
		lookup[grid] = sz(seq);
		seq.pb(grid);
		rotateRound(grid);
	}

	ll precyc = lookup[grid], cycle_len = seq.size() - precyc;
	ll num = precyc + (1'000'000'000LL - precyc) % cycle_len;
	return eval(seq[num]);
}



int main() {
	vector<string> grid;
	string line;
	while (getline(cin, line), cin) grid.pb(line);

	ll sumA = partA(grid);
	cout << "Part A: " << sumA << endl;
	ll sumB = partB(grid);
	cout << "Part B: " << sumB << endl;
	return 0;
}
