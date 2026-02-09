#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(void) {
	vector<int> height, idx, r, l;
	//stack<pair<int, int>> s;
	stack<int> s;
	pair<int, int> cur;
	int n;

	cin >> n;
	height.resize(n + 1);
	idx.resize(n + 1, 0);
	r.resize(n + 1, 0);
	l.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> height[i];
	
	for (int i = n; i >= 1; i--) {
		while (!s.empty()) {
			if (height[s.top()] > height[i]) {
				r[i] = r[s.top()] + 1;
				idx[i] = s.top();
				break;
			}
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty())
		s.pop();
	for (int i = 1; i <= n; i++) {
		while (!s.empty()) {
			if (height[s.top()] > height[i]) {
				l[i] = l[s.top()] + 1;
				if (!idx[i] || idx[i] - i >= i - s.top())
					idx[i] = s.top();
				break;
			}
			s.pop();
		}
		s.push(i);
	}
	for (int i = 1; i <= n; i++) {
		if (l[i] + r[i] == 0) {
			cout << 0 << std::endl;
			continue;
		}
		cout << l[i] + r[i] << " " << idx[i] << '\n';
	}
}