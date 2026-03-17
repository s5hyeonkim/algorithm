#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 반복되는 문자열을 저장
vector<int> pi, dp;
int main(void) {
	int n, id;
	long long ret;
	string s;

	cin >> n >> s;
	pi.resize(n, 0);
	dp.resize(n, 0);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j > 0 && s[j] != s[i])
			j = pi[j - 1];
		if (s[i] == s[j])
			j++;
		pi[i] = j;
		dp[i] = j;
		if (dp[i] > 0 && dp[dp[i] - 1] > 0)
			dp[i] = dp[dp[i] - 1];
	}
	ret = 0;
	for (int i = 1; i < n; i++) {
		if (dp[i] && dp[i] <= (i + 1) / 2)
			ret += i + 1 - dp[i];
	}
	cout << ret << std::endl;
}
