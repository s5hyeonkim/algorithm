#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <set>
using namespace std;
int r, c;

void bfs(const pair<int, int>& beg, vector<string>& map) {
	queue<pair<int, int>> q;
	set<pair<int, int>> s;
	pair<int, int> cur, npos;
	const int dr[] = { 0, -1, 0, 1 };
	const int dc[] = { -1, 0, 1, 0 };
	int mn, i;
	
	q.push(beg);
	s.insert(beg);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			npos = { cur.first + dr[i], cur.second + dc[i] };
			if (npos.first < 1 || npos.second < 0 || npos.first > r || npos.second >= c)
				continue;
			if (s.find(npos) != s.end() || map[npos.first][npos.second] != 'x')
				continue;
			if (!npos.first)
				return;
			s.insert(npos);
			q.push(npos);
		}
	}
	mn = 500;
	for (set<pair<int, int>>::const_iterator rit = s.cbegin(); rit != s.cend(); rit++) {
		for (int i = rit->first - 1; i >= 0; i--) {
			if (!i || map[i][rit->second] == 'x') {
				if (s.find({ i, rit->second }) == s.end())
					mn = min(mn, rit->first - (i + 1));
				break;
			}
		}
	}
	for (set<pair<int, int>>::const_iterator rit = s.cbegin(); rit != s.cend(); rit++)
		swap(map[rit->first - mn][rit->second], map[rit->first][rit->second]);
}

void bfsBySeed(const pair<int, int>& seed, vector<string> &map ) {
	const int dr[] = { 0, -1, 0, 1 };
	const int dc[] = { -1, 0, 1, 0 };
	for (int i = 0; i < 4; i++) {
		if (seed.first + dr[i] < 1 || seed.first + dc[i] > r || seed.second + dc[i] < 0 || seed.second + dc[i] >= c)
			continue;
		if (map[seed.first + dr[i]][seed.second + dc[i]] != 'x')
			continue;
		bfs({ seed.first + dr[i], seed.second + dc[i] }, map);
	}
}

void print(const vector<string>& map) {
	for (int i = r; i >= 1; i--)
		cout << map[i] << std::endl;
}

int main(void) {
	vector<string> map;
	queue<pair<int, int>> q;
	vector<int> height;
	int cnt, pos;

	cin >> r >> c;
	map.resize(r + 1);
	for (int i = r; i >= 1; i--)
		cin >> map[i];
	cin >> cnt;
	height.resize(cnt);
	for (int i = 0; i < cnt; i++)
		cin >> height[i];
	for (int i = 0; i < cnt; i++) {
		if (i % 2 == 0)
			pos = map[height[i]].find('x');
		else
			pos = map[height[i]].rfind('x');
		if (pos == std::string::npos)
			continue;
		map[height[i]][pos] = '.';
		bfsBySeed({ height[i], pos }, map);
	}
	print(map);
}