#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector <int> prefix_s, prefix_k, suffix_s, suffix_k;
size_t N;
void input() {
	string s;
	
	cin >> N;
	cin >> s;
	prefix_s.resize(N + 1, 0);
	prefix_k.resize(N + 1, 0);
	suffix_s.resize(N + 2, 0);
	suffix_k.resize(N + 2, 0);
	for (size_t i = 1; i <= N; i++) {
		if (s[i - 1] == 's') {
			prefix_s[i] = prefix_s[i - 1] + 1;
			prefix_k[i] = prefix_k[i - 1];
		}
		else {
			prefix_k[i] = prefix_k[i - 1] + 1;
			prefix_s[i] = prefix_s[i - 1];
		}
	}
	for (int i = N; i >= 1; i--) {
		if (s[i - 1] == 's') {
			suffix_s[i] = suffix_s[i + 1] + 1;
			suffix_k[i] = suffix_k[i + 1];
		}
		else {
			suffix_s[i] = suffix_s[i + 1];
			suffix_k[i] = suffix_k[i + 1] + 1;
		}
	}
}

int split(const pair<int, int> & f, const pair<int, int>& s, const int& idx, const int& cnt, vector<int>& result) {
	if (!cnt) {
		return f.first + suffix_s[idx] == N / 4 && f.second + suffix_k[idx] == N / 4;
	}
	else if (cnt == 1) {
		int num = N / 2 - f.first - f.second;
		result[cnt - 1] = idx + num - 1;
		return split(s, {f.first + prefix_s[idx + num - 1], f.second + prefix_k[idx + num - 1]}, idx + num, cnt - 1, result);
	}
	for (int i = idx; i < N - cnt + 1; i++) {
		if (f.first + prefix_s[i] - prefix_s[idx - 1] > N / 4)
			break;
		if (f.second + prefix_k[i] - prefix_k[idx - 1] > N / 4)
			break;
		if (f.first + f.second + i - idx + 1 > N / 2)
			break;
		result[cnt - 1] = i;
		if (split(s, { f.first + prefix_s[i] - prefix_s[idx - 1], f.second + prefix_k[i] - prefix_k[idx - 1] }, i + 1, cnt - 1, result))
			return true;
	}
	return false;
}

int operate(vector<int> &result) {
	int cur;
	pair<int, int> jake, fin;

	if (prefix_s[N / 2] == N / 4 && prefix_k[N / 2] == N / 4) {
		result.push_back(N / 2);
		return 1;
	}
	for (int cnt = 2; cnt <= N; cnt++) {
		jake = { 0, 0 };
		fin = { 0, 0 };
		result.resize(cnt);
		if (split(jake, fin, 1, cnt, result))
			return cnt;
	}
	return -1;
}

void print() {
	for (int i = 1; i <= N; i++)
		cout << prefix_s[i] << " ";
	cout << '\n';
	for (int i = 1; i <= N; i++)
		cout << suffix_s[i] << " ";
	cout << '\n';
}

int main(void) {
	vector<int> result;
	
	input();
	//print();
	cout << operate(result) << '\n';
	sort(result.begin(), result.end());
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
	cout << '\n';
}