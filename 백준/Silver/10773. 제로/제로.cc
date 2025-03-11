#include <iostream>
#include <stack>
using namespace std;

int main (void)
{
    stack<int>  s;
    int         n, num, answer;

    cin >> n;
    answer = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        if (num)
        {
            s.push(num);
            answer += num;
        }
        else
        {
            answer -= s.top();
            s.pop();
        }
    }
    cout << answer << '\n';
}