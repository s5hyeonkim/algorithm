#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
	queue<int> q;
	int n, req, conn, cur;
	char type;

	cin >> n;
	while (n) {
		vector<pair<char, int>> rooms(n + 1);
		vector<vector<int>> node(n + 1);
		vector<int> visited(n + 1, -1);
		for (int room_id = 1; room_id <= n; room_id++) {
			cin >> type >> req;
			rooms[room_id] = { type, req };
			cin >> conn;
			while (conn) {
				node[room_id].push_back(conn);
				cin >> conn;
			}
		}
		q.push({1});
		visited[1] = 0;
		while (!q.empty() && visited[n] == -1) {
			cur = q.front();
			q.pop();
			for (const auto& nroom : node[cur]) {
				switch (rooms[nroom].first) {
					case 'E' :
						if (visited[nroom] == -1 || visited[nroom] < visited[cur]) {
							visited[nroom] = visited[cur];
							q.push(nroom);
						}
						break;
					case 'L' :
						if (visited[nroom] == -1 || visited[nroom] < max(visited[cur], rooms[nroom].second)) {
							visited[nroom] = max(visited[cur], rooms[nroom].second);
							q.push(nroom);
						}
						break;
					case 'T' :
						if (visited[nroom] < visited[cur] - rooms[nroom].second) {
							visited[nroom] = visited[cur] - rooms[nroom].second;
							q.push(nroom);
						}
						break;
				}
			}
		}
		if (visited[n] != -1)
			cout << "Yes" << std::endl;
		else
			cout << "No" << std::endl;
		cin >> n;
	}
}