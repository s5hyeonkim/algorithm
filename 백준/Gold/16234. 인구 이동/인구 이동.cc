#include <iostream>
#include <queue>
using namespace std;


int pop[51][51] = { 0, };
int pop_comp[51][51] = { 0, };
int popsum = 0;
int memcount = 0;

//개수, 하한, 상한
int N, L, H;
struct coord {
	int r, c;
};
queue <coord> now_pop;
queue <coord> next_pop;
queue <coord> dist_pop;

int dc[] = { 0,0,-1,1 };
int dr[] = { -1,1, 0,0 };
int used[51][51] = { 0, };

void bfs()
{
	while (!now_pop.empty())
	{
		coord now = now_pop.front();
		now_pop.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = now.r + dr[i];
			int nx = now.c + dc[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (used[ny][nx]) continue;
			int val = pop[now.r][now.c] - pop[ny][nx];
			if (val < 0) val *= -1;
			if (val > H || val < L) continue;
			used[ny][nx] = 1;
			memcount++;
			popsum += pop[ny][nx];
			next_pop.push({ ny,nx });
		}
	}
	while (!next_pop.empty()) 
	{
		coord next = next_pop.front();
		next_pop.pop();
		dist_pop.push({ next.r, next.c });
		now_pop.push({ next.r, next.c });
	}
	if (now_pop.empty()) return;
	bfs();
}


int main()
{
	cin >> N >> L >> H;
	
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cin >> pop[r][c];
			pop_comp[r][c] = pop[r][c];
		}
	}
	int count = 0;
	int flag = 0;
	int daynum = 0;
	int de = 1;
	while (!flag)
	{
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				popsum = pop[r][c];
				memcount = 1;
				if (used[r][c]) continue;
				used[r][c] = 1;
				now_pop.push({ r,c });
				dist_pop.push({ r,c });
				bfs();
				int val = popsum / memcount;
				while (!dist_pop.empty())
				{
					coord dist = dist_pop.front();
					dist_pop.pop();
					pop_comp[dist.r][dist.c] = val;
				}

			}
		}
		//reset 및 비교
		flag = 1;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				used[r][c] = 0;
				if (pop_comp[r][c] != pop[r][c]) flag = 0;
				pop[r][c] = pop_comp[r][c];
			}
		}
		daynum++;
	}
	cout << daynum - 1;
}