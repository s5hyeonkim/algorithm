#include <iostream>

using namespace std;

char arr[50][50] = { 0, };
int mn = 2132312;

int func(int y, int x)
{
	if (y == 1 && x == 2)
	{
		int de = 1;
	}
	int sum = 0;
	int sum1 = 0;
	char a = 'W';
	char b = 'B';
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (sum > mn) break;
			if ((i + j) % 2 == 1)
			{
				if (a == arr[y+i][x+j])
				{
					sum++;
					continue;
				}
			}

			else if ((i + j) % 2 == 0)
			{
				if (a != arr[y+i][x+j])
				{
					sum++;
					continue;
				}
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (sum1 > sum) break;
			if ((i + j) % 2 == 1)
			{
				if (b == arr[y + i][x + j])
				{
					sum1++;
					continue;
				}
			}

			else if ((i + j) % 2 == 0)
			{
				if (b != arr[y + i][x + j])
				{
					sum1++;
					continue;
				}
			}
		}
	}

	if (sum > sum1)
	{
		sum = sum1;
	}
	return sum;
}


int main()
{
	int M, N;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string a;
		cin >> a;
		for (int j = 0; j <M; j++)
		{
			arr[i][j] = a[j];
		}
	}



	for (int i = 0; i < N-7; i++)
	{
		for (int j = 0; j < M-7; j++)
		{
			int re=func(i, j);
			if (mn > re)
			{
				mn = re;
			}

		}
	}
	cout << mn;

}