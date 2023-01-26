#include <iostream>
#include <math.h>
#include <queue>

using namespace std;
// 격자안 = 얼음양
// 파이어스톰 시전할때마다 단계 L 결정
// 2^L * 2^L 부분 격자로 나누고 모든 격자 시계방향으로 90도 회전
// 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸 얼음 양 --


// 남아있는 얼음의 합
// 얼음 덩어리가 차지하는 칸의 개수
int map[65][65] = { 0, };
int N = 0;
int Q = 0;
int M = 0;

void norm_rotate(int r, int c, int lsize)
{
	int rdople[65][65] = { 0, };
	if (c + lsize > M)
	{
		norm_rotate(r + lsize, 0, lsize);
		return;
	}
	if (r + lsize > M) return;

	for (int i=0; i< lsize; i++)
	{
		for (int j=lsize-1; j>=0; j--)
		{
			rdople[i][lsize-1-j] = map[r+j][c+i];
		}
	}

	for (int i = 0; i < lsize; i++)
	{
		for (int j = 0; j < lsize; j++)
		{
			map[i+r][j+c] = rdople[i][j];
		}
	}
	norm_rotate(r, c + lsize, lsize);
}

int dc[4] = { 0,0,-1,1 };
int dr[4] = { -1,1,0,0 };

struct coord {
	int y, x;
};
queue <coord> mzero;
queue <coord> ice_coord;

int visited[65][65] = { 0, };
int dnum = 0;

void check_coord()
{
	dnum = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visited[i][j] = 0;
			if (map[i][j] == 0) mzero.push({ i,j });
		}
	}


	//4귀퉁이
	while (!mzero.empty())
	{

		coord A = mzero.front();
		mzero.pop();
		// 얼음 근처 애들을 봐야한다.
		// 좌표 4귀퉁이, 4모서리, 격자 내측

		for (int i = 0; i < 4; i++)
		{
			int ny = dr[i] + A.y;
			int nx = dc[i] + A.x;
			if (ny < 0 || nx < 0 || ny >= M || nx >= M) continue;
			if (visited[ny][nx] == 1) continue;
			// 모서리 부분은 근처에 0 있으면 바로 세주자.
			if (ny == 0 || nx == 0 || ny == M-1 || nx == M-1)
			{
				visited[ny][nx] = 1;
				ice_coord.push({ ny,nx });
				continue;
			}
			int n = 0;
			for (int j = 0; j < 4; j++)
			{
				// 인접 4칸 조사
				int nny = dr[j] + ny;
				int nnx = dc[j] + nx;
				if (nny < 0 || nnx < 0 || nny >= M || nnx >= M) continue;
				if (map[nny][nnx] > 0) n++;
			}
			if (n < 3)
			{
				visited[ny][nx] = 1;
				ice_coord.push({ ny,nx });
				continue;
			}
		}
	}
	if (visited[M - 1][0] == 0) ice_coord.push({ M - 1, 0 });
	if (visited[0][0] == 0) ice_coord.push({ 0, 0 });
	if (visited[0][M-1] == 0) ice_coord.push({0,M-1 });
	if (visited[M - 1][M-1] == 0) ice_coord.push({ M - 1, M-1 });

}


void dec_ice()
{
	while (!ice_coord.empty())
	{
		coord A = ice_coord.front();
		ice_coord.pop();
		if (map[A.y][A.x] > 0) map[A.y][A.x]--;
	}
}

int used[65][65] = { 0, };

queue <coord> checking_first;
queue <coord> checking_mass;

int massnum = 0;

void check_mass()
{
	while (!checking_first.empty())
	{
		coord A = checking_first.front();
		checking_first.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = A.y + dr[i];
			int nx = A.x + dc[i];
			if (ny < 0 || nx < 0 || ny >= M || nx >= M) continue;
			if (used[ny][nx] == 1) continue;
			if (map[ny][nx] == 0) continue;
			used[ny][nx] = 1;
			massnum++;
			checking_mass.push({ny, nx});
		}
	}
	while (!checking_mass.empty())
	{
		coord A = checking_mass.front();
		checking_mass.pop();
		checking_first.push({ A.y, A.x });
	}
	if (!checking_first.empty())
	{
		check_mass();
	}
}
int main() {
	cin >> N >> Q;
	M = pow(2, N);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	int de = 1;
	int lstep = 0;
	for (int i = 0; i < Q; i++)
	{
		cin >> lstep;
		int step = pow(2, lstep);
		if (step > 1)
		{
			norm_rotate(0, 0, step);
		}
		check_coord();
		dec_ice();
	}



	int maxnum = 0;
	int result = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			massnum = 1;
			result+= map[i][j];
			if (map[i][j] == 0)
			{
				used[i][j] = 1;
				continue;
			}
			if (used[i][j] == 1) continue;
			used[i][j] = 1;
			checking_first.push({ i,j });
			check_mass();
			if (maxnum < massnum) maxnum = massnum;
		}
	}
	cout << result << endl;
	cout << maxnum << endl;
	return 0;
}