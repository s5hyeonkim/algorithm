#include <string>
#include <vector>
#include <queue>
using namespace std;

bool    checkRemovable(pair<int, int> &cur, vector<string> &storage)
{
    pair<int, int>  next;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
    {
        next.first = dr[i] + cur.first;
        next.second = dc[i] + cur.second;
        if (next.first < 0 || next.second < 0 || next.first >= storage.size() || next.second >= storage[0].size())
            return true;
        if (storage[next.first][next.second] == 'q')
            return true;
    }
    return false;
}

void    bfs(pair<int, int> &cur, vector<string> &storage)
{
    queue<pair<int, int>>   q;
    pair<int, int>          next;
    int                     dr[] = {-1, 0, 1, 0};
    int                     dc[] = {0, 1, 0, -1};

    q.push(cur);
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            next.first = dr[i] + cur.first;
            next.second = dc[i] + cur.second;
            if (next.first < 0 || next.second < 0 || next.first >= storage.size() || next.second >= storage[0].size())
                continue ;
            if (storage[next.first][next.second] == '.')
            {
                storage[next.first][next.second] = 'q';
                q.push(next);
            }
        }
    }
}

int solution(vector<string> storage, vector<string> requests) {
    queue<pair<int, int>> q[26], q2;
    pair<int, int>      cur;
    int                 answer;
    size_t              size;

    answer = storage.size() * storage[0].size();
    for (int i = 0; i < storage.size(); i++)
    {
        for (int j = 0; j < storage[0].size(); j++)
            q[storage[i][j] - 'A'].push({i, j});
    }
    for (int i = 0; i < requests.size(); i++)
    {
        size = q[requests[i][0] - 'A'].size();
        while (size--)
        {
            cur = q[requests[i][0] - 'A'].front();
            q[requests[i][0] - 'A'].pop();
            answer--;
            if (checkRemovable(cur, storage))
                q2.push({cur});
            else if (requests[i].size() != 1)
                storage[cur.first][cur.second] = '.';
            else
            {
                answer++;
                q[requests[i][0] - 'A'].push(cur);                    
            }
        }
        while (!q2.empty())
        {

            cur = q2.front();
            q2.pop();
            storage[cur.first][cur.second] = 'q';
            bfs(cur, storage);
        }
    }
    return answer;
}