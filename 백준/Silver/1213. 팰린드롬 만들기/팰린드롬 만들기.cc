#include <iostream>
#include <queue>
using namespace std;

priority_queue<char, vector<char>, greater<char> >  pq;

void input()
{
    string  str;

    cin >> str;
    for (int i = 0; i < str.size(); i++)
        pq.push(str[i]);
    
}

int main (void)
{
    vector<char>    answer;
    size_t          size, id;
    char            temp;

    id = 0; temp = 0;
    input();
    size = pq.size(); answer.resize(size);
    while (!pq.empty())
    {
        answer[id] = pq.top();
        pq.pop();
        if (!pq.empty() && answer[id] == pq.top())
        {
            answer[size - 1 - id] = pq.top();
            pq.pop();
            id++;
        }
        else if (temp)
        {
            cout << "I'm Sorry Hansoo" << '\n';
            return 0;
         }
        else
        {
            temp = answer[id];
            continue ;
        }
    }
    if (temp)
        answer[id] = temp;
    for (size_t i = 0; i < size; i++)
        cout << answer[i];
    cout << '\n';
}