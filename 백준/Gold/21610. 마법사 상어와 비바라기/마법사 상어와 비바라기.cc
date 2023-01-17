#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int dir, dis;
};
struct coord
{
	int y, x;
};
queue <coord> cloud_pos;
queue <coord> cloud_npos;

int N, M;
int map[51][51] = { 0, };
int post_cloud[51][51] = { 0, };
//구름 이동 
int dr_cloud[9] = {0,0,-1,-1,-1,0,1,1,1};
int dc_cloud[9] = {0,-1,-1,0,1,1,1,0,-1};

//복사 방향
int dr_copy[4] = { -1,-1,1,1 };
int dc_copy[4] = { -1,1,-1,1 };

void cloud_move(int ord, int dis)
{
	while (!cloud_pos.empty())
	{
		coord A = cloud_pos.front();
		cloud_pos.pop();
		int ny = A.y+dr_cloud[ord] * dis;
		int nx = A.x+dc_cloud[ord] * dis;
		if (ny < 0) ny += N * 100;
		if (nx < 0) nx += N * 100;
		if (ny > N) ny = ny %N;
		if (nx > N) nx = nx %N;
		if (ny == 0) ny = N;
		if (nx == 0) nx = N;
		cloud_npos.push({ ny,nx });
		map[ny][nx]++;
		post_cloud[ny][nx]++;
	}
}

void hydro_copy()
{
	while (!cloud_npos.empty())
	{
		coord A = cloud_npos.front();
		cloud_npos.pop();
		int n = 0;
		for (int i = 0; i < 4; i++)
		{
			int ny = A.y + dr_copy[i];
			int nx = A.x + dc_copy[i];
			if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
			if (map[ny][nx] <1) continue;
			n++;
		}
		map[A.y][A.x] += n;
	}
}

void cloud_enchant()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (post_cloud[i][j] == 1)
			{
				post_cloud[i][j] = 0;
				continue;
			}
			if (map[i][j] >= 2)
			{
				map[i][j] -= 2;
				cloud_pos.push({ i,j });
			}
		}
	}
}

int main()
{

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> map[i][j];
		}
	}
	Node info_cloud[101] = { 0, };
	for (int i = 0; i < M; i++)
	{
		cin >> info_cloud[i].dir >> info_cloud[i].dis;
	}

	//비바라기 시전
	cloud_pos.push({ N,1 });
	cloud_pos.push({ N,2 });
	cloud_pos.push({ N-1,1 });
	cloud_pos.push({ N-1,2 });

	for (int i = 0; i < M; i++)
	{
		// 구름의 이동, 1 증가, 사라진다
		cloud_move(info_cloud[i].dir, info_cloud[i].dis);
		// 복사 마법
		hydro_copy();
		// 구름 생성
		cloud_enchant();
		/*
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		*/
	}
	int result = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			result += map[i][j];
		}
	}

	cout << result;
	return 0;

}