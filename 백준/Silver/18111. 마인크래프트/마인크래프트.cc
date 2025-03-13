#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

vector<int> boards;
int r, c, blocks;
void    input()
{
    cin >> r >> c >> blocks;
    boards.resize(r * c);
    for (int i = 0; i < r * c; i++)
        cin >> boards[i];
}

int main (void)
{
    pair<int, int>  answer;
    int             max, min, useblock, elapsed_time;

    input();
    max = *max_element(boards.begin(), boards.end());
    min = *min_element(boards.begin(), boards.end());
    answer = make_pair(2147483647, 0);
    for (; max >= min; max--)
    {
        useblock = blocks;
        elapsed_time = 0;
        for (int i = 0; i < r * c; i++)
        {
            if (boards[i] > max)
                elapsed_time += (boards[i] - max) * 2;
            else
                elapsed_time += (max - boards[i]);
            useblock += boards[i] - max;
        }
        if (useblock < 0)
            continue ;
        if (elapsed_time >= answer.first)
            break ;
        answer = make_pair(elapsed_time, max);
    }
    std::cout << answer.first << " " << answer.second << '\n';
}