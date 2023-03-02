#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<string, int> um;
int N, M, K;
int dr[] = { 0,0,0,-1,1 };
int dc[] = { 0,1,-1,0,0 };
int py, px;
int arr[21][21] = { 0, };

void init()
{
	um["top"] = 0;
	um["btm"] = 0;
	um["rgt"] = 0;
	um["lft"] = 0;
	um["frt"] = 0;
	um["bck"] = 0;
}
void input()
{
	cin >> N >> M >> px >> py >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
		}
	}
}

void dice_change(int d)
{
	int empty = 0;
	// 동서남북 1234
	if (d < 3) // 동서
	{
		int m = d % 2; // 동: 1, 서: 0
		// 동 1번 서 3번 반복
		while (m <= d)
		{
			empty = um["top"];
			um["top"] = um["lft"];
			um["lft"] = um["btm"];
			um["btm"] = um["rgt"];
			um["rgt"] = empty;
			m++;
		}
	}
	else
	{
		int m = d % 2+1; // 북: 2, 남: 1
		// 북 1번 남 3번 반복
		while (m < d)
		{
			empty = um["top"];
			um["top"] = um["frt"];
			um["frt"] = um["btm"];
			um["btm"] = um["bck"];
			um["bck"] = empty;
			m++;
		}
	}
}

void dice_move(int dir)
{
	//y는 횡 x는 종
	int ny = py + dc[dir];
	int nx = px + dr[dir];
	// 바깥 향할시 명령 무시
	if (ny < 0 || nx < 0 || ny >= M || nx >= N) return;
	py = ny;
	px = nx;
	dice_change(dir);
	cout << um["top"] << endl;
	// 이동한 칸 !=0 -> 주사위 바닥면 = 칸 && 칸=0;
	if (arr[px][py] != 0)
	{
		um["btm"] = arr[px][py];
		arr[px][py] = 0;
	}
	// 이동할 칸 0이면 칸 = 주사위 바닥면
	else arr[px][py] = um["btm"];

}
void solve()
{
	int ord = 0;
	for (int i = 0; i < K; i++)
	{
		cin >> ord;
		dice_move(ord);
	}
}
int main()
{
	init();
	input();
	int de = 1;
	solve();
	return 0;
}