#include <iostream>
#include <deque>
#include <stack>
using namespace std;
int check(stack<int>& s, const int& height) {
	while (!s.empty() && s.top() > height)
		s.pop();
	if (height && (s.empty() || s.top() < height)) {
		s.push(height);
		return 1;
	}
	return 0;
}

int main(void) {
	deque<pair<int, int>> height;
	stack<int> built;
	int n, cnt;

	cin >> n;
	cnt = 0;
	height.resize(n);
	for (int i = 0; i < n; i++)
		cin >> height[i].first >> height[i].second;
	for (int i = 0; i < n; i++)
		cnt += check(built, height[i].second);
	cout << cnt << std::endl;
}