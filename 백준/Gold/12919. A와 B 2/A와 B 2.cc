#include <iostream>
#include <string>
#include <vector>
#define FORWARD 0
#define BACKWARD 1
using namespace std;

string s, t;
bool check(string s, const string& t, const int &dir, const int &idx) {
	if (dir == FORWARD) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != t[i + idx])
				return 0;
		}
		return 1;
	}
	else {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != t[t.size() - 1 - i])
				return 0;
		}
	}
	return 1;
}

int dfs(const string& s, string t, const int &dir, const int &idx) {
	char c = 0;
	bool flag = false;
	if (s.size() == t.size() - idx) {
		if (check(s, t, dir, idx))
			return 1;
		return 0;
	}
	if (dir == FORWARD && t.back() == 'A') {
		t.pop_back();
		flag = dfs(s, t, dir, idx);
		t.push_back('A');
	}
	if (!flag && dir == FORWARD && t[idx] == 'B') {
		flag = dfs(s, t, BACKWARD, idx + 1);
	}
	if (!flag && dir == BACKWARD && t[idx] == 'A') {
		flag = dfs(s, t, BACKWARD, idx + 1);
	}
	if (!flag && dir == BACKWARD && t.back() == 'B') {
		t.pop_back();
		flag = dfs(s, t, FORWARD, idx);
		t.push_back('B');
	}
	return flag;
}
int main(void) {
	cin >> s >> t;
	cout << dfs(s, t, 0, 0) << "\n";
}