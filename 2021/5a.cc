#include<bits/stdc++.h>
using namespace std;

bool seen[1000][1000]={};
set<pair<int,int>> sol;

int main() {
	string line;
	while (getline(cin, line), cin) {
		for (char &ch : line)
			if (ch < '0' || ch > '9') ch = ' ';
		stringstream ss(line);
		int x1,y1,x2,y2;
		ss >> x1 >> y1 >> x2 >> y2;
		if (y1 == y2) {
			for (int x=min(x1,x2); x <= max(x1,x2); x++) {
				if (seen[x][y1]) sol.emplace(x,y1);
				seen[x][y1] = true;
			}
		} else if (x1 == x2) {
			for (int y=min(y1,y2); y <= max(y1,y2); y++) {
				if (seen[x1][y]) sol.emplace(x1,y);
				seen[x1][y] = true;
			}
		/* } else if (x1 + y1 == x2 + y2) {
			if (x1 > x2) swap(x1, x2);
			for (int x=x1,y=y1; x <= x2; x++, y--) {
				if (seen[x][y]) sol.emplace(x,y);
				seen[x][y] = true;
			}
		} else if (x1 - y1 == x2 - y2) {
			if (x1 > x2) swap(x1, x2);
			for (int x=x1,y=y1; x <= x2; x++, y++) {
				if (seen[x][y]) sol.emplace(x,y);
				seen[x][y] = true;
			} */
		} else cerr << "WUUT" << endl;
	}

	/* for (int i=0; i<20; i++) {
		for (int j=0; j<20; j++)
			cout << seen[i][j];
		cout << endl;
	} */

	cout << sol.size() << endl;
	return 0;
}
