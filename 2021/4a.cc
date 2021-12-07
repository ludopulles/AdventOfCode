#include<bits/stdc++.h>
using namespace std;

struct Board {
	int x[5][5];
};

int main() {
	string movesS;
	getline(cin, movesS);

	for (char &ch : movesS)
		if (ch == ',') ch = ' ';
	
	stringstream ss(movesS);
	vector<int> moves;
	for (int x; ss >> x; ) moves.push_back(x);

	vector<Board> boards;
	vector<int> sums;
	vector<array<int,5>> mrow, mcol;

	while (true) {
		bool stop = false;
		Board b;
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				if (!(cin >> b.x[r][c])) {
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
		if (stop) break;

		boards.push_back(b);
		int s = 0;
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				s += b.x[r][c];
			}
		}
		sums.push_back(s);
		mrow.emplace_back();
		mcol.emplace_back();
	}

	int nb = (int) boards.size();
	set<int> seen;
	for (int number : moves) {
		if (seen.find(number) != seen.end())
			continue;
		seen.insert(number);

		for (int i=0; i<nb; i++) {
			for (int r = 0; r < 5; r++) {
				for (int c = 0; c < 5; c++) {
					if (boards[i].x[r][c] == number) {
						sums[i] -= number;
						if (++mrow[i][r] == 5 || ++mcol[i][c] == 5) {
							cout << (number * sums[i]) << endl;
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}
