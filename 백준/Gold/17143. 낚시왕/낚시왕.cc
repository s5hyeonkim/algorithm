#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct Shark {
	int size, speed, dir;
	pair<int, int> pos;
	Shark():size(0), speed(0), dir(0), pos({0, 0}) {}
	Shark(const int& size, const int& speed, const pair<int, int>& pos) : pos(pos), size(size), speed(speed), dir(dir) {}
};

class Fishing {
	private:
		struct cmp {
			bool operator()(const Shark& a, const Shark& b) {
				return a.size > b.size;
			}
		};
		vector<vector<int>> map;
		vector<Shark> sharks;
		vector<int> is_dead;
		int r, c, shark_num, result;
		const int dr[5] = { 0, -1, 1, 0, 0 };
		const int dc[5] = { 0, 0, 0, 1, -1 };

		void set() {
			result = 0;
			// 상어 위치 기록
			map.resize(r + 1);
			for (int i = 1; i <= r; i++)
				map[i].resize(c + 1, -1);
			sort(sharks.begin(), sharks.end(), cmp());
			is_dead.resize(shark_num, 0);
			for (int i = 0; i < sharks.size(); i++) {
				map[sharks[i].pos.first][sharks[i].pos.second] = i;
			}
		}
		
		void input() {
			Shark s;
			cin >> r >> c >> shark_num;
			sharks.resize(shark_num);
			for (int i = 0; i < shark_num; i++) {
				cin >> s.pos.first >> s.pos.second >> s.speed >> s.dir >> s.size;
				sharks[i] = s;
			}
		}

		void catchShark(const int &col) {
			pair<int, int> pos;
			int to_catch_idx;
			for (int i = 1; i <= r; i++) {
				if ((to_catch_idx = map[i][col]) != -1) {
					to_catch_idx = map[i][col];
					break;
				}
			}
			if (to_catch_idx == -1)
				return;
			pos = sharks[to_catch_idx].pos;
			map[pos.first][pos.second] = -1;
			is_dead[to_catch_idx] = 1;
			result += sharks[to_catch_idx].size;
		}

		void setNextPos(Shark &shark) {
			int dist, cur_dist;
			if (shark.dir >= 3) {
				dist = shark.speed % (2 * c - 2);
			}
			else
				dist = shark.speed % (2 * r - 2);
			while (dist) {
				if (shark.dir == 3) {
					cur_dist = min(c - shark.pos.second, dist);
					shark.pos.second += cur_dist;
				}
				else if (shark.dir == 4) {
					cur_dist = min(shark.pos.second - 1, dist);
					shark.pos.second -= cur_dist;
				}
				else if (shark.dir == 1) {
					cur_dist = min(shark.pos.first - 1, dist);
					shark.pos.first -= cur_dist;
				}
				else {
					cur_dist = min(r - shark.pos.first, dist);
					shark.pos.first += cur_dist;
				}
				if (!(dist -= cur_dist))
					break;
				if (shark.dir % 2)
					shark.dir++;
				else
					shark.dir--;
			}
		}

		void eatShark() {
			Shark cur;

			for (int i = 0; i < sharks.size(); i++) {
				if (is_dead[i])
					continue;
				cur = sharks[i];
				if (map[cur.pos.first][cur.pos.second] != -1) {
					is_dead[i] = 1;
					continue;
				}
				map[cur.pos.first][cur.pos.second] = i;
			}
		}

		void moveShark() {

			for (int i = 0; i < sharks.size(); i++) {
				Shark &cur = sharks[i];
				if (is_dead[i])
					continue;
				map[cur.pos.first][cur.pos.second] = -1;
				setNextPos(cur);
			}
		}
		void print() {
			Shark cur;
			int size = sharks.size();
			for (int i = 0; i < sharks.size(); i++) {
				cur = sharks[i];
				cout << cur.size << " " << cur.pos.first << " " << cur.pos.second << " " << cur.speed << "\n";
			}
		}
		void operate() {
			for (int fisher_pos = 1; fisher_pos <= c; fisher_pos++) {
				catchShark(fisher_pos);
				moveShark();
				eatShark();
				//print();
			}
			cout << result << '\n';
		}
	public : 
	Fishing() {
		input();
		set();
		operate();
	}
	~Fishing() {}

};

int main(void) {
	Fishing fisher;
}