#include <iostream>
#include <utility>
#include <queue>
using namespace std;

struct cmp
{
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2)
    {
        if (p1.second > p2.second)
            return true;
        return false;
    }
};

int main (void)
{
    priority_queue<pair<int,int>, vector<pair<int,int> >, cmp>  pq;
    vector<int>                                                 arr, answer;
    pair<int, int>                                              cur;
    int                                                         n;
    size_t                                                      size;

    cin >> n;
    arr.resize(n);
    answer.resize(n, -1);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        while (!pq.empty() && pq.top().second < arr[i])
        {
            answer[pq.top().first] = arr[i];
            pq.pop();
        }
        pq.push(make_pair(i, arr[i]));
    }
    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';
    cout << '\n';
}