#include <iostream>

using namespace std;

// 남은 N일 동안 최대한 많은 상담을 하려고 한다.
// 하루에 하나씩 서로 다른 사람의 상담을 잡았다.
int N;
int T[16] = { 0, };
int P[16] = { 0, };
int used[16] = { 0, };
int max_money = 0;

void init()
{
	max_money = 0;
}

void input()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> T[i] >> P[i];
	}
}

int cal()
{
	int flag = 0;
	for (int i = 1; i <= N; i++)
	{
		if (used[i])
		{
			// 당일 고려
			if (i + T[i] > N+1) flag = 1;
			if (flag) break;
			for (int j = i + 1; j < i + T[i]; j++)
			{
				if (used[j])
				{
					flag = 1;
					break;
				}
			}
		}
	}
	return flag;
}

void func(int num, int give_money)
{
	if (num > N)
	{
		int flag = cal();
		if (!flag && give_money > max_money)
		{
			max_money = give_money;
		}
		return;
	}

	used[num] = 0;
	func(num + 1, give_money);
	used[num] = 1;
	func(num + 1, give_money + P[num]);
}
void solve()
{
	func(1, 0);
}

int main()
{
	int de = 1;
	init();
	input();
	solve();
	cout << max_money << endl;
	return 0;
}