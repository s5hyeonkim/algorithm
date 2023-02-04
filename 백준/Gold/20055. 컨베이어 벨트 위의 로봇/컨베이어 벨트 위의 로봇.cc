#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int zero_count = 0;
vector <int> vused;
vector <int> v;
queue <int> q_now;
queue <int> q_next;
int N, K;

void first()
{
	int convey_back = v.back();
	v.pop_back();
	//1번에 convey back을 저장해준다.
	v.insert(v.begin()+1, convey_back);

	int used_check = vused.back();
	vused.pop_back();
	vused.insert(vused.begin() + 1, used_check);

	//컨베이어 벨트 이동에 따른 로봇 위치값 증가
	while (!q_now.empty())
	{
		int robot_pos = q_now.front();
		q_now.pop();
		//first step 1++
		robot_pos++;

		q_next.push(robot_pos);
	}
	while (!q_next.empty())
	{
		int robot_move = q_next.front();
		q_next.pop();
		q_now.push(robot_move);
	}
}

void robot_dec()
{
	// 지금 위치에 대하여 내리기
	while (!q_now.empty())
	{
		int robot_pos = q_now.front();
		q_now.pop();

		if (vused[robot_pos] == 1 && robot_pos == N)
		{
			vused.erase(vused.begin() + robot_pos);
			vused.insert(vused.begin() + robot_pos, 0);
			continue;
		}
		q_next.push(robot_pos);
	}
	while (!q_next.empty())
	{
		int robot_move = q_next.front();
		q_next.pop();
		q_now.push(robot_move);
	}

}
void second()
{
	while (!q_now.empty())
	{
		int robot_pos = q_now.front();
		q_now.pop();

		// 다음 자리가 0보다 크고 로봇이 없으면, 다음위치 push
		if (v[robot_pos + 1] && !vused[robot_pos+1])
		{
			int a = v[robot_pos + 1];
			v.erase(v.begin() + robot_pos+1);
			v.insert(v.begin() + robot_pos+ 1, a - 1);

			//vused 지금자리 0 배정
			vused.erase(vused.begin() + robot_pos);
			vused.insert(vused.begin() + robot_pos, 0);

			//vused 다음자리 1 배정
			vused.erase(vused.begin() + robot_pos + 1);
			vused.insert(vused.begin() + robot_pos + 1, 1);

			if (!v[robot_pos + 1]) {
				zero_count++;
				if (zero_count == K) return;
			}
			q_next.push(robot_pos + 1);
		}
		// 원래 자리 다시 푸시
		else
		{
			q_next.push(robot_pos);
		}
	}
	while (!q_next.empty())
	{
		int robot_move = q_next.front();
		q_next.pop();
		q_now.push(robot_move);
	}
}

void third()
{
	if (v[1] != 0)
	{
		int a = v[1];
		v.erase(v.begin() + 1);
		v.insert(v.begin() + 1, a - 1);
		vused.erase(vused.begin() + 1);
		vused.insert(vused.begin() + 1, 1);
		
		q_now.push(1);
		if (v[1] == 0) 
		{
			zero_count++;
			if (zero_count == K) return;
		}
	}
}


int main()
{
	cin >> N >> K;
	v.push_back(-1);
	vused.push_back(-1);

	for (int i = 1; i <= 2 * N; i++)
	{
		int a;
		cin >> a;
		v.push_back(a);
		vused.push_back(0);
	}

	int step = 0;
	int de = 1;
	while (zero_count<K)
	{
		first();
		robot_dec();
		second();
		robot_dec();
		third();
		step++;
		if (zero_count >= K) break;
	}

	cout << step;
}