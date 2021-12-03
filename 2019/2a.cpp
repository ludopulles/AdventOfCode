#include<bits/stdc++.h>
using namespace std;

long long run(vector<long long> v) {
	int ptr = 0;
	while (v[ptr] != 99) {
		long long lop = v[v[ptr+1]];
		long long rop = v[v[ptr+2]];
		v[v[ptr+3]] = (v[ptr] == 1 ? (lop+rop) : (lop*rop));
		ptr += 4;
	}
	return v[0];
}

int main() {
	vector<long long> v;

	char s[11];
	while (scanf("%10[^,]", s) == 1) {
		// printf("Reading %s\n", s);

		stringstream ss(s);
		int n;
		ss >> n;
		v.push_back(n);
		// not for the last one:

		int ch = getchar();
		assert(ch == ',' || ch == EOF);
	}

	// for (int x : v) cout << x << " ";
	// return 0;

	for (int nv = 0; ; nv++) {
		for (int noun = 0; noun <= nv; noun++) {
			int verb = nv - noun;
			v[1] = noun;
			v[2] = verb;
			
			if (run(v) == 19690720LL) {
				printf("%lld %lld -> %lld\n", noun, verb, 100LL * noun + verb);
			}
		}
	}
	return 0;
}
