#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<string> map;
int r, c;

int backtracking(queue<pair<int, int>> &jpos_q, queue<pair<int, int>> &fpos_q, vector<vector<pair<int, int>>> &visited) {
	const int dr[] = { 0, 1, 0, -1 };
	const int dc[] = { -1, 0, 1, 0 };
	pair<int, int> npos, fpos, jpos;
	size_t size;

	jpos = jpos_q.front();
	if (jpos.first == r - 1 || jpos.second == c - 1 || !jpos.first || !jpos.second)
		return visited[jpos.first][jpos.second].first;
	while (!jpos_q.empty()) {
		size = fpos_q.size();
		while (size--) {
			fpos = fpos_q.front();
			fpos_q.pop();
			for (int i = 0; i < 4; i++) {
				npos = { fpos.first + dr[i], fpos.second + dc[i] };
				if (npos.first < 0 || npos.second < 0 || npos.first >= r || npos.second >= c)
					continue;
				if (map[npos.first][npos.second] == '#' || visited[npos.first][npos.second].second)
					continue;
				visited[npos.first][npos.second].second = visited[fpos.first][fpos.second].second + 1;
				fpos_q.push(npos);
			}

		}
		size = jpos_q.size();
		while (size--) {
			jpos = jpos_q.front();
			jpos_q.pop();
			for (int i = 0; i < 4; i++) {
				npos = { jpos.first + dr[i], jpos.second + dc[i] };
				if (npos.first < 0 || npos.second < 0 || npos.first >= r || npos.second >= c)
					continue;
				if (map[npos.first][npos.second] == '#' || visited[npos.first][npos.second].first || visited[npos.first][npos.second].second)
					continue;
				if (npos.first == r - 1 || npos.second == c - 1 || !npos.first || !npos.second)
					return visited[jpos.first][jpos.second].first + 1;
				visited[npos.first][npos.second].first = visited[jpos.first][jpos.second].first + 1;
				jpos_q.push(npos);
			}
		}
	}
	return 0;
}

int main(void) {
	queue<pair<int, int>> fpos_q, jpos_q;
	pair<int, int> jpos, fpos;
	vector<vector<pair<int, int>>> visited;
	int ret;

	cin >> r >> c;
	map.resize(r);
	visited.resize(r);
	for (int i = 0; i < r; i++) {
		visited[i].resize(c, { 0, 0 });
		cin >> map[i];
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 'J') {
				jpos_q.push({ i, j });
				visited[i][j].first = 1;
			}
			else if (map[i][j] == 'F') {
				fpos_q.push({ i, j });
				visited[i][j].second = 1;
			}
		}
	}
	if ((ret = backtracking(jpos_q, fpos_q, visited)))
		cout << ret << std::endl;
	else
		cout << "IMPOSSIBLE" << std::endl;
}