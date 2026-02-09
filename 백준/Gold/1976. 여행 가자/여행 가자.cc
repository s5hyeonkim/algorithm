#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(void) {
	int n, m, city, cur;
	vector<vector<int>> node;
	vector<int> target, visited;
	queue<int> q;

	cin >> n >> m;
	node.resize(n + 1);
	target.resize(n + 1, 0);
	visited.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		node[i].resize(n + 1);
		for (int j = 1; j <= n; j++) {
			cin >> node[i][j];
		}
	}
	for (int i = 1; i <= m; i++) {
		cin >> city;
		target[city] = 1;
	}
	visited[city] = 1;
	q.push(city);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (int i = 1; i <= n; i++) {
			if (node[cur][i] && !visited[i]) {
				visited[i] = 1;
				q.push(i);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (target[i] && !visited[i]) {
			cout << "NO\n";
			return 0;
		}
	}
	cout << "YES" << std::endl;;
}