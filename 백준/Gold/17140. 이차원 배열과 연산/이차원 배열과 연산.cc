#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int N, Nnum;
};

struct cmp
{
	bool operator()(Node A, Node B)
	{
		if (A.Nnum > B.Nnum) return true;
		else if (A.Nnum < B.Nnum) return false;
		if (A.N > B.N) return true;
		else if (A.N < B.N) return false;
		return false;
	}
};


priority_queue <Node, vector<Node>, cmp > align_arr;
queue <int> arr_num;

int arr[101][101] = { 0, };
// R 연산 행>=열 : 
// C 연산 행 < 열 : 

// 수, 등장횟수 세트로 행 또는 열에 넣어준다. 
// 세트 order: 등장횟수 오름차순, 숫자 오름차순

int used[101] = { 0, };
bool flag = 1;

int row = 0;
int col = 0;

void numbering()
{
	//flag 0 이면 col이 더 큰 것.
	if (row < col) flag = 0;
	int maxnum = 0;

	for (int i = 1; i <= 101; i++)
	{
		for (int j = 1; j<=101; j++)
		{
			//행 탐색
			if (flag)
			{
				if (i > row || j > col) break;
				if (arr[i][j]==0) continue;
				if (used[arr[i][j]]) used[arr[i][j]]++;
				else
				{
					used[arr[i][j]] = 1;
					arr_num.push(arr[i][j]);
				}
				arr[i][j] = 0;
			}
			//열탐색
			else
			{
				if (j > row || i > col) break;
				if (arr[j][i] == 0) continue;
				if (used[arr[j][i]]) used[arr[j][i]]++;
				else
				{
					used[arr[j][i]] = 1;
					arr_num.push(arr[j][i]);
				}
				arr[j][i] = 0;
			}
		}

		// 검색을 하고 숫자들이 정해지면 정리해주자.
		while (!arr_num.empty())
		{
			int arrnum = arr_num.front();
			arr_num.pop();
			// 수와 등장 횟수 push
			align_arr.push({ arrnum, used[arrnum] });
			used[arrnum] = 0;
		}
		int num = 1;
		while (!align_arr.empty())
		{
			Node arrset = align_arr.top();
			align_arr.pop();
			if (flag)
			{
				arr[i][num] = arrset.N;
				arr[i][num + 1] = arrset.Nnum;
			}
			else
			{
				arr[num][i] = arrset.N;
				arr[num + 1][i] = arrset.Nnum;
			}
			num += 2;
		}
		//최대 차지하는 칸수를 저장해주자.
		if (maxnum < num - 1) maxnum = num - 1;
	}
	// 행 연산중에 col이 차지하는 max 칸
	if (flag) col = maxnum;
	// 열 연산중 row가 차지하는 max 칸
	else row = maxnum;
}



int main()
{
	int r, c, k;
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			cin >> arr[i][j];
		}
	}

	int t = 0;
	//flag==1 이면 row >= col
	flag = 1;
	row = 3;
	col = 3;
	int de = 1;
	while (t <= 100)
	{
		flag = 1;
		if (arr[r][c] == k) break;
		numbering();
		t++;
	}
	
	if (t >= 101) t = -1;
	cout << t << endl;
	
	return 0;
}