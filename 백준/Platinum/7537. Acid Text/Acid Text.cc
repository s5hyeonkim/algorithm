#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

int tcase;
struct File {
	vector<string> graphics;
	string name;
	int h, w;
	File() : h(0), w(0) {}
	void refine() {
		for (auto& s : graphics) {
			for (auto& c : s) {
				if (c == '.')
					c = ' ';
			}
		}
	}
};

struct Css {
	string id;
	int x, y;
	Css* parent;
	File* file;
	int layer;
	Css() : id(""), x(0), y(0), parent(nullptr), file(nullptr), layer(0) {}
	Css(const string &id) : id(id), x(0), y(0), parent(nullptr), file(nullptr), layer(0) {}
	~Css() {
		file = nullptr;
		parent = nullptr;
	}
	pair<int, int> getLTop() const {
		pair<int, int> ret = { 0, 0 };
		if (parent)
			ret = parent->getLTop();
		return { ret.first + x, ret.second + y };
	}
};

map<string, File*> m_f;
map<string, Css*> m_css;
bool isWhiteSpace(const char& c) {
	if (c == ' ' || c == '\n' || c == '\t')
		return true;
	return false;
}
string parseByLimiter(const string& s, int beg, const char& limiter) {
	string ret = "";

	while (beg < s.size() && isWhiteSpace(s[beg]))
		beg++;
	while (beg < s.size() && !isWhiteSpace(s[beg]) && s[beg] != limiter)
		ret += s[beg++];
	return ret;
}

struct cmp {
	bool operator()(const pair<int, Css* >& p1, pair<int, Css* >& p2) {
		if (p1.second->layer != p2.second->layer)
			return p1.second->layer > p2.second->layer;
		return p1.first > p2.first;
	}
};
priority_queue < pair<int, Css* >, vector<pair<int, Css *>>, cmp> pq;
void input(Css *bg) {
	string str, id, obj;
	int nfiles, ncss;

	cin >> nfiles; 
	for (int i = 0; i < nfiles; i++) {
		File *f = new File();
		cin >> f->name >> f->h >> f->w;
		f->graphics.resize(f->h);
		for (int i = 0; i < f->h; i++)
			cin >> f->graphics[i];
		f->refine();
		m_f[f->name] = f;
	}
	cin >> ncss;
	for (int i = 0; i < ncss; i++) {
		getline(cin, str, '#');
		getline(cin, str, '\n');
		id = parseByLimiter(str, 0, '{');
		if (!m_css[id])
			m_css[id] = new Css(id);
		for (int j = 0; j < 5; j++) {
			getline(cin, str, ':');
			getline(cin, obj, '\n');
			obj = parseByLimiter(obj, obj.find('=') + 1, ';');
			if (str.find("pos-x") != (size_t)-1)
				m_css[id]->x = stoi(obj);
			else if (str.find("pos-y") != (size_t)-1)
				m_css[id]->y = stoi(obj);
			else if (str.find("position") != (size_t)-1 && obj.find("absolute") != (size_t)-1)
				m_css[id]->parent = bg;
			else if (str.find("position") != (size_t)-1) {
				if (!m_css[obj])
					m_css[obj] = new Css(obj);
				m_css[id]->parent = m_css[obj];
			}
			else if (str.find("file") != (size_t)-1) {
				obj = parseByLimiter(obj, 0, ';');
				m_css[id]->file = m_f[obj];
			}
			else
				m_css[id]->layer = stoi(obj);
		}
		getline(cin, str, '\n');
		pq.push({ i, m_css[id] });
	}
}

void operate(Css *bg) {
	vector<string> s;
	pair<int, Css*> cur;
	pair<int, int> beg;
	int nh, nw, ch;
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		vector<string>& cv = cur.second->file->graphics;
		beg = cur.second->getLTop();
		nh = cv.size() + beg.second;
		nw = s.empty() ? 0 : s[0].size();
		nw = max(nw, (int)cv[0].size() + beg.first);
		ch = s.size();
		if (nh > ch)
			s.resize(nh);
		for (int i = 0; i < s.size(); i++) {
			if (s[i].size() < nw)
				s[i].resize(nw, ' ');
		}
		if (cv[0].size() + beg.first > s[0].size()) {
			for (int i = 0; i < s.size(); i++)
				s[i].resize(cv[0].size() + beg.first, ' ');
		}
		for (int i = 0; i < cv.size(); i++) {
			for (int j = 0; j < cv[i].size(); j++) { 
				if (cv[i][j] != ' ')
					s[i + beg.second][j + beg.first] = cv[i][j];
			}
		}
	}
	for (int i = 0; i < s.size(); i++)
		cout << s[i] << '\n';
}

int main(void) {
	cin >> tcase;
	for (int i = 0; i < tcase; i++) {
		cout << "Scenario #" << i + 1 << ":\n";
		Css* bg = new Css();
		input(bg);
		operate(bg);
		cout << '\n';
		delete bg;
		for (const auto& f : m_f)
			delete f.second;
		for (const auto& s : m_css)
			delete s.second;
		m_css.clear();
		m_f.clear();
	}
}
