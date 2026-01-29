#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#define WHITE 0
#define RED 1
#define BLUE 2
using namespace std;

typedef struct Piece {
	pair<int, int> pos;
	int dir;
	Piece() : pos({0, 0}), dir(0) {}
	Piece(const int& r, const int& c, const int& dir) : pos(r, c), dir(dir) {}
	pair<int, int>getNextPos() {
		const int dr[] = { 0, 0, 0, -1, 1 };
		const int dc[] = { 0, 1, -1, 0, 0 };
		return { pos.first + dr[dir], pos.second + dc[dir] };
	}
	void reverse() {
		if (dir % 2)
			dir++;
		else
			dir--;
	}
	void movePos(const pair<int, int> &npos) {
		pos = npos;
	}
};

vector<vector<int>> board;
deque<int> pieces[13][13];
vector<Piece> pieces_pos;
int n, k;
int checkColor(const pair<int, int>& pos) {
	if (pos.first > n || pos.first < 1 || pos.second > n || pos.second < 1)
		return BLUE;
	return board[pos.first][pos.second];
}

void takePieces(deque<int>& temp, const pair<int, int>& pos, const int& target) {
	int i;
	deque<int>& pieces_pos = pieces[pos.first][pos.second];
	//while (!pieces[pos.first][pos.second].empty()) {
	temp.clear();
	for (i = 0; i < pieces_pos.size(); i++) {
		temp.push_back(pieces_pos[i]);
		if (pieces_pos[i] == target)
			break;
	}
	pieces_pos.erase(pieces_pos.begin(), pieces_pos.begin() + i + 1);
}

void putPiecesByColor(deque<int> &temp, const pair<int, int> &npos, const int &color) {
	deque<int>& target = pieces[npos.first][npos.second];
	if (color == WHITE) {
		for (auto it = temp.rbegin(); it != temp.rend(); it++)
			target.push_front(*it);
	}
	else {
		for (auto it = temp.begin(); it != temp.end(); it++)
			target.push_front(*it);
	}
	for (auto it = temp.begin(); it != temp.end(); it++) {
		pieces_pos[*it].movePos(npos);
	}
}

void operate(int &e) {
	deque<int> temp;
	for (int i = 1; i <= k; i++) {
		Piece& p = pieces_pos[i];
		pair<int, int> npos = p.getNextPos();
		if (checkColor(npos) == BLUE) {
			p.reverse();
			npos = p.getNextPos();
		}
		if (checkColor(npos) == BLUE)
			continue;
		takePieces(temp, p.pos, i);
 		putPiecesByColor(temp, npos, checkColor(npos));
		if ((e = (pieces[npos.first][npos.second].size() >= 4)))
			break;
	}
}

void input() {
	cin >> n >> k;
	board.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		board[i].resize(n + 1);
		for (int j = 1; j <= n; j++)
			cin >> board[i][j];
	}
	pieces_pos.resize(k + 1);
	for (int i = 1; i <= k; i++) {
		Piece& p = pieces_pos[i];
		cin >> p.pos.first >> p.pos.second >> p.dir;
		pieces[p.pos.first][p.pos.second].push_back(i);
	}
}

int main(void) {
	int turn = 0;
	int e = 0;
	input();
	while (!e && ++turn <= 1000)
		operate(e);
	if (turn > 1000)
		cout << -1 << '\n';
	else
		cout << turn << "\n";
}