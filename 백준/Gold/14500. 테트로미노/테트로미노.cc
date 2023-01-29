#include <iostream>

using namespace std;

//테트로노미노는 길이가 4인 칸
int num_arr[501][501] = { 0, };
int used[501][501] = { 0, };

int dr[4] = { 1,0, 0,-1 };
int dc[4] = { 0,1, -1,0 };
int N, M;
int mxscore = 0;
void len4_func(int y,  int x, int num, int score)
{
	if (num == 4)
	{
		if (mxscore < score) mxscore = score;
		return;
	}
	// 중복 방지 위해 방향은 좌우하로만 제한
	for (int i = 0; i < 3; i++)
	{
		int ny = y + dr[i];
		int nx = x + dc[i];
		if (ny <0 || nx <0 || ny>N || nx >M) continue;
		if (used[ny][nx]) continue;
		used[ny][nx] = 1;
		len4_func(ny, nx, num+1, score+num_arr[ny][nx]);
		used[ny][nx] = 0;
	}
}

void octo_func(int y,  int x)
{
	int n = 0;
	int mn = 123123;
	int numsum = num_arr[y][x];
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dr[i];
		int nx = x + dc[i];
		if (ny <0 || nx <0 || ny>N || nx >M) continue;
		n++;
		if (num_arr[ny][nx] < mn) mn = num_arr[ny][nx];
		numsum += num_arr[ny][nx];
	}
	if (n >= 4) numsum -= mn;
	if (numsum > mxscore) mxscore = numsum;
}

int main()
{
	cin >> N >> M;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			cin >> num_arr[r][c];
		}
	}

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			used[r][c] = 1;
			len4_func(r, c, 1, num_arr[r][c]);
			used[r][c] = 0;
			octo_func(r, c);
		}
	}
	cout << mxscore;
}