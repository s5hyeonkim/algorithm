#include <iostream>
using namespace std;

int main (void)
{
    int     num, answer;

    cin >> num;
    answer = num > 99 ? 99 : num;
    while (num >= 100)
    {
        if (num / 100 - num / 10 % 10 == num / 10 % 10 - num % 10)
            answer++;
        num--;
    }
    cout << answer << '\n';
}