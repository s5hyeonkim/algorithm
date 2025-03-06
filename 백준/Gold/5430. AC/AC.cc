# include <iostream>
# include <deque>
using namespace std;

deque<int> deq;
string      cmds, arr;
int         num;

void init () {
    int     cnt;

    cin >> cmds >> num >> arr;
    cnt = 0;
    deq.clear();
    deq.resize(num, 0);
    for (size_t idx = 1; idx < arr.size() - 1; idx++)
    {
        if (isdigit(arr[idx]))
            deq[cnt] = deq[cnt] * 10 + arr[idx] - '0';
        else
            cnt++;
    }
}

void operate() {
    int flag;

    flag = 1;
    for (size_t idx = 0; idx < cmds.size(); idx++)
    {
        if (cmds[idx] == 'D' && deq.empty())
        {
            std::cout << "error" << '\n';
            return ;
        }
        else if (flag && cmds[idx] == 'D')
            deq.pop_front();
        else if (cmds[idx] == 'D')
            deq.pop_back();
        else
            flag = !flag;
    }
    std::cout << '[';
    if (flag == 1)
    {
        for (auto it = deq.begin(); it != deq.end(); it++)
        {
            std::cout << *it;
            if (it != deq.end() - 1)
                std::cout << ',';
        }
    }
    else
    {
        for (auto it = deq.rbegin(); it != deq.rend(); it++)
        {
            std::cout << *it;
            if (it != deq.rend() - 1)
                std::cout << ',';
        }
    }
    std::cout << ']' << '\n';
}

int main (void)
{
    int tcase;

    cin >> tcase;
    while (tcase--)
    {
        init();
        operate();
    }
}
