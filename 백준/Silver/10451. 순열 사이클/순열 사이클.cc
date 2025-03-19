#include <iostream>
#include <vector>
using namespace std;

int main (void)
{
    vector<int> v, used;
    int         tcase, n, next, cnt;

    cin >> tcase;
    for (; tcase > 0; tcase--)
    {
        cin >> n;
        v.resize(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> v[i];
        used.resize(n + 1, 0);
        cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (used[i])
                continue ;
            cnt++;
            used[i] = 1;
            next = v[i];
            while (!used[next])
            {
                used[next] = 1;
                next = v[next];
            }
        }
        cout << cnt << '\n';
        v.clear();
        used.clear();
    }
}