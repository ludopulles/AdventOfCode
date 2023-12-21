#include "header.h"

vvi seqs;

bool isconstant(const vi &seq, int i0) {
	for (int i = i0; i + 1 < sz(seq); i++) if (seq[i] != seq[i + 1]) return false;
	return true;
}

void differentiate(vi &seq, int i0) {
	for (int i = sz(seq) - 1; i > i0; i--) seq[i] -= seq[i - 1];
}

void integrate(vi &seq, int i0) {
	for (int i = i0 + 1; i < sz(seq); i++) seq[i] += seq[i - 1];
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), cin) {
		vi nums;
		int pos = 0;
		while (pos < sz(line))
			nums.pb(parse_int(line, pos)), ++pos;
		seqs.pb(nums);
	}

	for (vi seq : seqs) {
		vi curseq = seq;
		int deltas = 0;
		for (; !isconstant(curseq, deltas); ++deltas) {
			differentiate(curseq, deltas); 
		}
		int before = curseq[deltas];
		curseq.pb(curseq[deltas]);
		while (deltas --> 0) {
			before = curseq[deltas] - before;
			// curseq[deltas + 1] += curseq[deltas];
			// curseq[deltas + 2] += curseq[deltas + 1];
			integrate(curseq, deltas);
		}

		sumA += curseq.back();
		sumB += before;
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
