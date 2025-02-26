#include <string>
#include <vector>

using namespace std;
void    timeFlow(int &h1, int &m1, int &s1)
{
    ++s1 %= 60;
    if (!s1)
        ++m1 %= 60;
    if (!s1 && !m1)
        h1++;
}

int backToZero(int num) {
    return num % (12 * 3600);
}

void    moveNeedleBySeconds(int &hpos, int &mpos, int &spos) {
    hpos = backToZero(hpos + 1);
    mpos = backToZero(mpos + 12); 
    spos = backToZero(spos + 720);
}

bool isBetween(int s1, int e1, int s2, int e2)
{
    if (s1 < s2 && e2 <= e1)
        return true ;
    return false;
}

int isThereNeedle(int hpos, int mpos, int spos)
{
    return isBetween(spos, spos + 720, mpos, mpos + 12) + isBetween(spos, spos + 720, hpos, hpos + 1) - (mpos + 12 == spos + 720 && spos + 720 == hpos + 1);
}

void init (int &hpos, int &mpos, int &spos, int h1, int m1, int s1)
{
    hpos = backToZero(3600 * h1 + 60 * m1 + s1);
    mpos = (60 * m1 + s1) * 12;
    spos = 720 * s1;    
}
#include <iostream>
int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    int answer;
    int hpos, mpos, spos;

    init(hpos, mpos, spos, h1, m1, s1);
    answer = (hpos == mpos || spos == mpos);    
    while (h1 != h2 || m1 != m2 || s1 != s2)
    {
        answer += isThereNeedle(hpos, mpos, spos);
        moveNeedleBySeconds(hpos, mpos, spos);
        timeFlow(h1, m1, s1);
    }
    return answer;
}