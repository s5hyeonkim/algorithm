#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<char>              l;
    list<char>::iterator    it;
    int                     cmdNum;
    string                  str;
    char                    cmd, obj;
    
    cin >> str >> cmdNum;
    for (int i = 0; i < str.size(); i++)
        l.push_back(str[i]);
    it = l.end();
    for (int i = 0; i < cmdNum; i++)
    {
        cin >> cmd;
        if (cmd == 'P')
        {
            cin >> obj;
            l.insert(it, obj);
        }
        else if (cmd == 'L' && it != l.begin())
            it--;
        else if (cmd == 'D' && it != l.end())
            it++;
        else if (cmd == 'B' && it != l.begin())
        {
            --it;
            l.erase(it++);     
        }
    }
    for (auto itr = l.begin(); itr != l.end(); itr++)
        cout << *itr;
    cout << '\n';
}