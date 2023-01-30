#include <iostream>

using namespace std;

int N;
int arr_org[21][21] = { 0, };
int arr[21][21] = { 0, };

int dc[] = { -1,1,0,0 };
int dr[] = { 0,0,1,-1 };

// 0: 좌<- 1:우 2:하 3:상
int used[5] = { 0, };


void limit_move(int y, int x, int unum)
{
	int ny = y + dr[unum];
	int nx = x + dc[unum];
	if (ny >= N || nx >= N || ny < 0 || nx < 0) return;

	if (arr[ny][nx] == 0)
	{
		arr[ny][nx] = arr[y][x];
		arr[y][x] = 0;
	}
	else return;
	limit_move(ny, nx, unum);
}

void limit_go(int unum)
{
	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++){

			if (unum == 0)
			{
				//<-로 합쳐준다.
				limit_move(i, j, unum);
			}
			else if (unum == 1)
			{
				//->로 합쳐준다.
				limit_move(i, N - 1 - j, unum);
			}
			else if (unum == 2)
			{
				//상 -> 하로 합쳐준다 아래
				limit_move(N - 1 - j, i, unum);
			}
			else if (unum == 3)
			{
				//하 -> 상로 합쳐준다 위
				limit_move(j, i, unum);
			}

		}
	}
}
void move_array(int unum)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j == N - 1) continue;
			if (unum == 0)
			{
				// <-로 합쳐준다.
				if (arr[i][j] == arr[i][j + 1])
				{
					arr[i][j] *=2;
					arr[i][j + 1] = 0;
				}
			}
			else if (unum == 1)
			{
				// ->로 합쳐준다.
				if (arr[i][N - 1 - j] == arr[i][N - 2 - j])
				{
					arr[i][N - 1 - j] *= 2;
					arr[i][N - 2 - j] = 0;
				}
			}
			else if (unum == 2)
			{
				//상 -> 하로 합쳐준다
				if (arr[N - 2 - j][i] == arr[N - 1 - j][i])
				{
					arr[N - 1 - j][i] *= 2;
					arr[N - 2 - j][i] = 0;
				}
			}
			else if (unum == 3)
			{
				//하 -> 상로 합쳐준다
				if (arr[j][i] == arr[j + 1][i])
				{
					arr[j][i] *= 2;
					arr[j + 1][i] = 0;
				}				
			}

		}
	}
	limit_go(unum);
}

int mx = 0;

void choose_dir(int num)
{
	if (num >= 5)
	{
		for (int i = 0; i < 5; i++)
		{
			limit_go(used[i]);
			move_array(used[i]);
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mx < arr[i][j])mx = arr[i][j];
				arr[i][j] = arr_org[i][j];
			}
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		used[num] = i;
		choose_dir(num + 1);
	}
}

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr_org[i][j];
			arr[i][j] = arr_org[i][j];
		}
	}
	int de = 1;
	choose_dir(0);

	cout << mx << endl;
	return 0;
}                    