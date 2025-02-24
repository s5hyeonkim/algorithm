#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int answer;

bool    cmp(vector<int> &v1, vector<int> &v2)
{
    if (v1[0] > v2[0])
        return true;
    if (v1[0] < v2[0])
        return false;
    if (v1[1] < v2[1])
        return true;
    return false;
}

void    dfs(vector<vector<int>> &info, int n, int m, int recur)
{
    if (recur == info.size() || answer >= n)
    {
        answer = max(answer, n);
        return ;
    }
    if (m - info[recur][1] > 0)
        dfs(info, n, m - info[recur][1], recur + 1);
    if (n - info[recur][0] > 0)
        dfs(info, n - info[recur][0], m, recur + 1);
}

int solution(vector<vector<int>> info, int n, int m) {
    answer = -1;
    sort(info.begin(), info.end(), cmp);
    dfs(info, n, m, 0);
    if (answer != -1)
        answer = n - answer;
    return answer;
}