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

string board[5];
const int moveCost[4] = { 1, 10, 100, 1000 };

bool isEnd() {
	return board[2][3] == 'A' && board[3][3] == 'A'
		&& board[2][5] == 'B' && board[3][5] == 'B'
		&& board[2][7] == 'C' && board[3][7] == 'C'
		&& board[2][9] == 'D' && board[3][9] == 'D';
}

ll hashboard() {
	int p[8];
	REP(i, 8) p[i] = -1;
	rep(r, 1, 4) rep(c, 1, 12) if (board[r][c] != '#' && board[r][c] != '.') {
		int type = board[r][c] - 'A', loc = (r<<4) | c;
		if (p[2*type] < 0) p[2*type] = loc;
		else p[2*type+1] = loc;
	}
	ll res = 0;
	REP(i, 8) res = (res<<8) | p[i];
	return res;
}

unordered_map<ll, int> lookup;

int bestSol = INT_MAX;

int search(int accCost) {
	if (accCost >= bestSol) return INT_MAX; // nothing better here

	ll H = hashboard();
	if (lookup.find(H) != lookup.end())
		return lookup[H] == INT_MAX ? INT_MAX : accCost + lookup[H];

	if (isEnd()) {
		bestSol = min(bestSol, accCost);
		return accCost;
	}

	int res = INT_MAX;
	// modify the current board
	rep(r, 1, 4) rep(c, 1, 12) if (board[r][c] != '#' && board[r][c] != '.') {
		int type = board[r][c] - 'A';
		int tr = 3, tc = 3 + 2*type; // target column
		if (board[tr][tc] == 'A' + type) tr = 2;

		if (r == 1) {
			if (board[2][tc] != '.' || board[tr][tc] != '.')
				continue; // we cannot move to target

			int cc = c;
			while (cc < tc && board[r][cc+1] == '.') ++cc;
			while (cc > tc && board[r][cc-1] == '.') --cc;
			if (cc != tc) continue; // we cannot move to target

			int cost = (abs(tc - c) + (tr - r)) * moveCost[type];
			swap(board[r][c], board[tr][tc]);
			res = min(res, search(accCost + cost));
			swap(board[r][c], board[tr][tc]);
			continue;
		}

		if (tc == c && (r == 3 || board[2][tc] == board[3][tc]))
			continue; // this column is done
		if (r == 3 && board[2][c] != '.') continue; // we cannot move

		int loc = c, hic = c;
		while (board[1][loc-1] == '.') loc--;
		while (board[1][hic+1] == '.') hic++;

		if (tc != c && loc <= tc && tc <= hic && board[2][tc] == '.'
				&& (board[3][tc] == '.' || board[3][tc] == 'A' + type)) {
			int rr = board[3][tc] == '.' ? 3 : 2;
			int cost = (abs(tc - c) + (rr - 1) + (r - 1)) * moveCost[type];
			swap(board[r][c], board[rr][tc]);
			res = min(res, search(accCost + cost));
			swap(board[r][c], board[rr][tc]);
			continue;
		}

		for (int cc = loc; cc <= hic; cc++) {
			if (cc != 3 && cc != 5 && cc != 7 && cc != 9) {
				int cost = (abs(cc - c) + (r - 1)) * moveCost[type];
				swap(board[r][c], board[1][cc]);
				res = min(res, search(accCost + cost));
				swap(board[r][c], board[1][cc]);
			}	
		}
	}

	lookup[H] = res == INT_MAX ? INT_MAX : (res - accCost);
	return res;
}

int main() {
	REP(i, 5)
		getline(cin, board[i]);
	board[3].resize(11);
	board[4].resize(11);
	board[3].resize(13, '#');
	board[4].resize(13, '#');
	board[3][0] = board[3][1] = board[4][0] = board[4][1] = '#';

	int cost = search(0);
	cout << cost << endl;
	return 0;
}
