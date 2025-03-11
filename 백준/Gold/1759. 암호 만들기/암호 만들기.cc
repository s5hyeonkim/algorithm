#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int l, c;
string str;

bool	isVowel(char c)
{
	if (c == 'a' || c == 'i' || c == 'e' || c == 'o' || c == 'u')
		return true;
	return false;
}

void	dfs(string &answer, int vnum, int cnum, int cur)
{
	if (answer.size() == l)
	{
		if (vnum >= 1 && cnum >= 2)
			cout << answer << '\n';
		return;
	}
	for (int i = cur; i < str.size(); i++)
	{
		answer += str[i];
		dfs(answer, vnum + isVowel(str[i]), cnum + !isVowel(str[i]), i + 1);
		answer.pop_back();
	}
}

int main(void)
{
	string	answer;

	cin >> l >> c;
	str.resize(c);
	for (int i = 0; i < c; i++)
		cin >> str[i];
	sort(str.begin(), str.end());
	dfs(answer, 0, 0, 0);
}