#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main (void)
{
    int n;
    long long answer;
    vector<int> v;

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    answer = 0;
    for (long long i = 0; i < n; i++)
        answer = answer + i * v[i] + (1 + i - n) * v[i];
    cout << answer * 2L << endl;
    return 0;
}