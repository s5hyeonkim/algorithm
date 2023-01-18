#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int r, c, m, s, d;
};
queue <Node> ord_wizard;

int N, M, K;
int dr[] = { -1,-1,0,1,1,1,0,-1 };
int dc[] = { 0,1,1,1,0,-1,-1,-1 };

struct info
{
	int m, s, d, num;
};

info map[51][51] = { 0, };

void fireball_move()
{
	while (!ord_wizard.empty())
	{
		Node A = ord_wizard.front();
		ord_wizard.pop();
		int ny = A.r + A.s * dr[A.d];
		int nx = A.c + A.s * dc[A.d];
		if (ny < 0) ny += N * 250;
		if (nx < 0) nx += N * 250;
		if (ny> N) ny %= N;
		if (nx> N) nx %= N;
		if (ny==0) ny = N;
		if (nx==0) nx = N;
		map[ny][nx].num += 1;
		map[ny][nx].m+=A.m;
		map[ny][nx].s += A.s;
		if (map[ny][nx].num == 1) map[ny][nx].d = A.d;
		else
		{
			if (map[ny][nx].d % 2 != A.d % 2) map[ny][nx].d = -1;
		}
	}
}

void fireball_create()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j].num > 1)
			{
				if (map[i][j].m / 5 == 0) map[i][j].d = -2;
				// 방향 기준 홀수
				if (map[i][j].d == -1)
				{
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,1 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,3 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,5 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,7 });
				}
				else if (map[i][j].d>=0)
				{
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,0 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,2 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,4 });
					ord_wizard.push({ i,j,map[i][j].m / 5, map[i][j].s / map[i][j].num,6 });
				}
			}
			else if (map[i][j].num == 1)
			{
				ord_wizard.push({ i,j,map[i][j].m, map[i][j].s, map[i][j].d});
			}
			map[i][j].d = 0;
			map[i][j].num = 0;
			map[i][j].m = 0;
			map[i][j].s = 0;
		}
	}
}
int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		ord_wizard.push({ r,c,m,s,d });
	}

	for (int i = 0; i < K; i++)
	{
		fireball_move();
		fireball_create();
	}
	int result = 0;
	while (!ord_wizard.empty())
	{
		Node A = ord_wizard.front();
		ord_wizard.pop();
		result += A.m;
	}

	cout << result;
	return 0;
}