#include "header.h"

struct Instr {
	char name, cmp;
	ll cmpVal;
	string towards;
};

struct Range {
	map<char, ll> low, high;
};

bool isempty(const Range &r) {
	for (auto [ch, l] : r.low)
		if (l > r.high.find(ch)->y) return true;
	return false;
}

ll evalRange(const Range &r) {
	if (isempty(r)) return 0;
	ll prod = 1;
	for (auto [ch, l] : r.low)
		prod *= (r.high.find(ch)->y - l + 1);
	return prod;
}

pair<Range, Range> splitRange(const Range &r, const Instr &instr)
{
	Range r2 = r, r3 = r;
	if (instr.cmp == '>') {
		r2.low[instr.name] = max(r2.low[instr.name], instr.cmpVal + 1);
		r3.high[instr.name] = min(r3.high[instr.name], instr.cmpVal);
	} else {
		r2.high[instr.name] = min(r2.high[instr.name], instr.cmpVal - 1);
		r3.low[instr.name] = max(r3.low[instr.name], instr.cmpVal);
	}
	return make_pair(r2, r3);
}

map<string, vector<Instr>> instrs;

ll solveB(string cur, const Range &r) {
	if (cur == "R" || cur == "A") {
		return cur == "A" ? evalRange(r) : 0;
	}

	ll res = 0LL;
	Range cur_r = r;
	for (const Instr &inst : instrs[cur]) {
		if (inst.name == '\0') {
			res += solveB(inst.towards, cur_r);
		} else {
			auto [r0, r1] = splitRange(cur_r, inst);
			res += solveB(inst.towards, r0);
			if (isempty(r1)) break;
			cur_r = r1;
		}
	}
	return res;
}

int main() {
	ll sumA = 0, sumB = 0;

	string line;
	while (getline(cin, line), line != "") {
		// Parse instruction
		assert(line.back() == '}');
		auto [name, partsS] = split_at(line.substr(0, sz(line) - 1), "{");

		vector<Instr> lst;
		auto parts = split_str(partsS, ",");
		assert(sz(parts) >= 1);
		for (auto part : parts) {
			if (part.find(':') == string::npos) {
				lst.pb(Instr{ '\0', '\0', 0, part});
			} else {
				auto [pre, post] = split_at(part.substr(2), ":");
				lst.pb(Instr{ part[0], part[1], parse_int(pre), post });
			}
		}
		instrs[name] = lst;
	}

	while (getline(cin, line), cin) {
		// Go through process
		assert(line[0] == '{' && line.back() == '}');
		auto parts = split_str(line.substr(1, sz(line) - 2), ",");
		
		map<char, ll> vals;
		for (string part : parts) {
			auto [name, val] = split_at(part, "=");
			assert(sz(name) == 1);
			vals[name[0]] = parse_int(val);
		}

		string cur = "in";
		while (cur != "R" && cur != "A") {
			cerr << cur << " -> ";
			bool broken = false;
			for (const Instr &inst : instrs[cur]) {
				if (inst.name == '\0' ||
					(inst.cmp == '>' && vals[inst.name] > inst.cmpVal) ||
					(inst.cmp == '<' && vals[inst.name] < inst.cmpVal)) {
					cur = inst.towards;
					broken = true;
					break;
				}
			}
			assert(broken);
		}
		// cerr << cur << endl;

		if (cur == "A") for (auto [ch, val] : vals) sumA += val;
	}
	cout << "Part A: " << sumA << endl;

	Range r0 = Range{
		{{'x',1},{'m',1},{'a',1},{'s',1}},
		{{'x',4000},{'m',4000},{'a',4000},{'s',4000}},
	};
	sumB = solveB("in", r0);

	cout << "Part B: " << sumB << endl;
	return 0;
}
