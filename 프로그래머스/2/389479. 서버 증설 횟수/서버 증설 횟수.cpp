#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef struct s_info
{
    int id, cnt;
}   t_info;

int solution(vector<int> players, int m, int k) {
    queue<t_info>   q;
    t_info          cur;
    int             answer;
    size_t          size;

    answer = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i] / m == 0)
            continue ;
        size = q.size();
        while (size--)
        {
            cur = q.front();
            q.pop();
            if (i - cur.id < k - 1)
                q.push(cur);
            if (i - cur.id < k)
                players[i] -= m * cur.cnt;
        }
        if (players[i] / m > 0)
        {
            q.push({i, players[i] / m});
            answer += players[i] / m;
        }
    }
    return answer;
}