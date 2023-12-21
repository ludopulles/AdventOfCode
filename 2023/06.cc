#include "header.h"

string replaceAll(const string &s, const string &from, const string &to) {
	string res;
	assert(from != "");
	size_t pos = 0, newpos;
	while ((newpos = s.find(from, pos)) != string::npos) {
		res += s.substr(pos, newpos - pos) + to;
		pos = newpos + from.size();
	}
	return res + s.substr(pos);
}

ll solveTask(ll t, ll d) {
	ll t1 = ceill((t - sqrtl(t*t - 4*d)) / 2);
	ll t2 = floorl((t + sqrtl(t*t - 4*d)) / 2);
	if (t1 * (t - t1) == d) ++t1;
	if (t2 * (t - t2) == d) --t2;
	return t2 - t1 + 1;
}

int main() {
	ll sumA = 1, sumB = 0;

	string line1, line2;
	getline(cin, line1);
	getline(cin, line2);

	vector<ll> times = parse_ints(split_str(line1.substr(11), " "));
	vector<ll> dists = parse_ints(split_str(line2.substr(11), " "));

	for (int i = 0; i < sz(times); i++) {
		ll t = times[i], d = dists[i];
		sumA *= solveTask(t, d);
	}

	sumB = solveTask(parse_int(replaceAll(line1.substr(11), " ", "")),
					 parse_int(replaceAll(line2.substr(11), " ", "")));

	cout << "Part A: " << sumA << endl;
	cout << "Part B: " << sumB << endl;
	return 0;
}
