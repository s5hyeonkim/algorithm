#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
map<string, int> m;

int cmp(const string& s1, const string& s2) {
	for (int i = 0; i < s1.size(); i++) {
		if (i == s2.size())
			return s2.size();
		if (s1[i] != s2[i])
			return i;
	}
	return s1.size();
}

int main(void) {
	vector<string> v;
	int n, result, cnt, temp[2];
	int idx[2];
	string s;

	cin >> n; 
	result = -1;
	for (int i = 0; i < n; i++) {
		cin >> s;
		m[s] = i;
		v.push_back(s);
	}
	for (auto it = m.begin(); it != m.end(); it++) {
		auto it2 = it;
		if (++it2 == m.end())
			break;
		for (; it2 != m.end(); it2++) {
			temp[0] = min(it->second, it2->second);
			temp[1] = max(it->second, it2->second);
			if (result < (cnt = cmp(it->first, it2->first))) {
				result = cnt;
				idx[0] = temp[0];
				idx[1] = temp[1];
			}
			else if (result == cnt && idx[0] >= temp[0]) {
				if (idx[0] > temp[0]) {
					idx[0] = temp[0];
					idx[1] = temp[1];
				}
				else if (idx[0] == temp[0] && idx[1] > temp[1])
					idx[1] = temp[1];
			}
			else if (result > cnt)
				break;
		}
	}
	cout << v[idx[0]] << '\n' << v[idx[1]] << std::endl;
}