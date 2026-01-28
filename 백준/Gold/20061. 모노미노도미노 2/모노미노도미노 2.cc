#include <iostream>
#include <vector>
#define GYSIZE 6
#define BYSIZE 4
using namespace std;

typedef struct Block {
	vector<pair<int, int>> pos;
	int t;
	Block() {}
	Block(const int& t, const int& r, const int& c) : t(t) {
		pos.push_back({ r, c });
		if (t != 1) {
			pos.resize(2);
			changePos(pos[0]);
		}
	}
	void changePos(const pair<int, int> &bpos) {
		pos[0] = bpos;
		if (!hasNextBlock())
			return;
		if (t == 2)
			pos[1] = { bpos.first, bpos.second + 1 };
		else
			pos[1] = { bpos.first + 1, bpos.second };
	}
	pair<int, int> getNextBlock() const {
		return pos[1];
	}
	pair<int, int> getFirstBlock() const {
		return pos[0];
	}
	bool hasNextBlock() const {
		return pos.size() > 1;
	}
}	Block;

typedef struct Board {
	vector<vector<int>> board;
	int is_green;
	pair<int, int> dir;
	Board(const int& is_green) : is_green(is_green) {
		if (!is_green) {
			board.resize(BYSIZE + 1);
			for (int i = 0; i <= BYSIZE; i++)
				board[i].resize(GYSIZE, 0);
			dir = { 0, 1 };
		}
		else {
			board.resize(GYSIZE);
			for (int i = 0; i < GYSIZE; i++)
				board[i].resize(BYSIZE + 1, 0);
			dir = { 1, 0 };
		}
	}
	void pickPosition(Block& b) {
		if (is_green)
			b.changePos({ 0, b.getFirstBlock().second });
		else
			b.changePos({ b.getFirstBlock().first, 0 });
	}
	void putBlock(Block& b) {
		putBlockByPos(b.getFirstBlock());
		if (b.hasNextBlock())
			putBlockByPos(b.getNextBlock());
	}
	void removeBlockByPos(const pair<int, int> &pos) {
		if (is_green)
			board[pos.first][BYSIZE]--;
		else
			board[BYSIZE][pos.second]--;
		board[pos.first][pos.second]--;
	}
	void putBlockByPos(const pair<int, int>& pos) {
		if (is_green)
			board[pos.first][BYSIZE]++;
		else
			board[BYSIZE][pos.second]++;
		board[pos.first][pos.second]++;
	}
	void removeBlock(Block& b) {
		removeBlockByPos(b.getFirstBlock());
		if (b.hasNextBlock())
			removeBlockByPos(b.getNextBlock());
	}
	bool canPutTheBlock(const Block& b) {
		pair<int, int> pos = b.getFirstBlock();
		if (!canPutTheBlockByPos(pos))
			return false;
		if (b.hasNextBlock()) {
			pos = b.getNextBlock();
			return canPutTheBlockByPos(pos);
		}
		return true;
	}
	bool canPutTheBlockByPos(const pair<int, int>& pos) {
		if (pos.first < 0 || pos.second < 0)
			return false;
		if (is_green && (pos.first >= GYSIZE || pos.second >= BYSIZE))
			return false;
		if (!is_green && (pos.first >= BYSIZE || pos.second >= GYSIZE))
			return false;
		return board[pos.first][pos.second] == 0;
	}
	void moveBlock(Block& b) {
		pair<int, int> pos = b.getFirstBlock();
		while (canPutTheBlock(b)) {
			pos = b.getFirstBlock();
			b.changePos({ pos.first + dir.first, pos.second + dir.second });
		}
		b.changePos(pos);
		putBlock(b);
	}
	void checkSpeicalByPos(const pair<int, int>& pos, vector<int> &idx) {
		if (is_green && pos.first <= 1) {
			idx[pos.first] = 1;
		}
		else if (!is_green && pos.second <= 1) {
			idx[pos.second] = 1;
		}
	}
	void checkSpecial() {
		vector<int> idx(2, 0);
		if (is_green) {
			idx[1] = board[1][BYSIZE];
			idx[0] = board[0][BYSIZE];
		}
		else {
			idx[0] = board[BYSIZE][0];
			idx[1] = board[BYSIZE][1];
		}
		if (idx[0] && idx[1])
			swapByDirection(4);
		if (idx[0] || idx[1])
			swapByDirection(5);
	}
	bool checkLineClearByPos(const pair<int, int>& pos) {
		if (is_green) {
			if (board[pos.first][BYSIZE] == BYSIZE) {
				swapByDirection(pos.first);
				return true;
			}
			return false;
		}
		if (board[BYSIZE][pos.second] == BYSIZE) {
			swapByDirection(pos.second);
			return true;
		}
		return false;
	}
	void checkLineClear(const Block& b, int& le) {
		pair<int, int> pos = b.getFirstBlock();
		le = checkLineClearByPos(pos);
		if (b.hasNextBlock()) {
			pos = b.getNextBlock();
			le += checkLineClearByPos(pos);
		}
	}
	void swapByDirection(const int &id) {
		if (is_green) {
			for (int c = 0; c <= BYSIZE; c++) {
				for (int r = id; r >= 0; r--) {
					if (r)
						swap(board[r][c], board[r - 1][c]);
					else
						board[r][c] = 0;
				}
			}
		}
		else {
			for (int r = 0; r <= BYSIZE; r++) {
				for (int c = id; c >= 0; c--) {
					if (c)
						swap(board[r][c], board[r][c - 1]);
					else
						board[r][c] = 0;
				}
			}
		}
	}
	void operateLineClear(const Block& b, int &le) {
		checkLineClear(b, le);
	}
	void operateSpecial() {
		checkSpecial();
	}
	int operate(const Block& b) {
		Block beg = b;
		int cnt;

		pickPosition(beg);
		moveBlock(beg);
		operateLineClear(beg, cnt);
		operateSpecial();
		return cnt;
	}
	int getTiles() const {
		int cnt = 0;
		if (is_green) {
			for (int i = 0; i < GYSIZE; i++)
				cnt += board[i][BYSIZE];
		}
		else {
			for (int i = 0; i < GYSIZE; i++)
				cnt += board[BYSIZE][i];
		}
		return cnt;
	}
	void print() const {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				cout << board[i][j] << " ";
			}
			cout << '\n';
		}
	}
}	Board;

class Tetrodomino {
	private: 
		Board board_b, board_g;
		vector<Block> blocks;
		void input() {
			int n, t, r, c;
			
			cin >> n;
			blocks.resize(n);
			for (int i = 0; i < n; i++) {
				cin >> t >> r >> c;
				blocks[i] = Block(t, r, c);
			}
		}
		void operate() {
			int result = 0;
			for (int i = 0; i < blocks.size(); i++) {
				result += board_b.operate(blocks[i]);
				result += board_g.operate(blocks[i]);
				//cout << "\nB: " << "\n";
				//board_b.print();
				//cout << "\nG: " << "\n";
				//board_g.print();
			}
			cout << result << "\n" << board_b.getTiles() + board_g.getTiles()  << '\n';
		}
	public: 
		Tetrodomino(): board_b(Board(0)), board_g(Board(1)) {
			input();
			operate();
		}
		~Tetrodomino() {}
};

int main(void) {
	Tetrodomino t;
}