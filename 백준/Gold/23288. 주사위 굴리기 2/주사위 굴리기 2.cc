#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

struct coord
{
	int y, x;
};
int arr[21][21] = { 0, };
unordered_map <string, int> um;
queue <coord> q;
// -> 시계 / <- 반시계
int dc[] = { 1,0,-1,0 };
int dr[] = { 0, 1, 0, -1 };
int used[21][21] = { 0, };
//주사위면수
int N, M, K;
int px, py, dir;
int score = 0;
int mxmove = 0;

void init()
{
	um["top"] = 1;
	um["btm"] = 6;
	um["rgt"] = 3;
	um["lft"] = 4;
	um["frt"] = 5;
	um["bck"] = 2;
	px = 1;
	py = 1;
	dir = 0;
	score = 0;
}
void input()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> arr[i][j];
		}
	}
}

void move_dice(int mode)
{
	px = px + dc[mode];
	py = py + dr[mode];
	int m = 0;
	int empty = 0;
	// 이동방향으로 한칸 굴러간다.
	// 북 남 3 1
	if (mode % 2)
	{
		while (m < mode)
		{
			empty = um["top"];
			um["top"] = um["bck"];
			um["bck"] = um["btm"];
			um["btm"] = um["frt"];
			um["frt"] = empty;
			m++;
		}
	}
	// 동 서 0 2
	else
	{
		mode = mode + 1;
		while (m < mode)
		{
			empty = um["top"];
			um["top"] = um["lft"];
			um["lft"] = um["btm"];
			um["btm"] = um["rgt"];
			um["rgt"] = empty;
			m++;
		}
	}
	// 주사위 아랫면 정수 A 와 주사위 있는 칸 B 비교해서 이동방향 결정
	if (um["btm"] > arr[py][px])
	{
		dir++;
		if (dir > 3) dir = 0;
	}
	else if (um["btm"] < arr[py][px])
	{
		dir--;
		if (dir < 0) dir = 3;
	}
}

queue <coord> qnext;

void bfs(int move)
{
	while (!q.empty())
	{
		coord A = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = A.y + dr[i];
			int nx = A.x + dc[i];
			if (ny <= 0 || nx <= 0 || ny > N || nx > M) continue;
			if (arr[ny][nx] != arr[A.y][A.x]) continue;
			if (used[ny][nx] == 1) continue;
			move++;
			used[ny][nx] = 1;
			qnext.push({ ny,nx });
		}
	}
	while (!qnext.empty())
	{
		coord A = qnext.front();
		q.push({A.y, A.x});
		qnext.pop();
	}
	if (mxmove < move) mxmove = move;
	if (q.empty()) return;
	bfs(move);
}
void cal_score()
{
	// 주사위가 도착한 칸에 대한 점수 획득 =  칸 점수 * 주위 칸수(=지금 칸점수와 같을것) 
	int mnum = 0;
	mxmove = 1;
	used[py][px] = 1;
	q.push({ py, px });
	bfs(1);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			used[i][j] = 0;
		}
	}
	score += arr[py][px] * mxmove;
}

void change_dir()
{
	int ny = py + dr[dir];
	int nx = px + dc[dir];
	if (ny <= 0 || nx <= 0 || ny > N || nx > M) dir += 2;
	if (dir > 3) dir %= 2;
}
void solve()
{
	int k = 0;
	while (k < K)
	{
		move_dice(dir);
		cal_score();
		change_dir();
		k++;
	}
	cout << score << endl;
}

int main()
{
	init();
	input();
	int de = 1;
	solve();
	return 0;
}