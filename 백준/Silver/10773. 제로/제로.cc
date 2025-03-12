#include <iostream>
using namespace std;

class Stack
{
    private:
        int     arr[100050];
        size_t  m_size;
        int     m_sum;
    public:
        Stack() { m_size = 0; m_sum = 0;}
        size_t  size() { return m_size ; }
        int     sum() { return m_sum; }
        void    push(int num) { arr[m_size++] = num; m_sum += num;}
        int     pop() { m_sum -= arr[--m_size]; return arr[m_size]; }
};

int main (void)
{
    Stack       s;
    int         n, num, answer;

    cin >> n;
    answer = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        if (num)
            s.push(num);
        else
            answer -= s.pop();
    }
    cout << s.sum() << '\n';
}