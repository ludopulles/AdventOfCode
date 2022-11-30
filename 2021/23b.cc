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

string board[7];
const int moveCost[4] = { 1, 10, 100, 1000 };

bool isEnd() {
	rep(r, 2, 6) REP(t, 4)
		if (board[r][3+2*t] != 'A' + t) return false;
	return true;
}

__int128 hashboard() {
	int p[16];
	REP(i, 16) p[i] = -1;
	rep(r, 1, 6) rep(c, 1, 12) if (board[r][c] != '#' && board[r][c] != '.') {
		int type = board[r][c] - 'A', loc = (r<<4) | c, insP = 4*type;
		while (p[insP] >= 0) insP++;
		p[insP] = loc;
	}
	__int128 res = 0;
	REP(i, 16) res = (res<<8) | p[i];
	return res;
}

map<__int128, int> lookup;

int bestSol = INT_MAX, calls = 0;

int search(int accCost) {
	calls++;
	if (accCost >= bestSol) return INT_MAX; // nothing better here

	__int128 H = hashboard();
	if (lookup.find(H) != lookup.end())
		return lookup[H] == INT_MAX ? INT_MAX : accCost + lookup[H];

	if (isEnd()) {
		bestSol = min(bestSol, accCost);
		return accCost;
	}

	int res = INT_MAX;
	// modify the current board
	rep(r, 1, 6) rep(c, 1, 12) if (board[r][c] != '#' && board[r][c] != '.') {
		int type = board[r][c] - 'A';
		int tr = 5, tc = 3 + 2*type; // target column
		while (board[tr][tc] == 'A' + type) --tr;

		bool canfill = true;
		for (int rr = 2; rr <= tr; rr++)
			canfill &= board[rr][tc] == '.';

		if (r == 1) {
			if (!canfill)
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

		if (tc == c && r > tr) continue; // this column is done

		int upr = r;
		while (board[upr-1][c] == '.') upr--;
		if (upr != 1) continue; // we cannot move to hallway

		int loc = c, hic = c;
		while (board[1][loc-1] == '.') loc--;
		while (board[1][hic+1] == '.') hic++;

		if (canfill && tc != c && loc <= tc && tc <= hic) {
			int cost = (abs(tc - c) + (tr - 1) + (r - 1)) * moveCost[type];
			swap(board[r][c], board[tr][tc]);
			res = min(res, search(accCost + cost));
			swap(board[r][c], board[tr][tc]);
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
	REP(i, 3) getline(cin, board[i]);
	board[3] = "###D#C#B#A###";
	board[4] = "###D#B#A#C###";
	for (int i=5; i <= 6; i++) getline(cin, board[i]);
	board[5].resize(11);
	board[6].resize(11);
	board[5].resize(13, '#');
	board[6].resize(13, '#');
	board[5][0] = board[5][1] = board[6][0] = board[6][1] = '#';

	int cost = search(0);
	cout << cost << endl;
	cout << "Calls: " << calls << endl;
	return 0;
}
