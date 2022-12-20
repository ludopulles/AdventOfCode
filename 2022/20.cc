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

bool areSame(vi &A, vi &B) {
	int i = find(all(A), 0) - begin(A);
	int j = find(all(B), 0) - begin(B);
	int n = sz(A);
	if (n != sz(B)) return false;
	REP(k, n)
		if (A[(k + i) % n] != B[(k + j) % n]) return false;
	return true;
}

void fix0(vi &A) {
	int n = sz(A);
	vi copy(A);

	int i0 = find(all(A), 0) - begin(A);

	REP(i, n) A[i] = copy[(i + i0) % n];
}

void decrypt(vi &A) {
	int n = sz(A);
	vii B;
	REP(i, n) B.eb(i, A[i]);

	// Now execute in order of first component
	REP(k, n) {
		int i = 0;
		while (B[i].x != k) i++;
		ll moves = B[i].y;

		moves %= n-1;

		if (moves < 0) REP(_, -moves) {
			// move one place back
			int j = (i != 0 ? i : n) - 1;
			swap(B[i], B[j]);
			i = j;
		} else REP(_, moves) {
			// move one place forward
			int j = (i < n - 1 ? i + 1 : 0);
			swap(B[i], B[j]);
			i = j;
		}
	}
	REP(i, n) A[i] = B[i].y;
}

void decryptB(vi &A) {
	int n = sz(A);
	vii B;
	REP(i, n) B.eb(i, A[i]);

	// Now execute in order of first component
	REP(reps, 10) REP(k, n) {
		int i = 0;
		while (B[i].x != k) i++;
		ll moves = B[i].y;

		moves %= n-1;

		if (moves < 0) REP(_, -moves) {
			// move one place back
			int j = (i != 0 ? i : n) - 1;
			swap(B[i], B[j]);
			i = j;
		} else REP(_, moves) {
			// move one place forward
			int j = (i < n - 1 ? i + 1 : 0);
			swap(B[i], B[j]);
			i = j;
		}
	}
	REP(i, n) A[i] = B[i].y;
}

int main() {
	int num;
	vi A;
	while (cin >> num) A.pb(num);
	vi B(all(A));

	decrypt(A);

	int i = find(all(A), 0) - begin(A), n = sz(A), sum = 0;
	assert(i != n);

	rep(j, 0, 4) sum += A[(i + j * 1000) % n];

	printf("Part A: %d\n", sum);

	for (ll &x : B) x *= 811589153;
	decryptB(B);

	i = find(all(B), 0) - begin(B), n = sz(B);
	ll sumB = 0;
	rep(j, 0, 4) {
		ll x = B[(i + j * 1000) % n];
		sumB += x;
	}
	printf("Part B: %lld\n", sumB);

	return 0;
}
