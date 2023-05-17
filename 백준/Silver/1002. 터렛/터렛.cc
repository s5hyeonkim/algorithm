#include <iostream>

using namespace std;
struct Node
{
	int y, x, r;
};
Node arr[1001] = { 0, };
Node arr2[1001] = { 0, };
int result[1001] = { 0, };
int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> arr[i].y >> arr[i].x >> arr[i].r;
		cin >> arr2[i].y >> arr2[i].x >> arr2[i].r;
	}
	for (int i = 0; i < T; i++)
	{
		int val = (arr[i].y - arr2[i].y)*(arr[i].y - arr2[i].y) + (arr[i].x - arr2[i].x)* (arr[i].x - arr2[i].x);
		if (arr[i].y == arr2[i].y && arr[i].x == arr2[i].x && arr[i].r == arr2[i].r)
		{
			result[i] = -1;
			continue;
		}
		else if (arr[i].y == arr2[i].y && arr[i].x == arr2[i].x && arr[i].r != arr2[i].r)
		{
			result[i] = 0;
			continue;
		}
		else if ((max(arr[i].r, arr2[i].r) - min(arr[i].r, arr2[i].r))* (max(arr[i].r, arr2[i].r) - min(arr[i].r, arr2[i].r)) == val)
		{
			result[i] = 1;
			continue;
		}
		else if ((max(arr[i].r, arr2[i].r) - min(arr[i].r, arr2[i].r))* (max(arr[i].r, arr2[i].r) - min(arr[i].r, arr2[i].r)) > val )
		{
			result[i] = 0;
			continue;
		}
		else if ((arr[i].r + arr2[i].r)* (arr[i].r + arr2[i].r) > val)
		{
			result[i] = 2;
			continue;
		}
		else if ((arr[i].r + arr2[i].r)* (arr[i].r + arr2[i].r) == val)
		{
			result[i] = 1;
			continue;
		}

	}
	for (int i = 0; i < T; i++)
	{
		cout << result[i] << endl;
	}
	return 0;
}
