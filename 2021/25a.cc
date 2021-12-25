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

string grid[137];
int H = 0, W = 0;

int main() {
	string line;
	while (getline(cin, line)) grid[H++] = line;
	W = grid[0].size();
	assert(H <= 137 && W <= 139);

	int time = 0;
	while (true) {
		bool moved = false;

		REP(i, H) {
			int j = 0;
			bool canMove = grid[i][0] == '.';
			for (; j < W-1; j++) if (grid[i][j] == '>' && grid[i][j+1] == '.')
				swap(grid[i][j], grid[i][j+1]), moved = true, j++;
			if (grid[i][W-1] == '>' && canMove && j < W)
				swap(grid[i][W-1], grid[i][0]), moved = true;
		}

		REP(j, W) {
			int i = 0;
			bool canMove = grid[0][j] == '.';
			for (; i < H-1; i++) if (grid[i][j] == 'v' && grid[i+1][j] == '.')
				swap(grid[i][j], grid[i+1][j]), moved = true, i++;
			if (grid[H-1][j] == 'v' && canMove && i < H)
				swap(grid[H-1][j], grid[0][j]), moved = true;
		}

		++time;
		if (!moved) break;
	}

	cout << "Finished: " << time << endl;


	return 0;
}
