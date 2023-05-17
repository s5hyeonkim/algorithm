#include <iostream>

using namespace std;

int N, L;
int result = 0;
void func(int now)
{
	if (now > 100) return;
	if (now % 2 == 0)
	{
		int val = now/2;
		if (N / now - val + 1 < 0) return;
		if ((N - val) % now == 0)
		{
			
			for (int i = 0; i < now; i++)
			{
				cout << N / now - val+1<< " ";
				val--;
			}
			result = now;
		}
		else
		{
			func(now + 1);
		}
	}
	else
	{
		if (N % now == 0)
		{
			int val = now / 2 * (-1);
			if (N / now + val < 0) return;
			for (int i = 0; i < now; i++)
			{
				cout << N / now + val << " ";
				val++;
			}
			result = now;
		}
		else
		{
			func(now + 1);
		}
	}
}

int main()
{
	cin >> N >> L;
	int de = 1;
	func(L);
	if (result == 0)
	{
		cout << -1;
	}
	return 0;
}