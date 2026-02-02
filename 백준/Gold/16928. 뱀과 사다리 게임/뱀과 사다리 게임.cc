#include <iostream>
#include <vector>
using namespace std;

int dp[101];
void dfs(const vector<int>& board, const int& cur, const int &cnt) {
	int next, result; 
	if (cur == 100)
		return;
	result = 1000000;
	for (int i = 1; i <= 6; i++) {
		next = cur + i;
		if (next > 100)
			break;
		if (dp[next] && dp[next] <= cnt)
			continue;
		dp[next] = cnt;
		while (board[next] != next) {
			next = board[next];
		}
		if (next != cur + i && dp[next] && dp[next] <= cnt)
			continue;
		dp[next] = cnt;
		dfs(board, next, cnt + 1);
	}
}

int main(void) {
	vector<int> board(101);
	int n, m, cur, next;
	cin >> n >> m;
	for (int i = 1; i <= 100; i++)
		board[i] = i;
	for (int i = 0; i < n + m; i++) {
		cin >> cur >> next;
		board[cur] = next;
	}
	dfs(board, 1, 1);
	cout << dp[100] << "\n";
}