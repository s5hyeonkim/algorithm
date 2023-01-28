#include <iostream>
#include <vector>
using namespace std;
int N, M;
int sN;
int map[51][51] = { 0, };

struct coord
{
	int r, c;
};
int used[14] = { 0, };

vector<coord> store;
vector<coord> home;

int n = 0;
int dismin_f = 123123;
int dismin_sum = 0;
void dist_min()
{
	dismin_sum = 0;
	for (int i = 0; i < home.size(); i++)
	{
		int dismin_each = 123123;
		int hy = home[i].r;
		int hx = home[i].c;
		for (int j = 0; j < store.size(); j++)
		{
			if (!used[j]) continue;
			int sy = store[j].r;
			int sx = store[j].c;
			int xdis = sx - hx;
			int ydis = sy - hy;
			if (xdis < 0) xdis *= -1;
			if (ydis < 0) ydis *= -1;
			if (dismin_each > xdis + ydis) dismin_each = xdis + ydis;
		}
		dismin_sum += dismin_each;
	}
}

void func_choose(int num)
{
	if (n >= M)
	{
		// 사용하는 치킨가게 정했으니 
		dist_min();
		if (dismin_f > dismin_sum) dismin_f = dismin_sum;
		return;
	}
	// n개 못채우고 store 개수 넘어가면 종료
	if (num >= store.size()) return;
	used[num] = 1;
	n++;
	func_choose(num + 1);
	used[num] = 0;
	n--;
	func_choose(num + 1);
}
int main()
{
	cin >> N >> M;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cin >> map[r][c];
			if (map[r][c] == 1) home.push_back({ r,c });
			if (map[r][c] == 2) store.push_back({ r,c });
		}
	}
	int de = 1;
	func_choose(0);
	cout << dismin_f << endl;

}