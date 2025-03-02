#include <stack>
#include <iostream>
#include <vector>

int main (void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::vector<char> v;
    std::stack<int> s;
    int n, target, id, flag;
   
    std::cin >> n;
    id = 1; flag = 1;
    for (int j = 0; j < n; j++)
    {
        std::cin  >> target;
        for (; id <= target && flag; id++)
        {
            s.push(id);
            v.push_back('+');
        }
        if (s.empty() || s.top() != target)
            flag = 0;
        else if(flag)
        {
            v.push_back('-');
            s.pop();            
        }
    }
    for (size_t i = 0; flag == 1 && i < v.size(); i++)
        std::cout << v[i] << '\n';
    if (!flag)
        std::cout << "NO" << '\n';
}