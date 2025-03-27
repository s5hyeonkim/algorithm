#include <iostream>
#include <vector>
using namespace std;
vector<int>coins, dp;
int	n, target;

int main() {

    cin >> n >> target;
    dp.resize(target + 1, 0);
    coins.resize(n);

    for (int i = 0; i < n; i++) 
        cin >> coins[i];

    dp[0] = 1;
    for (int i = 0; i < n; i++) 
    {
        for (int j = coins[i]; j <= target; j++)
            dp[j] += dp[j - coins[i]];
    }

    cout << dp[target] << '\n';
}