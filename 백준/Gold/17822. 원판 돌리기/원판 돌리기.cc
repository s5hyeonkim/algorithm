#include <iostream>
#include <vector>
#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1
using namespace std;

typedef struct Circle {
	int sum, start_idx, size;
	vector<int> nums;
	void rotate(const int& dir, const int& step) {
		if (dir == CLOCKWISE)
			start_idx = start_idx + nums.size() - step;
		else
			start_idx += step;
		start_idx %= nums.size();
	}
	int getNumberById(const int& id) const {
		return nums[(start_idx + id) % nums.size()];
	}
	void removeNumberById(const int& id) {
		if (getNumberById(id) == 0)
			return;
		sum -= nums[(start_idx + id) % nums.size()];
		nums[(start_idx + id) % nums.size()] = 0;
		size--;
	}
	
	void setNumberById(const int& id, const int& target) {
		size++;
		sum += target;
		nums[(start_idx + id) % nums.size()] = target;
	}

	void renewNumberById(const int& id, const int& target) {
		sum += target - getNumberById(id);
		nums[(start_idx + id) % nums.size()] = target;
	}
	
	void push(const int &num) {
		sum += num;
		nums.push_back(num);
		size++;
	}
	int getSum() const {
		return sum;
	}
	int getSize() const {
		return size;
	}
	int getNextNumById(const int &id) const {
		return nums[(start_idx + 1 + id) % nums.size()];
	}
	int getPrevNumById(const int &id) const {
		return nums[(nums.size() + start_idx - 1 + id) % nums.size()];
	}
	void print() const{
		for (int i = 0; i < nums.size(); i++) {
			int idx = (start_idx + i) % nums.size();
			cout << nums[idx] << " ";
		}
		cout << '\n';
	}
	Circle(): sum(0), start_idx(0), size(0) {}
}	Circle;

struct Order {
	int id, dir, step;
	Order(): id(0), dir(0), step(0) {}
	void push(const int& id, const int& dir, const int& step) {
		this->id = id;
		this->dir = dir;
		this->step = step;
	}
};

int n, m, k;
vector<Circle> circles;
vector<Order> orders;


bool removeBySeed(const int& cid, const int& idx) {
	int flag = false;
	int seed = circles[cid].getNumberById(idx);

	circles[cid].removeNumberById(idx);
	if (circles[cid].getNextNumById(idx) == seed) {
		flag = true;
		removeBySeed(cid, (idx + 1) % m);
		circles[cid].removeNumberById((idx + 1) % m);
	}
	if (circles[cid].getPrevNumById(idx) == seed) {
		flag = true;
		removeBySeed(cid, (idx + m - 1) % m);
		circles[cid].removeNumberById((idx + m - 1) % m);
	}
	if (cid != n && circles[cid + 1].getNumberById(idx) == seed) {
		flag = true;
		removeBySeed(cid + 1, idx);
		circles[cid + 1].removeNumberById(idx);
	}
	if (cid != 1 && circles[cid - 1].getNumberById(idx) == seed) {
		flag = true;
		removeBySeed(cid - 1, idx);
		circles[cid - 1].removeNumberById(idx);
	}
	if (!flag)
		circles[cid].setNumberById(idx, seed);
	return flag;
}

int checkNumberByCircle(const int &cid) {
	bool flag = false;
	for (int idx = 0; idx < m; idx++) {
		if (circles[cid].getNumberById(idx) && removeBySeed(cid, idx))
			flag = true;
	}
	return flag;
}

bool rotateByOrder(const Order& ord) {
	bool flag = false;
	for (int id = ord.id; id <= n; id += ord.id) {
		circles[id].rotate(ord.dir, ord.step);
	}
	return flag;
}

int checkNumber() {
	bool flag = false;
	for (int cid = 1; cid <= n; cid++) {
		for (int idx = 0; idx < m; idx++) {
			if (circles[cid].getNumberById(idx) && removeBySeed(cid, idx))
				flag = true;
		}
	}
	return flag;
}
int takeSize() {
	int result = 0;
	for (int i = 1; i <= n; i++)
		result += circles[i].getSize();
	return result;
}

int takeSum() {
	int result = 0;
	for (int i = 1; i <= n; i++)
		result += circles[i].getSum();
	return result;
}

void print() {
	for (int i = 1; i <= n; i++) {
		cout << "Circles " << i << "\n";
		circles[i].print();
	}
}

void renewNumber() {
	int target;
	int sum = takeSum();
	int size = takeSize();
	if (!size)
		return;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			target = circles[i].getNumberById(j);
			if (target && target * size > sum)
				circles[i].renewNumberById(j, target - 1);
			else if (target && target * size < sum)
				circles[i].renewNumberById(j, target + 1);
		}
	}
}

void operate() {
	bool flag;
	for (auto it = orders.begin(); it != orders.end(); it++) {
		flag = rotateByOrder(*it);
		if (!checkNumber() && !flag)
			renewNumber();
		//print();
	}
}

void input() {
	int num, id, dir, step;

	cin >> n >> m >> k;
	circles.resize(n + 1);
	orders.resize(k);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> num;
			circles[i].push(num);
		}
	}
	for (int i = 0; i < k; i++) {
		cin >> id >> dir >> step;
		orders[i].push(id, dir, step);
	}
}


int main(void) {
	input();
	operate();
	cout << takeSum() << "\n";
}