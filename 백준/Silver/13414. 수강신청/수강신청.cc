/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <unordered_map>
#include <map>
using namespace std;

int main()
{
    int n, k;
    string input;
    unordered_map<string, int> um;
    map<int, string> m;

    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        cin >> input;
        m[i] = input;
        um[input] = i;
    }
    for (auto it = m.begin(); it != m.end() && n; it++)
    {
        if (it->first == um[it->second])
        {
            n--;
            std::cout << it->second << '\n';
        }
    }
    return 0;
}