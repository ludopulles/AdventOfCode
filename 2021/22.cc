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

struct Cuboid {
	bool turnOn;
	int x1, x2, y1, y2, z1, z2;
	int x1m, x2m, y1m, y2m, z1m, z2m;
};

bool read(Cuboid &c) {
	string line, cmd;
	if (!getline(cin, line)) return false;
	for (char &ch : line)
		if (ch == '=' || ch == ',' || ch == '.') ch = ' ';
	stringstream ss(line);

	ss >> cmd;
	c.turnOn = cmd == "on";
	if (cmd != "on") assert(cmd == "off");
	ss >> cmd, assert(cmd == "x");
	ss >> c.x1 >> c.x2;
	ss >> cmd, assert(cmd == "y");
	ss >> c.y1 >> c.y2;
	ss >> cmd, assert(cmd == "z");
	ss >> c.z1 >> c.z2;

	c.x2++; c.y2++; c.z2++;
	return true;
}

const int MAXC = 840;

bitset<MAXC> prefix[MAXC+1], B[MAXC][MAXC];

void   setrange(bitset<MAXC> &b, int fr, int to) { b |= prefix[to] & ~prefix[fr]; }
void resetrange(bitset<MAXC> &b, int fr, int to) { b &= prefix[fr] | ~prefix[to]; }

int main() {
	assert(prefix[0].count() == 0);
	for (int i=1; i <= MAXC; i++) {
		prefix[i] |= prefix[i-1];
		prefix[i].set(i-1);
	}

	vector<Cuboid> cmds;
	for (Cuboid c; read(c); ) {
		cmds.pb(c);
	}
	cout << cmds.size() << " cuboids were read" << endl;

	set<int> xs({-50,51}), ys({-50,51}), zs({-50,51});
	for (Cuboid c : cmds) {
		xs.insert(c.x1), xs.insert(c.x2);
		ys.insert(c.y1), ys.insert(c.y2);
		zs.insert(c.z1), zs.insert(c.z2);
	}

	vi xsv(all(xs)), ysv(all(ys)), zsv(all(zs));
	for (Cuboid &c : cmds) {
		c.x1m = lower_bound(all(xsv), c.x1) - xsv.begin();
		c.x2m = lower_bound(all(xsv), c.x2) - xsv.begin();
		c.y1m = lower_bound(all(ysv), c.y1) - ysv.begin();
		c.y2m = lower_bound(all(ysv), c.y2) - ysv.begin();
		c.z1m = lower_bound(all(zsv), c.z1) - zsv.begin();
		c.z2m = lower_bound(all(zsv), c.z2) - zsv.begin();
	}

	for (Cuboid &c : cmds) {
		rep(x, c.x1m, c.x2m) rep(y, c.y1m, c.y2m) {
			if (c.turnOn)
				setrange(B[x][y], c.z1m, c.z2m);
			else
				resetrange(B[x][y], c.z1m, c.z2m);
		}
	}

	ll answerA = 0, answerB = 0;
	REP(x, MAXC) REP(y, MAXC) {
		int nleft = B[x][y].count();
		if (nleft == 0) continue;
		ll subv = (xsv[x+1] - xsv[x]) * (ysv[y+1] - ysv[y]);
		REP(z, MAXC) {
			if (!B[x][y].test(z)) continue;
			ll volume = subv * (zsv[z+1] - zsv[z]);
			if (-50 <= xsv[x] && xsv[x] <= 50 && 
					-50 <= ysv[y] && ysv[y] <= 50 && 
					-50 <= zsv[z] && zsv[z] <= 50) {
				answerA += volume;
			}
			answerB += volume;
			if (--nleft == 0) break;
		}
	}

	cout << "Part A: " << answerA << endl;
	cout << "Part B: " << answerB << endl;

	return 0;
}
