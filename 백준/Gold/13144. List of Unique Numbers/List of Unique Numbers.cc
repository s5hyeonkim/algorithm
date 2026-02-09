#include <iostream>
#include <queue>
#include <vector>
using namespace std;
long long calculate(int size) {
	long long sum = 0;
	while (size) {
		sum += size;
		size--;
	}
	return sum;
}


int main(void) {
	vector<int> visited, nums;
	int n, l, r, prev_r;
    long long sum = 0;
	
	cin >> n;
	nums.resize(n + 1);
	visited.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> nums[i];
	sum = 0;
	r = 1;
	prev_r = 1;
	l = 1;
	while (l <= n && r <= n) {
		while (visited[nums[r]]) {
			visited[nums[l]]--;
			l++;
		}
		while (r <= n && !visited[nums[r]]) {
			visited[nums[r]]++;
			r++;
		}
		sum += calculate(r - l);
		sum -= calculate(prev_r - l);
		prev_r = r;
	}
	cout << sum << std::endl;
}