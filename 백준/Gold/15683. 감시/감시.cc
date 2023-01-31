#include <iostream>
#include <vector>
using namespace std;

struct coord
{
	int y, x;
};

vector <coord> cctv_pos;


int dc[] = { 1,0,-1,0,1,0 };
int dr[] = { 0,1,0,-1,0,1 };
int map[8][8] = { 0, };
int c_region[8][8] = { 0, };
int c_setting[8][8] = { 0, };
//방향 1, 3, 4 -> 경우의수 4 / 방향 2 -> 2 / 방향 5 -> 1

int dirnum[6] = { 0,1,2,2,3,4 };
// 경우의수 0123 우하좌상(기준으로 시계방향) 

int used[8] = { 0, }; 
int N, M;


void cctv_colored(int cy, int cx, int dnum)
{
	int ny = dr[dnum] + cy;
	int nx = dc[dnum] + cx;
	if (ny < 0 || nx < 0 || ny >= N || nx >= M) return;
	if (map[ny][nx] == 6) return;
	c_region[ny][nx] = 1;
	cctv_colored(ny, nx, dnum);
}
void cctv_check()
{
	for (int i = 0; i < cctv_pos.size(); i++)
	{
		int cy = cctv_pos[i].y;
		int cx = cctv_pos[i].x;
		int cctvnum = map[cy][cx];
		//방향 개수
		if (cctvnum != 2)
		{
			for (int dir = used[i]; dir < dirnum[cctvnum] + used[i]; dir++)
			{
				cctv_colored(cy, cx, dir);
			}
		}
		else
		{
			//cctvnum=2일때 
			if (used[i] == 0)
			{
				cctv_colored(cy, cx, 0);
				cctv_colored(cy, cx, 2);
			}
			else if (used[i] == 1)
			{
				cctv_colored(cy, cx, 1);
				cctv_colored(cy, cx, 3);
			}
		}
	}
}

int mn = 123123;
void func(int num)
{
	int sum = 0;
	if (num >= cctv_pos.size())
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				c_region[i][j] = c_setting[i][j];
			}
		}
		cctv_check();
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (c_region[i][j] == 0) sum += 1;
				if (sum >= mn) return;
			}
		}
		if (sum < mn) mn = sum;
		return;
	}
	//num 번째 cctv 종류
	int cy = cctv_pos[num].y;
	int cx = cctv_pos[num].x;
	int cctvnum = map[cy][cx];
	// cctv 방향 최대 경우의 수는 4
	for (int j = 0; j < 4; j++)
	{
		if ((cctvnum == 5) && j > 0) continue;
		if ((cctvnum == 2) && j > 1)continue;
		//종류에 따라 방향 배정
		used[num] = j;
		func(num + 1);
	}
}


int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			c_setting[i][j] = map[i][j];
			if (map[i][j] > 0) 
			{
				if(map[i][j] < 6) cctv_pos.push_back({ i,j });
			}
		}
	}
	func(0);
	cout << mn << endl;
	return 0;
}