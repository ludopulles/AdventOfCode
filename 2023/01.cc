#include "header.h"

const string spelled[9] = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main() {
	string line;

	int sumA = 0;
	int sumB = 0;
	while (getline(cin, line), cin) {
		int n = (int) line.size();

		int fd = -1, ld = -1;

		for (int i = 0; i < n; i++) {
			if ('0' <= line[i] && line[i] <= '9') {
				fd = line[i] - '0';
				break;
			}
		}

		for (int i = n; i --> 0; ) {
			if ('0' <= line[i] && line[i] <= '9') {
				ld = line[i] - '0';
				break;
			}
		}

		sumA += fd*10 + ld;

		fd = ld = -1;
		for (int i = 0; i < n; i++) {
			if ('0' <= line[i] && line[i] <= '9') {
				fd = line[i] - '0';
				break;
			}
			for (int j = 0; j < 9; j++) {
				if (i + (int) spelled[j].size() < n && line.substr(i, spelled[j].size()) == spelled[j]) {
					fd = j + 1; break;
				}
			}
			if (fd != -1) break;
		}

		for (int i = n; i > 0; i--) {
			if ('0' <= line[i-1] && line[i-1] <= '9') {
				ld = line[i-1] - '0';
				break;
			}
			// cout << i << endl;
			for (int j = 0; j < 9; j++) {
				if (i - (int) spelled[j].size() >= 0 && line.substr(i - spelled[j].size(), spelled[j].size()) == spelled[j]) {
					ld = j + 1; break;
				}
			}
			if (ld != -1) break;
		}

		sumB += fd*10 + ld;
	}

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;

	return 0;
}
