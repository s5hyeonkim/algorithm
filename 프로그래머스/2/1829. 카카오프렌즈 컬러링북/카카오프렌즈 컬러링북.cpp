#include <vector>
#include <queue>
using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    vector<vector<int>> used(picture.size(), vector<int>(picture[0].size(), 0));
    vector<int>         answer(2, 0);
    queue<pair<int,int>> q;
    int                 cnt;
    int                 dr[] = {-1, 0, 1, 0};
    int                 dc[] = {0, 1, 0, -1};
    pair<int, int>      cur;


    for (int i = 0; i < picture.size(); i++)
    {
        for (int j = 0; j < picture[i].size(); j++)
        {
            if (used[i][j] || !picture[i][j])
                continue ;
            answer[0]++;
            used[i][j] = 1;
            q.push({i, j});
            cnt = 1;
            while (!q.empty())
            {
                cur = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    if (cur.first + dr[k] < 0 || cur.second + dc[k] < 0 || cur.first + dr[k] >= picture.size() || cur.second + dc[k] >= picture[0].size())
                        continue ;
                    if (used[cur.first + dr[k]][cur.second + dc[k]] || picture[cur.first][cur.second] != picture[cur.first + dr[k]][cur.second + dc[k]])
                        continue ;
                    used[cur.first + dr[k]][cur.second + dc[k]] = 1;
                    cnt++;
                    q.push({cur.first + dr[k], cur.second + dc[k]});
                }
            }
            answer[1] = max(answer[1], cnt);
        }
    }
    return answer;
}