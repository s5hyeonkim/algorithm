#include <iostream>
#include <vector>
#include <set>
using namespace std;
int n, m, l, k, x, y, result;
vector<pair<int, int>> v;

void print(const set<pair<int, int>>& s) {
	cout << s.size() << '\n';
	for (const auto& p : s) {
		cout << v[p.second].first << " " << v[p.second].second << '\n';
	}
}

void selectMaxY(set<pair<int, int>> sx, set<pair<int, int>> sy) {
	int target = -1;
	while (!sy.empty() && result < sx.size()) {
		if (sy.rbegin()->first != target) {
			target = sy.rbegin()->first;
			if (target - sy.begin()->first <= l) {
				result = sx.size();
				return;
			}
		}
		else {
			sx.erase({ v[sy.rbegin()->second].second, sy.rbegin()->second });
			sy.erase(*sy.rbegin());
		}
	}
}

void selectMinY(set<pair<int, int>> sx, set<pair<int, int>> sy) {
	int target = -1;
	while (!sy.empty() && result < sx.size()) {
		if (sy.begin()->first != target) {
			selectMaxY(sx, sy);
			target = sy.begin()->first;
			if (sy.rbegin()->first - target <= l)
				break;
		}
		else {
			sx.erase({ v[sy.begin()->second].second, sy.begin()->second });
			sy.erase(*sy.begin());
		}
	}
}

void selectMaxX(set<pair<int, int>> sx, set<pair<int, int>> sy) {
	int target = -1;
	while (!sx.empty() && result < sx.size()) {
		if (sx.rbegin()->first != target) {
			target = sx.rbegin()->first;
			if (target - sx.begin()->first <= l) {
				selectMinY(sx, sy);
				return;
			}
		}
		else {
			sy.erase({ v[sx.rbegin()->second].first, sx.rbegin()->second });
			sx.erase(*sx.rbegin());
		}
	}
}

void selectMinX(set<pair<int, int>> sx, set<pair<int, int>> sy) {
	int target = -1;
	while (!sx.empty() && result < sx.size()) {
		if (sx.begin()->first != target) {
			selectMaxX(sx, sy);
			target = sx.begin()->first;
			if (sx.rbegin()->first - sx.begin()->first <= l)
				break;
		}
		else {
			sy.erase({ v[sx.begin()->second].first, sx.begin()->second });
			sx.erase(*sx.begin());
		}
	}
}

int main(void) {
	set<pair<int, int>> sx, sy;

	cin >> n >> m >> l >> k;
	v.resize(k);
	result = 1;
	for (int i = 0; i < k; i++) {
		cin >> x >> y;
		v[i] = { y, x };
		sy.insert({ y, i });
		sx.insert({ x, i });
	}
	selectMinX(sx, sy);
	cout << k - result << '\n';
}